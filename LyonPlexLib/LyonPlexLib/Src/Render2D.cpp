//#include "Render2D.h"
#include "pch.h"
////#include "../../ExternalLib/DirectXTK12-main/Src/d3dx12.h"
////#include <DirectXMath.h>
//
//bool Render2D::Init(HWND windowHandle, ECSManager* ECS, GraphicsDevice* gd, DescriptorManager* dm, CommandManager* cm)
//{
//	m_ECS = ECS;
//	mp_graphicsDevice = gd;
//	mp_descriptorManager = dm;
//	mp_commandManager = cm;
//
//	m_textureManager = new TextureManager;
//	m_textureManager->Init(gd, dm);
//
//	m_graphicsPipeline.Init(mp_graphicsDevice, mp_descriptorManager, mp_commandManager);
//	m_meshManager.Init(mp_graphicsDevice);
//
//	if (InitConstantBuffer()) return false;
//	
//	//UpdateCbParams();
//
//	CreatePipeline();
//
//	return true;
//}
//
//bool Render2D::InitConstantBuffer()
//{
//
//	// init du Projection buffer
//	{
//		CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
//		CD3DX12_RESOURCE_DESC   desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(CB2D_Proj));
//		if (FAILED(mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_cbProjUpload))))
//			return false;
//
//		CD3DX12_RANGE readRange(0, 0);
//		if (FAILED(m_cbProjUpload->Map(0, &readRange, &m_mappedProj)))
//			return false;
//	}
//
//	// init du World constant buffer (object)
//	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
//	CD3DX12_RESOURCE_DESC   desc = CD3DX12_RESOURCE_DESC::Buffer(m_cbSize * mp_graphicsDevice->GetFrameCount() * m_ECS->GetEntityCount());
//	if (FAILED(mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_cbUpload))))
//		return false;
//
//	CD3DX12_RANGE readRange(0, 0);
//	if (FAILED(m_cbUpload->Map(0, &readRange, &m_mappedCB)))
//		return false;
//
//	return true;
//}
//
//void Render2D::Resize(int width, int height)
//{
//	// projection ortho de [0,w]×[0,h]
//	using namespace DirectX;
//	XMMATRIX newProj = XMMatrixOrthographicOffCenterLH(0.0f, float(width), float(height), 0.0f, 0.0f, 1.0f);
//
//	CB2D_Proj projBuffer;
//	XMStoreFloat4x4(&projBuffer.proj, XMMatrixTranspose(newProj));
//
//	// ecrire dans le CB a offset 0
//	memcpy(m_mappedProj, &projBuffer, sizeof(projBuffer));
//}
//
//void Render2D::UpdateCbParams()
//{
//	//UINT m_entityCount = m_ECS->GetEntityCount();
//	//UINT m_frameCount = mp_graphicsDevice->GetFrameCount();
//	//UINT m_totalSize = m_cbSize * m_entityCount * m_frameCount;
//}
//
//void Render2D::RecordCommands()
//{
//	auto cmdList = mp_commandManager->GetCommandList();
//
//	// 1) Pipeline 2D
//	cmdList->SetGraphicsRootSignature(m_graphicsPipeline.GetRootSignature().Get());
//	cmdList->SetPipelineState(m_graphicsPipeline.GetPipelineState().Get());
//
//	// 2) Heaps SRV + Sampler
//	ID3D12DescriptorHeap* heaps[] = { mp_descriptorManager->GetSrvHeap(), mp_descriptorManager->GetSamplerHeap() };
//	cmdList->SetDescriptorHeaps(_countof(heaps), heaps);
//
//	// 3) CB projection (slot b0)
//	cmdList->SetGraphicsRootConstantBufferView(0, m_cbProjUpload->GetGPUVirtualAddress());
//
//	// 4) SRV?table (slot t2), une seule fois
//	D3D12_GPU_DESCRIPTOR_HANDLE srvBase = mp_descriptorManager->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart();
//	cmdList->SetGraphicsRootDescriptorTable(2, srvBase);
//
//	// 5) IA setup (quad global)
//	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	cmdList->IASetVertexBuffers(0, 1, &m_meshManager.GetGlobalVBView());
//	cmdList->IASetIndexBuffer(&m_meshManager.GetGlobalIBView());
//
//	// 6) Clear RTV (pas de DSV)
//	UINT frameIdx = mp_graphicsDevice->GetFrameIndex();
//	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(mp_descriptorManager->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(), frameIdx, mp_descriptorManager->GetRtvDescriptorSize());
//	const float clearColor[] = { 0, 0, 0, 1.0f };
//	cmdList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
//	cmdList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
//
//	// 7) Boucle sur tes quads (MeshComponent)
//	ComponentMask mask = (1ULL << MeshComponent::StaticTypeID) | (1ULL << Type_2D::StaticTypeID);
//	m_ECS->ForEach(mask, [&](Entity ent) {
//		auto* mc = m_ECS->GetComponent<MeshComponent>(ent);
//
//		// 7a) Recupere la world matrix calculee par ton TransformSystem
//		XMMATRIX world = m_ECS->m_systemMgr.GetTransformSystem().worldMatrices[ent.id];
//
//		// 7b) Remplit le CB identique au 3D
//		CB2D_World cbData;
//		XMStoreFloat4x4(&cbData.world, XMMatrixTranspose(world));
//		cbData.materialIndex = mc->materialID;
//
//		//UpdateCbParams();
//		
//		// 7c) Calcul des offsets identique au 3D
//		UINT entityOffset = ent.id * m_cbSize;
//		UINT frameOffset = mp_graphicsDevice->GetFrameIndex() * m_ECS->GetEntityCount() * m_cbSize;
//		UINT finalOffset = frameOffset + entityOffset;
//
//		// 7d) Copier dans le CB upload
//		memcpy((BYTE*)m_mappedCB + finalOffset, &cbData, sizeof(cbData));
//
//		// 7e) Bind CB world (slot b1)
//		cmdList->SetGraphicsRootConstantBufferView(1, m_cbUpload->GetGPUVirtualAddress() + finalOffset);
//
//		// 7f) Draw
//		const MeshData& quad = m_meshManager.GetMeshLib().Get(mc->meshID);
//		cmdList->DrawIndexedInstanced(quad.iSize, 1, quad.iOffset, 0, 0);
//		});
//}
//
//void Render2D::CreatePipeline()
//{
//	 m_graphicsPipeline.CreatePipeline2D();
//}
//
//void Render2D::Release()
//{
//	delete m_textureManager;
//	m_textureManager = nullptr;
//}
