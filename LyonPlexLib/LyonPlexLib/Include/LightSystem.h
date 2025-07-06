// LightSystem.h
#pragma once
#include "ISystem.h"

#include "ECSManager.h"
#include "GraphicsDevice.h"
#include "CommandManager.h"

#include "Components.h"

static const uint32_t MAX_LIGHTS = 8;

struct Light
{
	uint32_t    type; // 0 = dir, 1 = point
	XMFLOAT3	color;
	float		intensity;
	XMFLOAT3	direction; // ou position si point
	float		range;
};

class LightSystem : public ISystem {
public:
	void Init(ECSManager& ecs, GraphicsDevice* dev, CommandManager* cmd);
	void Update(ECSManager& ecs, float dt);
	void BindAndUpload();

private:
	ComPtr<ID3D12Resource>	m_constantBuffer;    // upload heap
	Light                   m_cpuLights[MAX_LIGHTS];
	UINT                    m_lightCount = 0;

	GraphicsDevice* mp_device = nullptr;
	CommandManager* mp_cmdMgr = nullptr;
};

