#include "pch.h"
#include "Render3D.h"

bool Render3D::Init(HWND windowHandle, ECSManager* ECS, GraphicsDevice* graphicsDevice, DescriptorManager* descriptorManager, CommandManager* commandManager, MeshManager* meshManager)
{
	m_ECS = ECS;

	//m_textureManager = new TextureManager;



	mp_graphicsDevice = graphicsDevice;
	mp_descriptorManager = descriptorManager;
	mp_commandManager = commandManager;
	m_windowWP = windowHandle;
	m_meshManager = meshManager;

	m_graphicsPipeline.Init(mp_graphicsDevice, mp_descriptorManager, mp_commandManager);
	//m_meshManager.Init(mp_graphicsDevice);

	InitConstantBuffer();
	UpdateCbParams();

	CreatePipeline();

	// Ce bloc permet de verifier si un chemin/fichier existe
	/*DWORD len = GetFullPathNameW(L"..\\LyonPlexLib\\Ressources\\PixelShader.hlsl", 0, nullptr, nullptr);
	std::wstring fullpath(len, L'\0');
	GetFullPathNameW(L"..\\LyonPlexLib\\Ressources\\PixelShader.hlsl", len, fullpath.data(), nullptr);
	MessageBoxW(nullptr, fullpath.c_str(), L"Full path", MB_OK);*/

	//m_textureManager->LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	////m_textureManager->LoadTexture("../LyonPlexLib/Ressources/Test2.avif");
	//m_textureManager->LoadTexture("../LyonPlexLib/Ressources/Test.png");
	//m_textureManager->LoadTexture("../LyonPlexLib/Ressources/TestBRAS.png");

	return true;
}

void Render3D::Resize(int w, int h)
{
	// Pas besoin ?
}

void Render3D::RecordCommands()
{

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

	//UINT frameIdx = mp_graphicsDevice->GetFrameIndex();
	//// Clear RTV
	//CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
	//	mp_descriptorManager->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(),
	//	frameIdx,
	//	mp_descriptorManager->GetRtvDescriptorSize()
	//);
	//const float clearColor[] = { 0.1f, 0.2f, 0.3f, 1.0f };
	//mp_commandManager->GetCommandList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

	//// Clear DSV
	//CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(mp_descriptorManager->GetDsvHeap()->GetCPUDescriptorHandleForHeapStart(), frameIdx, mp_descriptorManager->GetDsvDescriptorSize());
	//mp_commandManager->GetCommandList()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH,  1.0f, 0, 0, nullptr);

	//// F) OMSetRenderTargets (RTV + DSV)
	//mp_commandManager->GetCommandList()->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);


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

	ComponentMask renderMask = (1ULL << MeshComponent::StaticTypeID) | (1ULL << Type_3D::StaticTypeID);
	//ComponentMask renderMask = (1ULL << MeshComponent::StaticTypeID) ;
	// Boucle sur toutes les entity a dessiner (componentMask MeshComponent)
	m_ECS->ForEach(renderMask, [&](Entity ent)
		{
			//const Material& mat = materialLib.Get(m->materialID);

			UpdateAndBindCB(ent);

			MeshComponent* meshComp = m_ECS->GetComponent<MeshComponent>(ent);
			uint32_t matID = meshComp->materialID;


			const MeshData& data = m_meshManager->GetMeshLib().Get(meshComp->meshID);
			mp_commandManager->GetCommandList()->DrawIndexedInstanced(
				data.iSize,      // nombre d’indices
				1,
				data.iOffset,    // offset dans le buffer d’indices
				0,				// BaseVertexLocation toujours = 0 ?
				0
			);
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

		// 2) Convertir (px,py,depth) → position view‑space
		float ndcX = 2.0f * px / 800 - 1.0f;
		float ndcY = 1.0f - 2.0f * py / 600;

		float fovY = XMConvertToRadians(75.0f); // compris entre : 0 < Fov < PI

		float tanH = tanf(fovY * 0.5f);
		float aspect = float(renderWidth) / float(renderHeight);


		/*XMVECTOR posView = XMVectorSet(
			ndcX * depth * tanH * aspect,
			ndcY * depth * tanH,
			depth,
			1.0f
		);*/

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
		UpdateCbParams();
		UINT entityOffset = ent.id * m_cbSize;
		UINT frameOffset = mp_graphicsDevice->GetFrameIndex()
			* m_entityCount * m_cbSize;
		UINT finalOffset = frameOffset + entityOffset;
		memcpy((BYTE*)m_mappedCBData + finalOffset, &cb, sizeof(cb));
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
	// Definir les proprietes du heap « upload »
	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);

	// Decrire un buffer de m_cbSize octets
	CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(m_cbSize/* * mp_graphicsDevice->GetFrameCount() * m_ECS->GetEntityCount()*/);

	// Creer le buffer upload
	HRESULT hr = mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_cbTransformUpload));
	if (FAILED(hr))
	{
		return false;
	}

	// 5) Mapper une seule fois pour recuperer l’adresse CPU
	CD3DX12_RANGE readRange(0, 0); // on ne lit jamais CPU→GPU
	hr = m_cbTransformUpload->Map(0, &readRange, reinterpret_cast<void**>(&m_mappedCBData));
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

void Render3D::UpdateCbParams()
{
	UINT m_entityCount = static_cast<UINT>(m_ECS->GetEntityCount());
	UINT m_frameCount = mp_graphicsDevice->GetFrameCount();
	UINT totalSize = m_cbSize * m_entityCount * m_frameCount;
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

	MeshComponent* meshComp = m_ECS->GetComponent<MeshComponent>(ent);
	cbData.materialIndex = meshComp->materialID;

	UpdateCbParams();
	UINT entityOffset = ent.id * m_cbSize;
	UINT frameOffset = mp_graphicsDevice->GetFrameIndex() * m_entityCount * m_cbSize;
	UINT finalOffset = frameOffset + entityOffset;

	//// 4) Copier les donnees dans le buffer upload mappe
	memcpy((BYTE*)m_mappedCBData + finalOffset, &cbData, sizeof(ConstantBuffData));

	// 5) Binder le constant buffer au root slot 1 (register b1) avec offset
	mp_commandManager->GetCommandList()->SetGraphicsRootConstantBufferView(/*rootParameterIndex=*/ 1, m_cbTransformUpload->GetGPUVirtualAddress() + finalOffset);
}
