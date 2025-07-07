// LightSystem.h
#pragma once
#include "ISystem.h"

#include "ECSManager.h"
#include "GraphicsDevice.h"
#include "CommandManager.h"

#include "Components.h"


static const uint32_t MAX_LIGHTS = 8;

//struct Light
//{
//	uint32_t    type = 0; // 0 = dir, 1 = point
//	XMFLOAT3	color = { 0, 1, 0 };
//	float		intensity = 1;
//	XMFLOAT3	direction = { 0, 0, 0 };; // ou position si point
//	float		range = 1;
//};
//
//// structure exactement calquée sur le cbuffer HLSL
//struct alignas(256) LightBuffer
//{
//	Light lights[MAX_LIGHTS]; // votre struct Light déjà définie
//	UINT  lightCount = 0;
//	// padding pour atteindre un multiple de 16 bytes si besoin
//	UINT  _pad[3];
//};

// chaque “Light” occupe exactement 3 × 16 bytes = 48 bytes
struct alignas(16) HlslLight
{
	uint32_t   type;          //  4
	uint32_t   _pad0[3];      // 12 -> on aligne à 16
	XMFLOAT4   color_inten;   // 16 = color.xyz + intensity dans color_inten.w
	XMFLOAT4   dir_range;     // 16 = direction.xyz + range dans dir_range.w
};

// puis le buffer complet
struct alignas(256) LightBuffer
{
	HlslLight lights[MAX_LIGHTS]; // 8 × 48 = 384 bytes
	uint32_t  lightCount;         //  4
	uint32_t  _pad[3];            // 12 -> pour aligner à 16
	// total = 384 + 16 = 400 -> aligné à 256 (constant buffer must be 256?aligned)
};


class LightSystem : public ISystem {
public:
	void InitVariables(GraphicsDevice* device, CommandManager* cmdMgr);
	void Init(ECSManager& ecs) override;
	void Update(ECSManager& ecs, float dt) override;
	void BindAndUpload(CommandManager* cmdMgr);

	LightBuffer* GetMappedBuffer() { return m_mappedBuffer; };

private:
	ComPtr<ID3D12Resource>	m_constantBuffer;    // upload heap
	LightBuffer*			m_mappedBuffer = nullptr;
	//Light                   m_cpuLights[MAX_LIGHTS];
	//UINT                    m_lightCount = 0;

	GraphicsDevice* mp_device = nullptr;
	CommandManager* mp_cmdMgr = nullptr;
};

