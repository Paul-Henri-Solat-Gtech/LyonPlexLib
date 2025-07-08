//// LightSystem.h
//#pragma once
//#include "ISystem.h"
//
//#include "ECSManager.h"
//#include "GraphicsDevice.h"
//#include "CommandManager.h"
//
//#include "Components.h"
//
//
//static const uint32_t MAX_LIGHTS = 8;
//
////struct Light
////{
////	uint32_t    type = 0; // 0 = dir, 1 = point
////	XMFLOAT3	color = { 0, 1, 0 };
////	float		intensity = 1;
////	XMFLOAT3	direction = { 0, 0, 0 };; // ou position si point
////	float		range = 1;
////};
////
////// structure exactement calquée sur le cbuffer HLSL
////struct alignas(256) LightBuffer
////{
////	Light lights[MAX_LIGHTS]; // votre struct Light déjà définie
////	UINT  lightCount = 0;
////	// padding pour atteindre un multiple de 16 bytes si besoin
////	UINT  _pad[3];
////};
//
//// chaque “Light” occupe exactement 3 × 16 bytes = 48 bytes
//struct alignas(16) Light
//{
//	uint32_t   type;          //  4
//	uint32_t   _pad0[3];      // 12 -> on aligne à 16
//	XMFLOAT4   color_inten;   // 16 = color.xyz + intensity dans color_inten.w
//	XMFLOAT4   dir_range;     // 16 = direction.xyz + range dans dir_range.w
//};
//
//// puis le buffer complet
//struct alignas(256) LightBuffer
//{
//	uint32_t  lightCount;         //  4
//	uint32_t  _pad[3];            // 12 -> pour aligner à 16
//	Light lights[MAX_LIGHTS]; // 8 × 48 = 384 bytes
//};
//
//
//class LightSystem : public ISystem {
//public:
//	void InitVariables(GraphicsDevice* device, CommandManager* cmdMgr);
//	void Init(ECSManager& ecs) override;
//	void Update(ECSManager& ecs, float dt) override;
//	void BindAndUpload(CommandManager* cmdMgr);
//
//	LightBuffer* GetMappedBuffer() { return m_mappedBuffer; };
//
//private:
//	ComPtr<ID3D12Resource>	m_constantBuffer;    // upload heap
//	LightBuffer*			m_mappedBuffer = nullptr;
//	//Light                   m_cpuLights[MAX_LIGHTS];
//	//UINT                    m_lightCount = 0;
//
//	GraphicsDevice* mp_device = nullptr;
//	CommandManager* mp_cmdMgr = nullptr;
//};
//


// LightSystem.h
#pragma once
#include "ISystem.h"
#include "ECSManager.h"
#include "GraphicsDevice.h"
#include "CommandManager.h"
#include "Components.h"

class RenderingManager;

static const uint32_t MAX_LIGHTS = 2;

// chaque “Light” occupe exactement 3 × 16 bytes = 48 bytes
struct Light
{
    //uint32_t   type;          //  4
    //uint32_t   _pad0[3];      // 12 -> on aligne à 16
    //XMFLOAT4   color_inten;   // 16 = color.xyz + intensity dans w
    //XMFLOAT4   dir_range;     // 16 = direction.xyz + range dans w
    uint32_t type;
    float    color[3];
    float    intensity;
    float    direction[3];
    float    range;
    //float    _pad[3];
};

// on met d’abord lightCount pour être sur qu’il est dans les 256 premiers bytes,
// puis padding pour 16?bytes, puis les lights, puis padding final pour atteindre 512 bytes
struct LightBuffer
{
    uint32_t  lightCount;               //  4
    uint32_t  _pad0[3];                 // 12 -> aligne à 16
    Light     lights[MAX_LIGHTS];       // 8 × 48 = 384
    //uint8_t   _padEnd[112];             // => 4+12+384+112 = 512
};
static_assert(sizeof(LightBuffer) % 256 == 0, "LightBuffer doit faire un multiple de 256 bytes");

class LightSystem : public ISystem {
public:
    //void InitVariables(GraphicsDevice* device, CommandManager* cmdMgr);
    void InitVariables(RenderingManager* rendMngr);
    void Init(ECSManager& ecs) override;
    void Update(ECSManager& ecs, float dt) override;
    void BindAndUpload(CommandManager* cmdMgr);

    // accède directement au buffer mappé (taille = sizeof(LightBuffer)==512)
    LightBuffer* GetMappedBuffer() { return m_mappedBuffer; };

private:
    ComPtr<ID3D12Resource> m_constantBuffer; // upload heap
    LightBuffer* m_mappedBuffer = nullptr;
    UINT64                 m_cbvSize = 0;       // = sizeof(LightBuffer)
    GraphicsDevice* mp_device = nullptr;
    CommandManager* mp_cmdMgr = nullptr;
    DescriptorManager* mp_descMgr = nullptr;

    ComPtr<ID3D12DescriptorHeap> m_srvHeap; // on récupérera le heap SRV
    D3D12_GPU_DESCRIPTOR_HANDLE  m_cbvGpuHandle{};
    D3D12_CPU_DESCRIPTOR_HANDLE  m_cbvCpuHandle{};
};
