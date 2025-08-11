#pragma once

#include "IRender.h"
#include "GraphicsPipeline.h"
#include "MeshManager.h"
#include "WaveManager.h"
#include "WaterPipeline.h"
#include "TextureManager.h"
#include "ParticleManager.h"

class ECSManager;

//inline UINT Align256(UINT size) { return (size + 255) & ~255; } //	Mettre dans Utils ??

struct ConstantBuffData
{
	DirectX::XMFLOAT4X4 World;				// Pos objet
	uint32_t            materialIndex = 0;	
	float				alpha = 1;
	float               padding[2];			// 8 bytes de « rembourrage » pour remplir le slot 16 bytes
};

class Render3D : public IRender
{
public:
	bool Init(HWND windowHandle, ECSManager* ECS, GraphicsDevice* graphicsDevice, DescriptorManager* descriptorManager, CommandManager* commandManager, MeshManager* meshManager) override;

	bool SetWaveManager(WaveManager* waveManager);
	bool SetTextureManager(TextureManager* textureManager);

	void Resize(int w, int h) override;
	void RecordCommands() override;
	void CreatePipeline() override; // Managing chain for 3D elements (data not draw)

	GraphicsPipeline& GetGraphicsPipeline() { return m_graphicsPipeline; };

	ParticleManager& GetParticleManager() { return m_smokeParticles; };

	void Release();

private:

	bool InitConstantBuffer();
	void AllocateCBUpload();
	void EnsureCapacity(UINT requiredEntityCount);
	void UpdateAndBindCB(Entity ent);


	HWND				m_windowWP;

	GraphicsDevice*		mp_graphicsDevice;
	DescriptorManager*	mp_descriptorManager;
	CommandManager*		mp_commandManager;

	MeshManager*		m_meshManager;
	TextureManager*		mp_textureManager = nullptr;

	GraphicsPipeline	m_graphicsPipeline;
	GraphicsPipeline	m_graphicsPipelineSeeThrough;

	WaterPipeline		m_waterPipeline;
	WaveManager*		m_waveManager;

	ParticleManager		m_smokeParticles;
	float				m_smokeTotalTime = 0;

	//ECS Manager
	ECSManager*			m_ECS;

	// Data linked to cBuffer VertexParam
	ComPtr<ID3D12Resource>	m_cbTransformUpload = nullptr;
	void*					m_mappedCBData		= nullptr;
	UINT					m_cbSize			= Align256(sizeof(ConstantBuffData)); // taille alignee a 256

	UINT                m_allocatedEntityCount = 0;  // capacité courante
	UINT                m_frameCount = 0;            // nombre de frames en vol

};

