#include "pch.h"
#include "Render3D.h"

bool Render3D::Init(HWND windowHandle, ECSManager* ECS, GraphicsDevice* graphicsDevice, DescriptorManager* descriptorManager, CommandManager* commandManager, MeshManager* meshManager)
{
	m_ECS = ECS;

	mp_graphicsDevice = graphicsDevice;
	mp_descriptorManager = descriptorManager;
	mp_commandManager = commandManager;
	m_windowWP = windowHandle;
	m_meshManager = meshManager;

	m_graphicsPipeline.Init(mp_graphicsDevice, mp_descriptorManager, mp_commandManager);

	InitConstantBuffer();
	CreatePipeline();

	// Ce bloc permet de verifier si un chemin/fichier existe
	/*DWORD len = GetFullPathNameW(L"..\\LyonPlexLib\\Ressources\\PixelShader.hlsl", 0, nullptr, nullptr);
	std::wstring fullpath(len, L'\0');
	GetFullPathNameW(L"..\\LyonPlexLib\\Ressources\\PixelShader.hlsl", len, fullpath.data(), nullptr);
	MessageBoxW(nullptr, fullpath.c_str(), L"Full path", MB_OK);*/


	return true;
}

void Render3D::Resize(int w, int h)
{
	//D3D12_VIEWPORT vp{ 0, 0, float(w), float(h), 0.f, 1.f };
	//D3D12_RECT     sc{ 0, 0, w, h };
	//auto cmd = mp_commandManager->GetCommandList();
	//cmd->RSSetViewports(1, &vp);
	//cmd->RSSetScissorRects(1, &sc);
}

void Render3D::RecordCommands()
{
	// Ensure size of global buffer
	UINT currentCount = static_cast<UINT>(m_ECS->GetEntityCount());
	EnsureCapacity(currentCount);

	// On definie la pipeline et la rootSignature
	mp_commandManager->GetCommandList()->SetGraphicsRootSignature(m_graphicsPipeline.GetRootSignature().Get());
	mp_commandManager->GetCommandList()->SetPipelineState(m_graphicsPipeline.GetPipelineState().Get());

	// Bind du buffer ViewProj de la Camera au slot b0
	mp_commandManager->GetCommandList()->SetGraphicsRootConstantBufferView(/*rootParameterIndex = slot b0*/ 0, m_ECS->m_systemMgr.GetCameraSystem().GetCBbuffer()->GetGPUVirtualAddress());

	// Bind des Heaps SRV + Sampler
	// 1. Rassemble tous tes descriptor heaps (SRV + Sampler)
	ID3D12DescriptorHeap* heaps[] = { mp_descriptorManager->GetSrvHeap()/*, mp_descriptorManager->GetSamplerHeap()*/ }; //  SRV heap (contenant toutes les textures) et Sampler heap ATTENTION SAMPLERS ONT CASSE LA PORTABILITE
	mp_commandManager->GetCommandList()->SetDescriptorHeaps(_countof(heaps), heaps);

	// 2. Bind UNE SEULE FOIS l’integralite de ton heap SRV au slot t0 (rootParameter index = 2)
	D3D12_GPU_DESCRIPTOR_HANDLE srvBase = mp_descriptorManager->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart();
	mp_commandManager->GetCommandList()->SetGraphicsRootDescriptorTable(/*rootParameterIndex=*/2, srvBase);


	//Draw vertices and index (mesh)
	mp_commandManager->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mp_commandManager->GetCommandList()->IASetVertexBuffers(0, 1, &m_meshManager->GetGlobalVBView());
	mp_commandManager->GetCommandList()->IASetIndexBuffer(&m_meshManager->GetGlobalIBView());

	// Get la width et height du client (fenetre)
	RECT renderZone;
	GetClientRect(mp_graphicsDevice->GetWindow(), &renderZone);
	UINT renderWidth = renderZone.right - renderZone.left;
	UINT renderHeight = renderZone.bottom - renderZone.top;
	// Definir le viewport et le scissor  (peuvent servir a "fenetrer" de l'affichage, par exemple pour minimap) : PEUT ETRE GENERAL OU VARIABLE
	// Le viewport represente la zone de la fenetre dans laquelle on va dessiner
	D3D12_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = renderWidth;  // window width
	viewport.Height = renderHeight;  // window height
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	// Le scissor defini un rectangle de pixels a dessiner dans la zone de dessin (viewport). Tous les pixels en dehors de cette zone ne sont pas dessines.
	D3D12_RECT scissorRect = { 0, 0, static_cast<LONG>(renderWidth), static_cast<LONG>(renderHeight) };
	// Actualisation du rectangle dans lequel on dessine, dans la fenetre
	mp_commandManager->GetCommandList()->RSSetViewports(1, &viewport);
	mp_commandManager->GetCommandList()->RSSetScissorRects(1, &scissorRect);

	ComponentMask local3DMask = (1ULL << MeshComponent::StaticTypeID) | (1ULL << Type_3D_LOC::StaticTypeID);
	m_ECS->ForEach(local3DMask, [&](Entity ent)
		{
			//const Material& mat = materialLib.Get(m->materialID);

			UpdateAndBindCB(ent);
			MeshComponent* meshComp = m_ECS->GetComponent<MeshComponent>(ent);
			uint32_t texId = meshComp->materialID;
			const MeshData& mesh = m_meshManager->GetMeshLib().Get(meshComp->meshID);

			// pour chaque sub‐mesh dans ce mesh
			for (auto const& sub : mesh.subMeshes)
			{
				if (sub.MaterialID < mesh.materialTextureIDs.size()) // BUG SI CETTE LIGNE EST ENLEVEE
				{
					

					//if (meshComp->materialID == 0)
					//{
					//	// 1) prendre le TextureID associé :
					//	texId = mesh.materialTextureIDs[sub.MaterialID];
					//}
					//else
					//	texId = meshComp->materialID;

					// 2) calculer le handle précis dans le heap (offset en descriptors) :
					UINT descSize = mp_descriptorManager->GetSrvDescriptorSize();
					D3D12_GPU_DESCRIPTOR_HANDLE handle = srvBase;
					handle.ptr += texId * descSize;

					// DEBUG
					/*char buf[128];
					sprintf_s(buf, sizeof(buf),
						"Binding texId=%u for Entity = %u ; submesh matID=%u\n",
						texId, ent, sub.MaterialID);
					OutputDebugStringA(buf);*/
					/*char bufDraw[128];
					sprintf_s(bufDraw, sizeof(bufDraw),
						"[Draw] Entity %u – mesh %u – subMat %u → texId = %u\n",
						ent.id,
						meshComp->meshID,
						sub.MaterialID,
						texId);
					OutputDebugStringA(bufDraw);*/

					// 3) binder **uniquement** ce handle sur rootParam 2 :
					mp_commandManager->GetCommandList()->SetGraphicsRootDescriptorTable(/*rootParamIndex=*/ 2, handle);

					UINT globalIndexStart = mesh.iOffset + sub.IndexOffset;
					// 4) dessiner ce submesh :
					mp_commandManager->GetCommandList()->DrawIndexedInstanced(
						sub.IndexCount,
						1,
						globalIndexStart,
						0,
						0);
				}
			}
			
		});


	ComponentMask loaded3DMask = (1ULL << MeshComponent::StaticTypeID) | (1ULL << Type_3D_EXT::StaticTypeID);
	m_ECS->ForEach(loaded3DMask, [&](Entity ent)
		{

			UpdateAndBindCB(ent);

			MeshComponent* meshComp = m_ECS->GetComponent<MeshComponent>(ent);
			const MeshData& mesh = m_meshManager->GetMeshLib().Get(meshComp->meshID);

			// pour chaque sub‐mesh dans ce mesh
			for (auto const& sub : mesh.subMeshes)
			{
				if (sub.MaterialID < mesh.materialTextureIDs.size()) // BUG SI CETTE LIGNE EST ENLEVEE
				{
					uint32_t texId = mesh.materialTextureIDs[sub.MaterialID];

					//if (meshComp->materialID == 0)
					//{
					//	// 1) prendre le TextureID associé :
					//	texId = mesh.materialTextureIDs[sub.MaterialID];
					//}
					//else
					//	texId = meshComp->materialID;

					// 2) calculer le handle précis dans le heap (offset en descriptors) :
					UINT descSize = mp_descriptorManager->GetSrvDescriptorSize();
					D3D12_GPU_DESCRIPTOR_HANDLE handle = srvBase;
					handle.ptr += texId * descSize;

					// DEBUG
					/*char buf[128];
					sprintf_s(buf, sizeof(buf),
						"Binding texId=%u for Entity = %u ; submesh matID=%u\n",
						texId, ent, sub.MaterialID);
					OutputDebugStringA(buf);*/
					/*char bufDraw[128];
					sprintf_s(bufDraw, sizeof(bufDraw),
						"[Draw] Entity %u – mesh %u – subMat %u → texId = %u\n",
						ent.id,
						meshComp->meshID,
						sub.MaterialID,
						texId);
					OutputDebugStringA(bufDraw);*/

					// 3) binder **uniquement** ce handle sur rootParam 2 :
					mp_commandManager->GetCommandList()->SetGraphicsRootDescriptorTable(/*rootParamIndex=*/ 2, handle);

					UINT globalIndexStart = mesh.iOffset + sub.IndexOffset;
					// 4) dessiner ce submesh :
					mp_commandManager->GetCommandList()->DrawIndexedInstanced(
						sub.IndexCount,
						1,
						globalIndexStart,
						0,
						0);
				}
			}
		});


	// ** passe 2.5D **
	// on réutilise la même PSO3D, même view+proj, même depth‑test…
	ComponentMask mask2_5 = (1ULL << MeshComponent::StaticTypeID)
		| (1ULL << Type_2D5::StaticTypeID);
	m_ECS->ForEach(mask2_5, [&](Entity ent) {
		// 1) Calculer world « 2.5D » : écrasez la partie view de votre TransformSystem
		//    pour que l’objet reste “fixe” par rapport à l’écran.
		//    Par exemple, on veut un billboard centré :
		auto* tc = m_ECS->GetComponent<TransformComponent>(ent);
		if (!tc) return;
		// 1) Charger position écran et profondeur
		float px = tc->position.x;
		float py = tc->position.y;
		//float depth = tc->position.z; // distance fixe ou stockée par entité
		float depth = 2; // distance fixe ou stockée par entité


		// 2) Convertir (px,py,depth) -> position view‑space
		float ndcX = 2.0f * px / renderWidth - 1.0f;
		float ndcY = 1.0f - 2.0f * py / renderHeight;

		float fovY = XMConvertToRadians(75.0f); // compris entre : 0 < Fov < PI

		float tanH = tanf(fovY * 0.5f);
		float aspect = float(renderWidth) / float(renderHeight);


		XMVECTOR offsetView = XMVectorSet(
			ndcX * depth * tanH * aspect,
			ndcY * depth * tanH,
			0.0f, // pas besoin de z ici
			0.0f
		);

		XMVECTOR baseView = XMVectorSet(0.0f, 0.0f, depth, 1.0f);
		XMVECTOR posView = XMVectorAdd(baseView, offsetView);

		CameraComponent* camC = nullptr;

		ComponentMask camMask = (1ULL << CameraComponent::StaticTypeID | 1ULL << TransformComponent::StaticTypeID);
		m_ECS->ForEach(camMask, [&](Entity e)
			{
				camC = m_ECS->GetComponent<CameraComponent>(e);
				if (!camC) return;
			});


		XMMATRIX viewMatrix = XMLoadFloat4x4(&camC->viewMatrix);
		// 3) Ramener en espace monde
		XMMATRIX invView = XMMatrixInverse(nullptr, viewMatrix);
		XMVECTOR posWorld = XMVector4Transform(posView, invView);

		// 4) Charger rotation et échelle depuis votre TransformComponent
		XMVECTOR quat = XMLoadFloat4(&tc->rotation);       // votre quaternion
		XMMATRIX R = XMMatrixRotationQuaternion(quat);
		XMMATRIX S = XMMatrixScaling(tc->scale.x,
			tc->scale.y,
			tc->scale.z);

		// 5) Construire la matrice world complète
		XMMATRIX T = XMMatrixTranslationFromVector(posWorld);
		XMMATRIX world = S * R * T;




		// 2) Appliquer rotation billboarding si besoin
		//    (ex: XMMatrixRotationY(cameraYaw) pour un billboard Y‑aligné)
		//    On transposera pour le CB :
		ConstantBuffData cb;
		XMStoreFloat4x4(&cb.World, XMMatrixTranspose(world));
		cb.materialIndex = m_ECS
			->GetComponent<MeshComponent>(ent)->materialID;

		// 3) Copier et binder comme en 3D
		UINT entityOffset = ent.id * m_cbSize;
		UINT frameOffset = mp_graphicsDevice->GetFrameIndex() * INT64(m_allocatedEntityCount) * m_cbSize;
		UINT finalOffset = frameOffset + entityOffset;
		memcpy((BYTE*)m_mappedCBData + finalOffset, &cb, sizeof(ConstantBuffData));

		mp_commandManager->GetCommandList()->SetGraphicsRootConstantBufferView(
			/*slot b1*/ 1,
			m_cbTransformUpload->GetGPUVirtualAddress() + finalOffset);

		// 4) Draw
		auto& data = m_meshManager->GetMeshLib().Get(
			m_ECS->GetComponent<MeshComponent>(ent)->meshID);
		mp_commandManager->GetCommandList()->DrawIndexedInstanced(data.iSize, 1, data.iOffset, 0, 0);


		});
}

void Render3D::CreatePipeline()
{
	m_graphicsPipeline.CreatePipeline();
}

void Render3D::Release()
{
	mp_graphicsDevice = nullptr;
	delete mp_graphicsDevice;

	mp_descriptorManager = nullptr;
	delete mp_descriptorManager;

	mp_commandManager = nullptr;
	delete mp_commandManager;
}


//-----------------------------------------------------------------------------//
// Gestion du Constant Buffer (transform)
//-----------------------------------------------------------------------------//

bool Render3D::InitConstantBuffer()
{
	// Appelé lors de l'Init global de la classe
	m_frameCount = mp_graphicsDevice->GetFrameCount();
	// Démarre avec au moins 1 entité pour éviter taille zero
	m_allocatedEntityCount = std::max<UINT>(1, static_cast<UINT>(m_ECS->GetEntityCount()));
	AllocateCBUpload();
	return true;
}

void Render3D::AllocateCBUpload()
{
	// Calcule la taille totale
	UINT64 totalSize = UINT64(m_cbSize) * UINT64(m_allocatedEntityCount) * UINT64(m_frameCount);

	// Libère l'ancien buffer si présent
	if (m_cbTransformUpload)
	{
		m_cbTransformUpload->Unmap(0, nullptr);
		m_cbTransformUpload.Reset();
		m_mappedCBData = nullptr;
	}

	// Propriétés et description
	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC   bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(totalSize);

	// Création
	HRESULT hr = mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_cbTransformUpload));
	if (FAILED(hr))
	{
		throw std::runtime_error("Échec création constant buffer");
	}

	// Mapping CPU → GPU
	CD3DX12_RANGE readRange(0, 0);
	hr = m_cbTransformUpload->Map(0, &readRange, reinterpret_cast<void**>(&m_mappedCBData));
	if (FAILED(hr))
	{
		throw std::runtime_error("Échec mapping constant buffer");
	}
}

void Render3D::EnsureCapacity(UINT requiredEntityCount)
{
	if (requiredEntityCount <= m_allocatedEntityCount)
		return;
	// Double la capacité jusqu'à couvrir
	while (requiredEntityCount > m_allocatedEntityCount)
		m_allocatedEntityCount = std::max<UINT>(1, m_allocatedEntityCount * 2);
	AllocateCBUpload();
}

void Render3D::UpdateAndBindCB(Entity ent)
{
	// 1) Recuperer TransformComponent de l’entite
	auto* tc = m_ECS->GetComponent<TransformComponent>(ent);
	if (!tc)
		return;

	// 2) Calculer la matrice monde (XMMATRIX) depuis tc->position/rotation/scale
	XMMATRIX world = m_ECS->m_systemMgr.GetTransformSystem().worldMatrices[ent.id];

	// 3) Construire le struct ConstantBuffData
	ConstantBuffData cbData;
	XMStoreFloat4x4(&cbData.World, XMMatrixTranspose(world));

	cbData.materialIndex = m_ECS->GetComponent<MeshComponent>(ent)->materialID;

	// Calcul des offsets en utilisant m_allocatedEntityCount
	UINT64 entityOffset = UINT64(ent.id) * m_cbSize;
	UINT64 frameOffset = UINT64(mp_graphicsDevice->GetFrameIndex()) * UINT64(m_allocatedEntityCount) * m_cbSize;
	UINT64 finalOffset = frameOffset + entityOffset;

	//// 4) Copier les donnees dans le buffer upload mappe
	memcpy((BYTE*)m_mappedCBData + finalOffset, &cbData, sizeof(ConstantBuffData));

	// 5) Binder le constant buffer au root slot 1 (register b1) avec offset
	mp_commandManager->GetCommandList()->SetGraphicsRootConstantBufferView(/*rootParameterIndex=*/ 1, m_cbTransformUpload->GetGPUVirtualAddress() + finalOffset);
}
