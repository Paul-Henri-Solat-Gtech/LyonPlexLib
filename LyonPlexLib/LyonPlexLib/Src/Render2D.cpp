#include "pch.h"
#include "Render2D.h"
//#include "../../ExternalLib/DirectXTK12-main/Src/d3dx12.h"
//#include <DirectXMath.h>

bool Render2D::Init(HWND windowHandle, ECSManager* ECS, GraphicsDevice* gd, DescriptorManager* dm, CommandManager* cm, MeshManager* meshManager)
{
	m_ECS = ECS;
	mp_graphicsDevice = gd;
	mp_descriptorManager = dm;
	mp_commandManager = cm;
	m_meshManager = meshManager;


	m_graphicsPipeline.Init(mp_graphicsDevice, mp_descriptorManager, mp_commandManager);

	if (!InitConstantBuffer())
	{
		return false;
	}

	CreatePipeline();

	// Get la width et height du client (fenetre)
	RECT renderZone;
	GetClientRect(mp_graphicsDevice->GetWindow(), &renderZone);
	UINT renderWidth = renderZone.right - renderZone.left;
	UINT renderHeight = renderZone.bottom - renderZone.top;

	Resize(renderWidth, renderHeight);


	return true;
}

bool Render2D::InitConstantBuffer()
{

	// init du Projection buffer
	{
		CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
		CD3DX12_RESOURCE_DESC   desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(CB2D_Proj));
		if (FAILED(mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_cbProjUpload))))
			return false;

		CD3DX12_RANGE readRange(0, 0);
		if (FAILED(m_cbProjUpload->Map(0, &readRange, &m_mappedProj)))
			return false;
	}

	//// init du World constant buffer (object)
	//CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
	//UINT totalSize;
	//if (m_ECS->GetEntityCount() == 0)
	//	totalSize = m_cbSize;
	//else
	//	totalSize = m_cbSize * m_ECS->GetEntityCount();
	////CD3DX12_RESOURCE_DESC   desc = CD3DX12_RESOURCE_DESC::Buffer(totalSize);
	//CD3DX12_RESOURCE_DESC   desc = CD3DX12_RESOURCE_DESC::Buffer(m_cbSize/* * mp_graphicsDevice->GetFrameCount() * m_ECS->GetEntityCount()*/);
	//if (FAILED(mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_cbUpload))))
	//	return false;

	//CD3DX12_RANGE readRange(0, 0);
	//if (FAILED(m_cbUpload->Map(0, &readRange, &m_mappedCB)))
	//	return false;

	// Appele lors de l'Init global de la classe
	m_frameCount = mp_graphicsDevice->GetFrameCount();
	// Demarre avec au moins 1 entite pour eviter taille zero
	m_allocatedEntityCount = std::max<UINT>(1, static_cast<UINT>(m_ECS->GetEntityCount()));
	AllocateCBUpload();

	return true;
}


void Render2D::AllocateCBUpload()
{
	// Calcule la taille totale
	UINT64 totalSize = UINT64(m_cbSize) * UINT64(m_allocatedEntityCount) * UINT64(m_frameCount);

	// Libere l'ancien buffer si present
	if (m_cbUpload)
	{
		m_cbUpload->Unmap(0, nullptr);
		m_cbUpload.Reset();
		m_mappedCB = nullptr;
	}

	// Proprietes et description
	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC   bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(totalSize);

	// Creation
	HRESULT hr = mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_cbUpload));
	if (FAILED(hr))
	{
		throw std::runtime_error("Échec création constant buffer");
	}

	// Mapping CPU -> GPU
	CD3DX12_RANGE readRange(0, 0);
	hr = m_cbUpload->Map(0, &readRange, reinterpret_cast<void**>(&m_mappedCB));
	if (FAILED(hr))
	{
		throw std::runtime_error("Échec mapping constant buffer");
	}
}

void Render2D::EnsureCapacity(UINT requiredEntityCount)
{
	if (requiredEntityCount <= m_allocatedEntityCount)
		return;
	// Double la capacite jusqu'a couvrir
	while (requiredEntityCount > m_allocatedEntityCount)
		m_allocatedEntityCount = std::max<UINT>(1, m_allocatedEntityCount * 2);
	AllocateCBUpload();
}


void Render2D::Resize(int width, int height)
{
	// projection ortho de [0,w]×[0,h]
	using namespace DirectX;
	XMMATRIX newProj = XMMatrixOrthographicOffCenterLH(0.0f, float(width), float(height), 0.0f, 0.0f, 1.0f);

	CB2D_Proj projBuffer;
	XMStoreFloat4x4(&projBuffer.proj, XMMatrixTranspose(newProj));

	// ecrire dans le CB a offset 0
	memcpy(m_mappedProj, &projBuffer, sizeof(projBuffer));
}

void Render2D::RecordCommands()
{
	// Ensure size of global buffer
	UINT currentCount = static_cast<UINT>(m_ECS->GetEntityCount());
	EnsureCapacity(currentCount);

	auto& cmdList = mp_commandManager->GetCommandList();

	// 1) Pipeline 2D
	cmdList->SetGraphicsRootSignature(m_graphicsPipeline.GetRootSignature().Get());
	cmdList->SetPipelineState(m_graphicsPipeline.GetPipelineState().Get());

	// 3) CB projection (slot b0)
	cmdList->SetGraphicsRootConstantBufferView(0, m_cbProjUpload->GetGPUVirtualAddress());

	// 2) Heaps SRV + Sampler
	ID3D12DescriptorHeap* heaps[] = { mp_descriptorManager->GetSrvHeap()/*, mp_descriptorManager->GetSamplerHeap()*/ };
	cmdList->SetDescriptorHeaps(_countof(heaps), heaps);

	// 4) SRV table (slot t2), une seule fois
	D3D12_GPU_DESCRIPTOR_HANDLE srvBase = mp_descriptorManager->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart();
	cmdList->SetGraphicsRootDescriptorTable(2, srvBase);

	/*auto samplerBase = mp_descriptorManager->GetSamplerHeap()
		->GetGPUDescriptorHandleForHeapStart();
	cmdList->SetGraphicsRootDescriptorTable(3, samplerBase);*/

	// 5) IA setup (quad global)
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	cmdList->IASetVertexBuffers(0, 1, &m_meshManager->GetGlobalVBView());
	cmdList->IASetIndexBuffer(&m_meshManager->GetGlobalIBView());



	RECT renderZone;
	GetClientRect(mp_graphicsDevice->GetWindow(), &renderZone);
	UINT renderWidth = renderZone.right - renderZone.left;
	UINT renderHeight = renderZone.bottom - renderZone.top;
	D3D12_VIEWPORT vp = {
	0.0f, 0.0f,
	renderWidth,
	renderHeight,
	0.0f, 1.0f
	};
	CD3DX12_RECT sc = CD3DX12_RECT(0, 0, renderWidth, renderHeight);
	cmdList->RSSetViewports(1, &vp);
	cmdList->RSSetScissorRects(1, &sc);



	// 7) Boucle sur tes quads (MeshComponent)
	ComponentMask mask = (1ULL << MeshComponent::StaticTypeID) | (1ULL << Type_2D::StaticTypeID);
	m_ECS->ForEach(mask, [&](Entity ent) {
		auto* tc = m_ECS->GetComponent<TransformComponent>(ent);
		if (!tc)
			return;

		// 7a) Recupere la world matrix calculee par ton TransformSystem
		XMMATRIX world = m_ECS->m_systemMgr.GetTransformSystem().worldMatrices[ent.id];

		//// 7b) Remplit le CB identique au 3D
		CB2D_World cbData;
		XMStoreFloat4x4(&cbData.world, XMMatrixTranspose(world));

		auto* mc = m_ECS->GetComponent<MeshComponent>(ent);
		cbData.materialIndex = mc->materialID;

		////UpdateCbParams();

		// 7c) Calcul des offsets identique au 3D
		UINT entityOffset = ent.id * m_cbSize;
		UINT frameOffset = mp_graphicsDevice->GetFrameIndex() * INT64(m_allocatedEntityCount) * m_cbSize;
		UINT finalOffset = frameOffset + entityOffset;

		// 7d) Copier dans le CB upload
		memcpy((BYTE*)m_mappedCB +/*entityOffset*/ finalOffset, &cbData, sizeof(CB2D_World /*cbData*/));

		// 7e) Bind CB world (slot b1)
		cmdList->SetGraphicsRootConstantBufferView(1, m_cbUpload->GetGPUVirtualAddress() + /*entityOffset*/ finalOffset);
		
		UINT descSize = mp_descriptorManager->GetSrvDescriptorSize();
		D3D12_GPU_DESCRIPTOR_HANDLE handle = srvBase;
		handle.ptr += cbData.materialIndex * descSize;

		cmdList->SetGraphicsRootDescriptorTable(/*rootParamIndex=*/2, handle);

		// 7f) Draw
		const MeshData& quad = m_meshManager->GetMeshLib().Get(mc->meshID);
		cmdList->DrawIndexedInstanced(quad.iSize, 1, quad.iOffset, /*quad.vOffset*/0, 0);
		});
}

void Render2D::CreatePipeline()
{
	m_graphicsPipeline.CreatePipeline2D();
}

void Render2D::Release()
{
}
