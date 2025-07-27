#pragma once
#include "Utils.h"
#include "TextureManager.h"

struct CBData
{
	DirectX::XMFLOAT4X4 World;				// Pos objet
	DirectX::XMFLOAT2   scrollOffset;
	float               padding[2];			
};

struct WaveVertex {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 uv;
	XMFLOAT3 normal;
};

class WaveManager
{
public:
	void Init(GraphicsDevice* graphicsDevice, TextureManager* textureManager);

	void InitWave();

	void SetECS(ECSManager* ecs) { m_ECS = ecs; };

	void Update(float deltaTime);

	void LoadTexture(TextureManager::TextureID id);

	D3D12_VERTEX_BUFFER_VIEW& GetVBView() { return m_VBView; }
	D3D12_INDEX_BUFFER_VIEW& GetIBView() { return m_IBView; }

	ComPtr<ID3D12Resource>& GetCBbuffer() { return m_constantBuffer; }

private:
	HRESULT BuildAndUploadBuffers();
	MeshData CreateMesh_Wave();

	//Utils::Vector2 scrollOffset = {0,0};
	DirectX::XMFLOAT2 m_scrollOffset = {0,0};

	std::vector<WaveVertex>  m_Vertices;
	std::vector<uint32_t>    m_Indices;

	ECSManager* m_ECS;

	GraphicsDevice* mp_graphicsDevice = nullptr;
	TextureManager* mp_textureManager = nullptr;

	ComPtr<ID3D12Resource>		m_VertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW	m_VBView;
	ComPtr<ID3D12Resource>		m_IndexBuffer;
	D3D12_INDEX_BUFFER_VIEW		m_IBView;

	// Data linked to cBuffer VertexParam
	ComPtr<ID3D12Resource>	m_constantBuffer	= nullptr;
	void*					m_mappedCBData		= nullptr;
	UINT					m_cbSize			= Align256(sizeof(CBData)); // taille alignee a 256
};

