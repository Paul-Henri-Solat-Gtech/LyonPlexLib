#include "Render2D.h"
#include "../../ExternalLib/DirectXTK12-main/Src/d3dx12.h"
#include <DirectXMath.h>

bool Render2D::Init(HWND windowHandle, ECSManager* ECS, GraphicsDevice* gd, DescriptorManager* dm, CommandManager* cm)
{
	m_ECS = ECS;
	mp_graphicsDevice = gd;
	mp_descriptorManager = dm;
	mp_commandManager = cm;

	m_textureManager = new TextureManager;
	m_textureManager->Init(gd, dm);

	// initialise ton SpriteRenderer (crée quad VB/IB, réserve instancing)
	//m_spriteRenderer.Init(gd, dm);
	m_graphicsPipeline.Init(mp_graphicsDevice, mp_descriptorManager, mp_commandManager);
	m_meshManager.Init(mp_graphicsDevice);

	InitConstantBuffer();
	UpdateCbParams();


	// init du constant buffer
	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC   desc = CD3DX12_RESOURCE_DESC::Buffer(m_cbSize);
	if (FAILED(gd->GetDevice()->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_cbUpload))))
		return false;

	CD3DX12_RANGE readRange(0, 0);
	if (FAILED(m_cbUpload->Map(0, &readRange, &m_mappedCB)))
		return false;

	return true;
}


void Render2D::Resize(int width, int height)
{
	// projection ortho de [0,w]×[0,h]
	using namespace DirectX;
	XMMATRIX newProj = XMMatrixOrthographicOffCenterLH(0.0f, float(width), float(height), 0.0f, 0.0f, 1.0f);
	XMStoreFloat4x4(&m_projMat, XMMatrixTranspose(newProj));

	// écrire dans le CB à offset 0
	memcpy(m_mappedCB, &m_projMat, sizeof(m_projMat));
}


//void Render2D::RecordCommands()
//{
//	//auto cmdList = mp_commandManager->GetCommandList();
//
//	//// 1) pipeline 2D
//	//cmdList->SetGraphicsRootSignature(m_graphicsPipeline.GetRootSignature().Get());
//	//cmdList->SetPipelineState(m_graphicsPipeline.GetPipelineState().Get());
//
//	//// 2) bind constant buffer view (projection) au slot b0
//	//cmdList->SetGraphicsRootConstantBufferView(
//	//    /*rootParamIndex=*/0,
//	//    m_cbUpload->GetGPUVirtualAddress());
//
//	//// 3) descriptor heaps (textures + samplers)
//	//ID3D12DescriptorHeap* heaps[] = {
//	//    mp_descriptorManager->GetSrvHeap(),
//	//    mp_descriptorManager->GetSamplerHeap()
//	//};
//	//cmdList->SetDescriptorHeaps(_countof(heaps), heaps);
//	//cmdList->SetGraphicsRootDescriptorTable(
//	//    /*rootParamIndex=*/1,
//	//    mp_descriptorManager->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart());
//
//	//// 4) préparer le SpriteRenderer (par ex. vider la liste d’instances)
//	////m_spriteRenderer.Begin();
//
//	//// itérer sur les entités qui ont un SpriteComponent
//	//ComponentMask mask = (1ULL << SpriteComponent::StaticTypeID);
//	//m_ECS->ForEach(mask, [&](Entity ent) {
//	//    auto* sc = m_ECS->GetComponent<SpriteComponent>(ent);
//	//    // world transform 2D (x, y, scale, rotation)
//	//    DirectX::XMFLOAT4X4 world = Compute2DWorldMatrix(sc);
//	//    DirectX::XMFLOAT4   tint = sc->tint;
//
//	//    // ajoute à ton batch de sprites
//	//    m_spriteRenderer.Draw(
//	//        sc->textureID,
//	//        world,
//	//        tint);
//	//    });
//
//	//// 5) envoie les draw calls
//	//m_spriteRenderer.FlushAndDraw(cmdList);
//
//	auto cmdList = mp_commandManager->GetCommandList();
//
//	// ————————————————————————————————
//	// 1) Bind pipeline 2D
//	cmdList->SetGraphicsRootSignature(m_graphicsPipeline.GetRootSignature().Get());
//	cmdList->SetPipelineState(m_graphicsPipeline.GetPipelineState().Get());
//
//	// 2) Bind descriptor heaps SRV + sampler
//	ID3D12DescriptorHeap* heaps[] = {mp_descriptorManager->GetSrvHeap(), mp_descriptorManager->GetSamplerHeap()};
//	cmdList->SetDescriptorHeaps(_countof(heaps), heaps);
//
//	// 3) Bind CB projection (slot b0, remplace la CB Camera du 3D)
//	cmdList->SetGraphicsRootConstantBufferView(/*rootParam=*/0, m_cbProjUpload->GetGPUVirtualAddress());
//
//	// 4) Setup IA avec ton quad global comme pour le 3D
//	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	cmdList->IASetVertexBuffers(0, 1, &m_meshManager.GetGlobalVBView());
//	cmdList->IASetIndexBuffer(&m_meshManager.GetGlobalIBView());
//
//	// ————————————————————————————————
//	// 5) Pas de clear DSV ni depth-stencil pour le 2D,
//	//    on ne fait QUE le RTV
//	UINT frameIdx = mp_graphicsDevice->GetFrameIndex();
//	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle( mp_descriptorManager->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(), frameIdx, mp_descriptorManager->GetRtvDescriptorSize());
//	const float clearColor[] = { 0, 0, 0, 1.0f };
//	cmdList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
//	cmdList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
//
//	// 6) Pour chaque entité 2D (MeshComponent = quad + materialID)
//	ComponentMask mask = 1ULL << MeshComponent::StaticTypeID;
//	m_ECS->ForEach(mask, [&](Entity ent)
//		{
//			auto* mc = m_ECS->GetComponent<MeshComponent>(ent);
//
//			// 6a) calculer ta matrice world 2D (X,Y,scale,rot)
//			XMFLOAT4X4 world = Compute2DWorld(mc);
//			CB2D_World cbData;
//			XMStoreFloat4x4(&cbData.World, XMMatrixTranspose(XMLoadFloat4x4(&world)));
//			cbData.materialIndex = mc->materialID;
//			// copier au bon offset dans m_mappedCBData (comme en 3D)
//			size_t offset = /* comme UpdateAndBindCB(en 3D) */;
//
//			memcpy((BYTE*)m_mappedCB + offset, &cbData, sizeof(cbData));
//
//			// 6b) bind CB world (slot b1)
//			cmdList->SetGraphicsRootConstantBufferView(
//				/*rootParam=*/1,
//				m_cbUpload->GetGPUVirtualAddress() + offset
//			);
//
//			// 6c) bind SRV pour ce materialID (slot t2)
//			D3D12_GPU_DESCRIPTOR_HANDLE srv =
//				mp_descriptorManager->GetSrvHandleForIndex(mc->materialID);
//			cmdList->SetGraphicsRootDescriptorTable(/*rootParam=*/2, srv);
//
//			// 6d) draw le quad
//			const MeshData& quad = m_meshManager.GetMeshLib().Get(mc->meshID);
//			cmdList->DrawIndexedInstanced(quad.iSize, 1, quad.iOffset, 0, 0);
//		});
//}

void Render2D::RecordCommands()
{
    auto cmdList = mp_commandManager->GetCommandList();

    // 1) Bind pipeline 2D
    cmdList->SetGraphicsRootSignature(m_graphicsPipeline.GetRootSignature().Get());
    cmdList->SetPipelineState(m_graphicsPipeline.GetPipelineState().Get());

    // 2) Bind heaps SRV + sampler
    ID3D12DescriptorHeap* heaps[] = {
        mp_descriptorManager->GetSrvHeap(),
        mp_descriptorManager->GetSamplerHeap()
    };
    cmdList->SetDescriptorHeaps(_countof(heaps), heaps);

    // 3) Bind CB projection (slot b0)
    cmdList->SetGraphicsRootConstantBufferView(
        /*rootParam=*/0,
        m_cbProjUpload->GetGPUVirtualAddress()
    );

    // 4) Bind **une seule fois** la SRV-table (slot t2)
    D3D12_GPU_DESCRIPTOR_HANDLE srvBase =
        mp_descriptorManager->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart();
    cmdList->SetGraphicsRootDescriptorTable(/*rootParam=*/2, srvBase);

    // 5) IA setup (quad)
    cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    cmdList->IASetVertexBuffers(0, 1, &m_meshManager.GetGlobalVBView());
    cmdList->IASetIndexBuffer(&m_meshManager.GetGlobalIBView());

    // 6) Clear RTV (pas de DSV pour le 2D)
    UINT frameIdx = mp_graphicsDevice->GetFrameIndex();
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
        mp_descriptorManager->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(),
        frameIdx,
        mp_descriptorManager->GetRtvDescriptorSize()
    );
    const float clearColor[] = { 0, 0, 0, 1.0f };
    cmdList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
    cmdList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

    // 7) Boucle sur tes sprites (MeshComponent)
    ComponentMask mask = 1ULL << MeshComponent::StaticTypeID;
    m_ECS->ForEach(mask, [&](Entity ent) {
        auto* mc = m_ECS->GetComponent<MeshComponent>(ent);

        // Calculer la world matrix 2D
        // C’est l’équivalent de UpdateAndBindCB, mais ici on
        // stocke juste la World (et le materialIndex) dans le CB.
        CB2D_World cbData;
        {
            // Compute2DWorld renvoie XMFLOAT4X4 construite depuis mc->position/scale/rot
            XMFLOAT4X4 world = Compute2DWorld(ent);
            XMStoreFloat4x4(&cbData.World,
                XMMatrixTranspose(XMLoadFloat4x4(&world)));
            cbData.materialIndex = mc->materialID;
        }

        // Copier dans le CB upload (exactement comme en 3D)
        size_t offset = /* m_frameCount* m_entityCount + ent.id etc. */;
        memcpy((BYTE*)m_mappedCB + offset, &cbData, sizeof(cbData));

        // 8) Bind CB world (slot b1)
        cmdList->SetGraphicsRootConstantBufferView(
            /*rootParam=*/1,
            m_cbUpload->GetGPUVirtualAddress() + offset
        );

        // 9) Draw le quad
        const MeshData& quad = m_meshManager.GetMeshLib().Get(mc->meshID);
        cmdList->DrawIndexedInstanced(quad.iSize, 1, quad.iOffset, 0, 0);
        });
}

void Render2D::CreatePipeline()
{
	// appellera, plus tard,
	// m_graphicsPipeline.CreatePipeline2D();
	// (on verra comment l’implémenter dans GraphicsPipeline)
}

XMFLOAT4X4 Render2D::Compute2DWorld(Entity ent)
{
    auto* tc = m_ECS->GetComponent<TransformComponent>(ent);
    if (!tc)
        return;

    // translation
    XMMATRIX T = XMMatrixTranslation(tc->position.x, tc->position.y, 0.0f);
    // rotation autour de Z
    XMMATRIX R = XMMatrixRotationZ(0); // VALEUR PAR DEFAUT A MODIFIER
    // scale
    XMMATRIX S = XMMatrixScaling(tc->scale.x, tc->scale.y, 1.0f);

    XMMATRIX W = S * R * T;
    XMFLOAT4X4 w4x4;
    XMStoreFloat4x4(&w4x4, W);
    return w4x4;
}