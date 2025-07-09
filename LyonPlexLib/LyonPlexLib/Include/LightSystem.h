
// LightSystem.h
#pragma once
#include "ISystem.h"
#include "ECSManager.h"
#include "GraphicsDevice.h"
#include "CommandManager.h"
#include "Components.h"
#include <wrl.h>
using Microsoft::WRL::ComPtr;

class RenderingManager;

static const uint32_t MAX_LIGHTS = 8;
static const uint32_t FRAME_COUNT = 2;

struct Light
{
    uint32_t type;
    float    color[3];
    float    intensity;
    float    direction[3];
    float    range;
};

struct CountCB
{
    uint32_t lightCount;
    uint32_t pad[3]; // align to 16 bytes
};

struct ArrayCB
{
    Light lights[MAX_LIGHTS];
};

class LightSystem : public ISystem {
public:
    void InitVariables(RenderingManager* rendMngr);
    void Init(ECSManager& ecs) override;
    void Update(ECSManager& ecs, float dt) override;
    void BindAndUpload(CommandManager* cmdMgr);

private:
    uint64_t m_countSize = 0;
    uint64_t m_arraySize = 0;

    ComPtr<ID3D12Resource> m_countUpload;
    uint8_t* m_countMapped = nullptr;

    ComPtr<ID3D12Resource> m_arrayUpload;
    uint8_t* m_arrayMapped = nullptr;

    uint32_t m_currentFrame = 0;

    GraphicsDevice* mp_device = nullptr;
    CommandManager* mp_cmdMgr = nullptr;
};
