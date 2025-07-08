//#include "pch.h"
//// LightSystem.cpp
//#include "LightSystem.h"
////#include <d3dx12.h>
//
//void LightSystem::InitVariables(GraphicsDevice* device, CommandManager* cmdMgr)
//{
//	mp_device = device;
//	mp_cmdMgr = cmdMgr;
//}
//
//void LightSystem::Init(ECSManager& ecs)
//{
//
//	//// créer le buffer GPU de taille sizeof(LightBuffer)
//	//UINT totalSize = sizeof(m_cpuLights) + sizeof(UINT);
//	//CD3DX12_HEAP_PROPERTIES hp(D3D12_HEAP_TYPE_UPLOAD);
//	//auto desc = CD3DX12_RESOURCE_DESC::Buffer(totalSize);
//
//	////THROW_IF_FAILED(dev->GetDevice()->CreateCommittedResource(&hp, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&_cb)));
//	//dev->GetDevice()->CreateCommittedResource(&hp, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_constantBuffer));
//	//m_constantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_cpuLights));
//	// 
//	
//	 
//	
//	//
//	//UINT totalSize = sizeof(LightBuffer);
//	//CD3DX12_HEAP_PROPERTIES hp(D3D12_HEAP_TYPE_UPLOAD);
//	//auto desc = CD3DX12_RESOURCE_DESC::Buffer(totalSize);
//	//ThrowIfFailed(mp_device->GetDevice()->CreateCommittedResource(&hp, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_constantBuffer)));
//
//	//// map to our struct
//	//ThrowIfFailed(m_constantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_mappedBuffer)));
//
//
//	UINT rawSize = sizeof(LightBuffer);
//	UINT alignedSize = (rawSize + 255) & ~255u;    // arrondi au multiple de 256
//	CD3DX12_HEAP_PROPERTIES hp(D3D12_HEAP_TYPE_UPLOAD);
//	auto desc = CD3DX12_RESOURCE_DESC::Buffer(alignedSize);
//
//	ThrowIfFailed(
//		mp_device->GetDevice()
//		->CreateCommittedResource(
//			&hp,
//			D3D12_HEAP_FLAG_NONE,
//			&desc,
//			D3D12_RESOURCE_STATE_GENERIC_READ,
//			nullptr,
//			IID_PPV_ARGS(&m_constantBuffer))
//	);
//
//	// Map une seule fois, reste mappé en permanence
//	ThrowIfFailed(
//		m_constantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_mappedBuffer))
//	);
//}
//
//void LightSystem::Update(ECSManager& ecs, float dt)
//{
//	//if (!m_mappedBuffer) return;
//	//ComponentMask mask = (1ULL << LightComponent::StaticTypeID) | (1ULL << TransformComponent::StaticTypeID);
//	//m_mappedBuffer->lightCount = 0;
//	//ecs.ForEach(mask, [&](Entity e) {
//	//	if (m_mappedBuffer->lightCount >= MAX_LIGHTS) return;
//	//	auto& dst = m_mappedBuffer->lights[m_mappedBuffer->lightCount++];
//
//	//	auto* lc = ecs.GetComponent<LightComponent>(e);
//	//	auto* tc = ecs.GetComponent<TransformComponent>(e);
//
//	//	dst.type = static_cast<uint32_t>(lc->type);
//	//	dst.color_inten = XMFLOAT4{ lc->color.x, lc->color.y, lc->color.z, lc->intensity };
//	//	dst.dir_range = XMFLOAT4{ tc->position.x, tc->position.y, tc->position.z, lc->range };
//
//	//	//dst.type = (uint32_t)lc->type;
//	//	//dst.color = lc->color;
//	//	//dst.intensity = lc->intensity;
//	//	//if (lc->type == LightComponent::Directional) 
//	//	//{
//	//	//	dst.direction = lc->direction;
//	//	//	dst.range = 0;
//	//	//}
//	//	//else 
//	//	//{
//	//	//	dst.direction = tc->position;  // re-utiliser champ pour position
//	//	//	dst.range = lc->range;
//	//	//}
//	//	});
//
//
//
//
//	//// collecter jusqu'à MAX_LIGHTS dans _cpuLights, mettre _lightCount
//	//m_lightCount = 0;
//	//ComponentMask mask = (1ULL << LightComponent::StaticTypeID) | (1ULL << TransformComponent::StaticTypeID);
//	//ecs.ForEach(mask, [&](Entity e) {
//	//    if (m_lightCount >= MAX_LIGHTS) return;
//	//    auto* lc = ecs.GetComponent<LightComponent>(e);
//	//    auto* tc = ecs.GetComponent<TransformComponent>(e);
//	//    Light& L = m_cpuLights[m_lightCount++];
//	//    L.type = (uint32_t)lc->type;
//	//    L.color = lc->color;
//	//    L.intensity = lc->intensity;
//	//    if (lc->type == LightComponent::Directional) {
//	//        L.direction = lc->direction;
//	//        L.range = 0;
//	//    }
//	//    else {
//	//        L.direction = tc->position;  // re-utiliser champ pour position
//	//        L.range = lc->range;
//	//    }
//	//    });
//	//// écrire lightCount juste après le tableau
//	//memcpy(reinterpret_cast<BYTE*>(m_cpuLights) + sizeof(m_cpuLights), &m_lightCount, sizeof(UINT));
//
//		// 1) Local buffer
//	LightBuffer  local = {};
//	local.lightCount = 0;
//
//	ComponentMask mask =
//		(1ULL << LightComponent::StaticTypeID) |
//		(1ULL << TransformComponent::StaticTypeID);
//
//	ecs.ForEach(mask, [&](Entity e)
//		{
//			if (local.lightCount >= MAX_LIGHTS) return;
//			// Remplir local.lights[local.lightCount]
//			auto* lc = ecs.GetComponent<LightComponent>(e);
//			auto* tc = ecs.GetComponent<TransformComponent>(e);
//
//			auto& dst = local.lights[local.lightCount++];
//			dst.type = uint32_t(lc->type);
//			dst.color_inten = XMFLOAT4{ lc->color.x, lc->color.y, lc->color.z, lc->intensity };
//			dst.dir_range = XMFLOAT4{ tc->position.x, tc->position.y, tc->position.z, lc->range };
//		});
//
//	// 2) memcpy en une seule fois
//	memcpy(m_mappedBuffer, &local, sizeof(LightBuffer));
//}
//
//void LightSystem::BindAndUpload(CommandManager* cmdMgr) {
//	// on est en upload, _cb est déjà mappé
//	// binder au slot b2
//	cmdMgr->GetCommandList()->SetGraphicsRootConstantBufferView(2, m_constantBuffer->GetGPUVirtualAddress());
//}


// LightSystem.cpp
#include "pch.h"
#include "LightSystem.h"


void LightSystem::InitVariables(RenderingManager* rendMngr)
{
    mp_device = rendMngr->GetGraphicsDevice();
    mp_cmdMgr = rendMngr->GetCommandManager();
    mp_descMgr = rendMngr->GetDescriptorManager();


    // On prend directement sizeof(LightBuffer) qui est déjà multiple de 256
    m_cbvSize = sizeof(LightBuffer); // 512

    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
    auto desc = CD3DX12_RESOURCE_DESC::Buffer(m_cbvSize);

    ThrowIfFailed(
        mp_device->GetDevice()
        ->CreateCommittedResource(
            &heapProps,
            D3D12_HEAP_FLAG_NONE,
            &desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&m_constantBuffer))
    );

    // On mappe une fois pour la vie du buffer
    ThrowIfFailed(
        m_constantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_mappedBuffer))
    );

    // 1) Récupérer le heap SRV du DescriptorManager
    m_srvHeap = mp_descMgr->GetSrvHeap();

    // 2) Allouer un emplacement CPU & GPU dans ce heap
    m_cbvCpuHandle = mp_descMgr->AllocateSrvCPU();
    m_cbvGpuHandle = mp_descMgr->AllocateSrvGPU();

    // 3) Créer la vue CBV en pointant sur tout votre LightBuffer (arrondi 256 bytes)
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
    cbvDesc.BufferLocation = m_constantBuffer->GetGPUVirtualAddress();
    cbvDesc.SizeInBytes = UINT((sizeof(LightBuffer) + 255) & ~255u);

    mp_device->GetDevice()->CreateConstantBufferView(
        &cbvDesc,
        m_cbvCpuHandle
    );
}

void LightSystem::Init(ECSManager& ecs)
{
    //// On prend directement sizeof(LightBuffer) qui est déjà multiple de 256
    //m_cbvSize = sizeof(LightBuffer); // 512

    //CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
    //auto desc = CD3DX12_RESOURCE_DESC::Buffer(m_cbvSize);

    //ThrowIfFailed(
    //    mp_device->GetDevice()
    //    ->CreateCommittedResource(
    //        &heapProps,
    //        D3D12_HEAP_FLAG_NONE,
    //        &desc,
    //        D3D12_RESOURCE_STATE_GENERIC_READ,
    //        nullptr,
    //        IID_PPV_ARGS(&m_constantBuffer))
    //);

    //// On mappe une fois pour la vie du buffer
    //ThrowIfFailed(
    //    m_constantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_mappedBuffer))
    //);

    //// 1) Récupérer le heap SRV du DescriptorManager
    //m_srvHeap = descriptorManager->GetSrvHeap();

    //// 2) Allouer un emplacement CPU & GPU dans ce heap
    //m_cbvCpuHandle = descriptorManager->AllocateSrvCPU();
    //m_cbvGpuHandle = descriptorManager->AllocateSrvGPU();

    //// 3) Créer la vue CBV en pointant sur tout votre LightBuffer (arrondi 256 bytes)
    //D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
    //cbvDesc.BufferLocation = m_constantBuffer->GetGPUVirtualAddress();
    //cbvDesc.SizeInBytes = UINT((sizeof(LightBuffer) + 255) & ~255u);

    //mp_device->GetDevice()->CreateConstantBufferView(
    //    &cbvDesc,
    //    m_cbvCpuHandle
    //);
}

void LightSystem::Update(ECSManager& ecs, float dt)
{
    // 1) On remplit une locale
    LightBuffer local = {};
    local.lightCount = 0;

    ComponentMask mask =
        (1ULL << LightComponent::StaticTypeID) |
        (1ULL << TransformComponent::StaticTypeID);

    ecs.ForEach(mask, [&](Entity e) {
        if (local.lightCount >= MAX_LIGHTS) return;

        auto* lc = ecs.GetComponent<LightComponent>(e);
        auto* tc = ecs.GetComponent<TransformComponent>(e);

        auto& dst = local.lights[local.lightCount++];
        dst.type = uint32_t(lc->type);
        dst.color_inten = XMFLOAT4{ lc->color.x, lc->color.y, lc->color.z, lc->intensity };
        dst.dir_range = XMFLOAT4{ tc->position.x, tc->position.y, tc->position.z, lc->range };
        });

    // 2) Copie en une seule fois dans le buffer mappé (512 bytes)
    memcpy(m_mappedBuffer, &local, sizeof(LightBuffer));
}

void LightSystem::BindAndUpload(CommandManager* cmdMgr)
{

    //auto addr = m_constantBuffer->GetGPUVirtualAddress();
    //cmdMgr->GetCommandList()->SetGraphicsRootConstantBufferView(
    //    /*rootParameterIndex=*/2,
    //    addr
    //);
    // 2) Binder la table au paramètre racine 2
    cmdMgr->GetCommandList()->SetGraphicsRootDescriptorTable(
        2,
        m_constantBuffer->GetGPUVirtualAddress()
    );
}
