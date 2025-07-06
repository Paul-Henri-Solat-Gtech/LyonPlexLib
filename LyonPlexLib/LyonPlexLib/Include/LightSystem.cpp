#include "pch.h"
// LightSystem.cpp
#include "LightSystem.h"
//#include <d3dx12.h>

void LightSystem::Init(ECSManager& ecs, GraphicsDevice* dev, CommandManager* cmd) 
{
    mp_device = dev; 
    mp_cmdMgr = cmd;

    // créer le buffer GPU de taille sizeof(LightBuffer)
    UINT totalSize = sizeof(m_cpuLights) + sizeof(UINT);
    CD3DX12_HEAP_PROPERTIES hp(D3D12_HEAP_TYPE_UPLOAD);
    auto desc = CD3DX12_RESOURCE_DESC::Buffer(totalSize);

    //THROW_IF_FAILED(dev->GetDevice()->CreateCommittedResource(&hp, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&_cb)));
    dev->GetDevice()->CreateCommittedResource(&hp, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_constantBuffer));
    m_constantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_cpuLights));
}

void LightSystem::Update(ECSManager& ecs, float dt) {
    // collecter jusqu'à MAX_LIGHTS dans _cpuLights, mettre _lightCount
    m_lightCount = 0;
    ComponentMask mask = (1ULL << LightComponent::StaticTypeID) | (1ULL << TransformComponent::StaticTypeID);
    ecs.ForEach(mask, [&](Entity e) {
        if (m_lightCount >= MAX_LIGHTS) return;
        auto* lc = ecs.GetComponent<LightComponent>(e);
        auto* tc = ecs.GetComponent<TransformComponent>(e);
        Light& L = m_cpuLights[m_lightCount++];
        L.type = (uint32_t)lc->type;
        L.color = lc->color;
        L.intensity = lc->intensity;
        if (lc->type == LightComponent::Directional) {
            L.direction = lc->direction;
            L.range = 0;
        }
        else {
            L.direction = tc->position;  // re-utiliser champ pour position
            L.range = lc->range;
        }
        });
    // écrire lightCount juste après le tableau
    memcpy(reinterpret_cast<BYTE*>(m_cpuLights) + sizeof(m_cpuLights), &m_lightCount, sizeof(UINT));
}

void LightSystem::BindAndUpload() {
    // on est en upload, _cb est déjà mappé
    // binder au slot b2
    mp_cmdMgr->GetCommandList()->SetGraphicsRootConstantBufferView(2, m_constantBuffer->GetGPUVirtualAddress());
}
