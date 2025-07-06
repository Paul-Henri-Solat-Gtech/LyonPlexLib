// MeshManager.h
#pragma once

#include "GraphicsDevice.h"
#include "ResourceManager.h"
#include "TextureManager.h"

struct VertexParam
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT4 Color;
	DirectX::XMFLOAT2 TexCoord;
	DirectX::XMFLOAT3 Normal;


	bool operator==(VertexParam const& o) const
	{
		return memcmp(this, &o, sizeof(VertexParam)) == 0;
	}
};

namespace std
{
	template<>
	struct hash<VertexParam>
	{
		size_t operator()(VertexParam const& v) const noexcept
		{
			// simple hash combine
			size_t h = std::hash<float>()(v.Position.x);
			h = h * 31 + std::hash<float>()(v.Position.y);
			h = h * 31 + std::hash<float>()(v.Position.z);
			h = h * 31 + std::hash<float>()(v.Normal.x);
			h = h * 31 + std::hash<float>()(v.Normal.y);
			h = h * 31 + std::hash<float>()(v.Normal.z);
			h = h * 31 + std::hash<float>()(v.TexCoord.x);
			h = h * 31 + std::hash<float>()(v.TexCoord.y);
			return h;
		}
	};
}

struct SubMesh
{
	uint32_t IndexOffset;
	uint32_t IndexCount;
	uint32_t MaterialID;
};

struct MeshData // OK for complex shapes composed of multiple shapes
{
	std::vector<VertexParam> vertices;
	std::vector<uint32_t>    indices;
	std::vector<SubMesh>     subMeshes;

	// store .mtl materials and associated texture IDs (for multiTextures/multiShapes meshes)
	std::vector<std::string>                materialNames;
	std::vector<TextureManager::TextureID>  materialTextureIDs;

	UINT vOffset = 0;
	UINT vSize = 0;
	UINT iOffset = 0;
	UINT iSize = 0;

	bool LoadFromFile(const std::string& path);
	void Unload()
	{
		vertices.clear();
		indices.clear();
		subMeshes.clear();
		materialNames.clear();
		materialTextureIDs.clear();
	}
};

class MeshManager
{
public:
	void Init(GraphicsDevice* graphicsDevice, TextureManager* textureManager);
	void InitTriangle();
	void InitSquare();
	void InitCube();
	// load custom mesh
	void LoadMeshFromFile(const std::string& path);

	D3D12_VERTEX_BUFFER_VIEW& GetGlobalVBView() { return m_globalVBView; }
	D3D12_INDEX_BUFFER_VIEW& GetGlobalIBView() { return m_globalIBView; }
	ResourceManager<MeshData>& GetMeshLib() { return m_meshLibrary; }

	HRESULT BuildAndUploadGlobalBuffers();
private:

	MeshData CreateMesh_Triangle();
	MeshData CreateMesh_Square();
	MeshData CreateMesh_Cube();


	GraphicsDevice* mp_graphicsDevice = nullptr;
	TextureManager* mp_textureManager = nullptr;

	ComPtr<ID3D12Resource> m_globalVertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW m_globalVBView;
	ComPtr<ID3D12Resource> m_globalIndexBuffer;
	D3D12_INDEX_BUFFER_VIEW m_globalIBView;

	std::vector<VertexParam> m_globalVertices;
	std::vector<uint32_t>    m_globalIndices;

	ResourceManager<MeshData> m_meshLibrary;
};
