


// LightSystem.cpp
#include "pch.h"
#include "LightSystem.h"

void LightSystem::InitVariables(RenderingManager* rendMngr)
{
    mp_device = rendMngr->GetGraphicsDevice();
    mp_cmdMgr = rendMngr->GetCommandManager();

    // Calculate aligned sizes
    m_countSize = (sizeof(CountCB) + 255) & ~255ull;
    m_arraySize = (sizeof(ArrayCB) + 255) & ~255ull;

    // Create upload heap for count buffers: totalSize = countSize * FRAME_COUNT
    uint64_t totalCountSize = m_countSize * FRAME_COUNT;
    {
        CD3DX12_HEAP_PROPERTIES hp(D3D12_HEAP_TYPE_UPLOAD);
        auto desc = CD3DX12_RESOURCE_DESC::Buffer(totalCountSize);
        ThrowIfFailed(mp_device->GetDevice()->CreateCommittedResource(
            &hp, D3D12_HEAP_FLAG_NONE, &desc,
            D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
            IID_PPV_ARGS(&m_countUpload)));
        CD3DX12_RANGE readRange(0, 0);
        ThrowIfFailed(m_countUpload->Map(0, &readRange, reinterpret_cast<void**>(&m_countMapped)));
    }

    // Create upload heap for array buffers: totalSize = arraySize * FRAME_COUNT
    uint64_t totalArraySize = m_arraySize * FRAME_COUNT;
    {
        CD3DX12_HEAP_PROPERTIES hp(D3D12_HEAP_TYPE_UPLOAD);
        auto desc = CD3DX12_RESOURCE_DESC::Buffer(totalArraySize);
        ThrowIfFailed(mp_device->GetDevice()->CreateCommittedResource(
            &hp, D3D12_HEAP_FLAG_NONE, &desc,
            D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
            IID_PPV_ARGS(&m_arrayUpload)));
        CD3DX12_RANGE readRange(0, 0);
        ThrowIfFailed(m_arrayUpload->Map(0, &readRange, reinterpret_cast<void**>(&m_arrayMapped)));
    }
}

void LightSystem::Init(ECSManager& ecs)
{
    // No additional init
}

void LightSystem::Update(ECSManager& ecs, float dt)
{
    m_currentFrame = mp_device->GetFrameIndex() % FRAME_COUNT;

    // Gather lights
    uint32_t count = 0;
    Light temp[MAX_LIGHTS];
    ComponentMask mask = (1ULL << LightComponent::StaticTypeID) | (1ULL << TransformComponent::StaticTypeID);
    ecs.ForEach(mask, [&](Entity e) {
        if (count >= MAX_LIGHTS) return;
        auto* lc = ecs.GetComponent<LightComponent>(e);
        auto* tc = ecs.GetComponent<TransformComponent>(e);
        temp[count++] = { uint32_t(lc->type),
                          {lc->color.x, lc->color.y, lc->color.z},
                          lc->intensity,
                          {tc->position.x, tc->position.y, tc->position.z},
                          lc->range };
        });

    // Copy count
    uint8_t* countDst = m_countMapped + m_currentFrame * m_countSize;
    memcpy(countDst, &count, sizeof(count));

    // Copy array
    ArrayCB arrayData{};
    memcpy(arrayData.lights, temp, sizeof(Light) * count);
    uint8_t* arrayDst = m_arrayMapped + m_currentFrame * m_arraySize;
    memcpy(arrayDst, &arrayData, sizeof(ArrayCB));
}

void LightSystem::BindAndUpload(CommandManager* cmdMgr)
{
    auto cl = cmdMgr->GetCommandList();
    // Bind count CBV at b2
    auto countAddr = m_countUpload->GetGPUVirtualAddress() + m_currentFrame * m_countSize;
    cl->SetGraphicsRootConstantBufferView(2, countAddr);
    // Bind array CBV at b3
    auto arrayAddr = m_arrayUpload->GetGPUVirtualAddress() + m_currentFrame * m_arraySize;
    cl->SetGraphicsRootConstantBufferView(3, arrayAddr);
}
