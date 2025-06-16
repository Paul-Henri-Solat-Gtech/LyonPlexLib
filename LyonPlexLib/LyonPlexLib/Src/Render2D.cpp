#include "pch.h"
#include "Render2D.h"
//#include "../../ExternalLib/DirectXTK12-main/Src/d3dx12.h"
//#include <DirectXMath.h>

bool Render2D::Init(HWND windowHandle, ECSManager* ECS, GraphicsDevice* gd, DescriptorManager* dm, CommandManager* cm)
{
	m_ECS = ECS;
	mp_graphicsDevice = gd;
	mp_descriptorManager = dm;
	mp_commandManager = cm;

	m_textureManager = new TextureManager;
	m_textureManager->Init(gd, dm);

	m_graphicsPipeline.Init(mp_graphicsDevice, mp_descriptorManager, mp_commandManager);
	m_meshManager.Init(mp_graphicsDevice);

	if (!InitConstantBuffer())
	{
		return false;
	}
	CreatePipeline();

	//m_textureManager->LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	//m_textureManager->LoadTexture("../LyonPlexLib/Ressources/Test2.avif");
	m_textureManager->LoadTexture("../LyonPlexLib/Ressources/Test.png");


	Resize(800, 600);
	//UpdateCbParams();


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

	// init du World constant buffer (object)
	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
	UINT totalSize;
	if (m_ECS->GetEntityCount() == 0)
		totalSize = m_cbSize;
	else
		totalSize = m_cbSize * m_ECS->GetEntityCount();
	//CD3DX12_RESOURCE_DESC   desc = CD3DX12_RESOURCE_DESC::Buffer(totalSize);
	CD3DX12_RESOURCE_DESC   desc = CD3DX12_RESOURCE_DESC::Buffer(m_cbSize/* * mp_graphicsDevice->GetFrameCount() * m_ECS->GetEntityCount()*/);
	if (FAILED(mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_cbUpload))))
		return false;

	CD3DX12_RANGE readRange(0, 0);
	if (FAILED(m_cbUpload->Map(0, &readRange, &m_mappedCB)))
		return false;



	// Temporary upload buffer for triangle test (vertices + indices)
	{
		struct Vertex {
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT4 color;
			DirectX::XMFLOAT2 uv;
		};

		const UINT vertsSize = 3 * sizeof(Vertex);
		const UINT idxsSize = 3 * sizeof(uint16_t);
		CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
		CD3DX12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(vertsSize + idxsSize);
		mp_graphicsDevice->GetDevice()->CreateCommittedResource(
			&heapProps, D3D12_HEAP_FLAG_NONE, &desc,
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
			IID_PPV_ARGS(&m_tempUploadBuffer));
		CD3DX12_RANGE readRange(0, 0);
		m_tempUploadBuffer->Map(0, &readRange, &m_mappedTemp);
	}

	return true;
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

void Render2D::UpdateCbParams()
{
	//UINT m_entityCount = m_ECS->GetEntityCount();
	//UINT m_frameCount = mp_graphicsDevice->GetFrameCount();
	//UINT m_totalSize = m_cbSize * m_entityCount * m_frameCount;
}

void Render2D::RecordCommands()
{
	auto cmdList = mp_commandManager->GetCommandList();

	// 1) Pipeline 2D
	cmdList->SetGraphicsRootSignature(m_graphicsPipeline.GetRootSignature().Get());
	cmdList->SetPipelineState(m_graphicsPipeline.GetPipelineState().Get());

	// 2) Heaps SRV + Sampler
	ID3D12DescriptorHeap* heaps[] = { mp_descriptorManager->GetSrvHeap(), mp_descriptorManager->GetSamplerHeap() };
	cmdList->SetDescriptorHeaps(_countof(heaps), heaps);

	// 3) CB projection (slot b0)
	cmdList->SetGraphicsRootConstantBufferView(0, m_cbProjUpload->GetGPUVirtualAddress());

	// 4) SRV table (slot t2), une seule fois
	D3D12_GPU_DESCRIPTOR_HANDLE srvBase = mp_descriptorManager->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart();
	cmdList->SetGraphicsRootDescriptorTable(2, srvBase);

	auto samplerBase = mp_descriptorManager->GetSamplerHeap()
		->GetGPUDescriptorHandleForHeapStart();
	cmdList->SetGraphicsRootDescriptorTable(3, samplerBase);

	// 5) IA setup (quad global)
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	cmdList->IASetVertexBuffers(0, 1, &m_meshManager.GetGlobalVBView());
	cmdList->IASetIndexBuffer(&m_meshManager.GetGlobalIBView());

	//// 6) Clear RTV (pas de DSV)
	//UINT frameIdx = mp_graphicsDevice->GetFrameIndex();
	//CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(mp_descriptorManager->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(), frameIdx, mp_descriptorManager->GetRtvDescriptorSize());
	//const float clearColor[] = { 10, 0, 0, 1.0f };
	//cmdList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	//cmdList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);


	RECT rc;
	FLOAT width = 0;
	FLOAT height = 0;
	if (GetClientRect(mp_graphicsDevice->GetWindow(), &rc))
	{
		width = static_cast<FLOAT>(rc.right - rc.left);   // largeur de la zone client
		height = static_cast<FLOAT>(rc.bottom - rc.top);    // hauteur de la zone client
	}
	D3D12_VIEWPORT vp = {
	0.0f, 0.0f,
	width,
	height,
	0.0f, 1.0f
	};
	CD3DX12_RECT sc = CD3DX12_RECT(0, 0, width, height);
	cmdList->RSSetViewports(1, &vp);
	cmdList->RSSetScissorRects(1, &sc);

	// TEST : draw a hard?coded triangle, bypass MeshManager
	struct Vertex { DirectX::XMFLOAT3 pos; DirectX::XMFLOAT4 color; DirectX::XMFLOAT2 uv; };
	Vertex triVerts[3] = {
		// Sommet 0
		{ { 0.0f, 0.0f, 0.0f }, {1, 0, 0, 1}, {0, 0} },
		// Sommet 1
		{ { 200.0f, 0.0f, 0.0f }, {0, 1, 0, 1}, {1, 0} },
		// Sommet 2
		{ { 100.0f, 200.0f, 0.0f }, {0, 0, 1, 1}, {0.5f, 1} }
	};
	
	//Vertex triVerts[3] = {
	//	{{-500,  500, 0.0f}, {1, 0, 0, 1}, {0, 0}},
	//	{{ 500,  500, 0.0f}, {0, 1, 0, 1}, {1, 0}},
	//	{{ 100.0f, -500, 0.0f}, {0, 0, 1, 1}, {0.5f, 1}}
	//};
	/*
	Vertex triVerts[3] = {
		{{-0.5f,  0.5f, 0.0f}, {1, 0, 0, 1}, {0, 0}},
		{{ 0.5f,  0.5f, 0.0f}, {0, 1, 0, 1}, {1, 0}},
		{{ 0.0f, -0.5f, 0.0f}, {0, 0, 1, 1}, {0.5f, 1}}
	};*/
	uint16_t triIdxs[3] = { 0, 1, 2 };

	// Copy into temp upload buffer (created & mapped in InitConstantBuffers)
	memcpy(m_mappedTemp, triVerts, sizeof(triVerts));
	memcpy((BYTE*)m_mappedTemp + sizeof(triVerts), triIdxs, sizeof(triIdxs));

	// Build VB + IB views
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	vbView.BufferLocation = m_tempUploadBuffer->GetGPUVirtualAddress();
	vbView.StrideInBytes = sizeof(Vertex);
	vbView.SizeInBytes = sizeof(triVerts);
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	D3D12_INDEX_BUFFER_VIEW ibView = {};
	ibView.BufferLocation = m_tempUploadBuffer->GetGPUVirtualAddress() + sizeof(triVerts);
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeof(triIdxs);
	cmdList->IASetIndexBuffer(&ibView);

	// Upload a default world matrix (identity) + first texture
	CB2D_World cbw;
	XMStoreFloat4x4(&cbw.world, XMMatrixTranspose(XMMatrixIdentity()));
	cbw.materialIndex = 0;
	memcpy(m_mappedCB, &cbw, sizeof(cbw));
	cmdList->SetGraphicsRootConstantBufferView(1, m_cbUpload->GetGPUVirtualAddress());

	// Finally draw the triangle
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	cmdList->DrawIndexedInstanced(3, 1, 0, 0, 0);



}

void Render2D::CreatePipeline()
{
	m_graphicsPipeline.CreatePipeline2D();
}

void Render2D::Release()
{
	delete m_textureManager;
	m_textureManager = nullptr;
}
