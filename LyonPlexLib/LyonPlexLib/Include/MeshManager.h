//#pragma once
//
//#include "GraphicsDevice.h"
//#include "ResourceManager.h"
////#include "d3dx12.h"
////#include <DirectXMath.h>
//#include "tiny_obj_loader.h"
////#include <unordered_map>
//
//struct VertexParam
//{
//    XMFLOAT3 Position;
//    XMFLOAT4 Color;
//    XMFLOAT2 TexCoord;
//    XMFLOAT3 Normal;
//
//    bool operator==(VertexParam const& o) const {
//        return memcmp(this, &o, sizeof(VertexParam)) == 0;
//    }
//};
//
//namespace std 
//{
//    template<> 
//    struct hash<VertexParam> 
//    {
//        size_t operator()(VertexParam const& v) const noexcept 
//        {
//            // simple hash combine
//            size_t h = std::hash<float>()(v.Position.x);
//            h = h * 31 + std::hash<float>()(v.Position.y);
//            h = h * 31 + std::hash<float>()(v.Position.z);
//            h = h * 31 + std::hash<float>()(v.Normal.x);
//            h = h * 31 + std::hash<float>()(v.Normal.y);
//            h = h * 31 + std::hash<float>()(v.Normal.z);
//            h = h * 31 + std::hash<float>()(v.TexCoord.x);
//            h = h * 31 + std::hash<float>()(v.TexCoord.y);
//            return h;
//        }
//    };
//}
//
//struct MeshData
//{
//    std::vector<VertexParam> vertices;
//    std::vector<uint16_t>    indices;
//    UINT vOffset = 0;
//    UINT vSize = 0;
//    UINT iOffset = 0;
//    UINT iSize = 0;
//
//    bool LoadFromFile(const std::string& path)
//    {
//        tinyobj::attrib_t attrib;
//        std::vector<tinyobj::shape_t> shapes;
//        std::vector<tinyobj::material_t> materials;
//        std::string warn, err;
//        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str()))
//            return false;
//
//        std::unordered_map<VertexParam, uint16_t> uniqueVertices;
//        for (auto const& shape : shapes) {
//            for (auto const& idx : shape.mesh.indices) {
//                VertexParam vp{};
//                vp.Position = {
//                    attrib.vertices[3 * idx.vertex_index + 0],
//                    attrib.vertices[3 * idx.vertex_index + 1],
//                    attrib.vertices[3 * idx.vertex_index + 2]
//                };
//                if (idx.normal_index >= 0)
//                    vp.Normal = {
//                        attrib.normals[3 * idx.normal_index + 0],
//                        attrib.normals[3 * idx.normal_index + 1],
//                        attrib.normals[3 * idx.normal_index + 2]
//                };
//                if (idx.texcoord_index >= 0)
//                    vp.TexCoord = {
//                        attrib.texcoords[2 * idx.texcoord_index + 0],
//                        attrib.texcoords[2 * idx.texcoord_index + 1]
//                };
//                vp.Color = { 1,1,1,1 };
//
//                if (uniqueVertices.count(vp) == 0) {
//                    uniqueVertices[vp] = static_cast<uint16_t>(vertices.size());
//                    vertices.push_back(vp);
//                }
//                indices.push_back(uniqueVertices[vp]);
//            }
//        }
//        vSize = static_cast<UINT>(vertices.size());
//        iSize = static_cast<UINT>(indices.size());
//        return true;
//    }
//
//    void Unload()
//    {
//        vertices.clear();
//        indices.clear();
//    }
//};
//
//class MeshManager
//{
//public:
//    void Init(GraphicsDevice* graphicsDevice)
//    {
//        mp_graphicsDevice = graphicsDevice;
//        // Optionnel: charger shapes basiques
//        InitializeMesh_Triangle();
//        InitializeMesh_Square();
//        InitializeMesh_Cube();
//        // ...
//
//        Entity tree = { -1 };
//        LoadObjMesh("../LyonPlexLib/Ressources/ArbreTest.obj", tree.id);
//        BuildAndUploadGlobalBuffers();
//    }
//
//    bool LoadObjMesh(const std::string& path, uint32_t& outMeshID)
//    {
//        MeshData mesh;
//        if (!mesh.LoadFromFile(path))
//            return false;
//        outMeshID = m_meshLibrary.Add(mesh);
//        return true;
//    }
//
//    // ICI ET EN DESSOUS NON CHANGE
//	D3D12_VERTEX_BUFFER_VIEW& GetGlobalVBView() { return m_globalVBView; };
//	D3D12_INDEX_BUFFER_VIEW& GetGlobalIBView() { return m_globalIBView; };
//
//	ResourceManager<MeshData>& GetMeshLib() { return m_meshLibrary; }
//
//private:
//
//	MeshData CreateMesh_Triangle();
//	MeshData CreateMesh_Square();
//	MeshData CreateMesh_Cube();
//
//	HRESULT BuildAndUploadGlobalBuffers();
//
//	void InitializeBasicShapes();
//
//	void InitializeMesh_Triangle();
//	void InitializeMesh_Square();
//	void InitializeMesh_Cube();
//
//
//	GraphicsDevice* mp_graphicsDevice;
//
//
//	// Variables de Vertex et Index globales
//	ComPtr<ID3D12Resource> m_globalVertexBuffer;
//	D3D12_VERTEX_BUFFER_VIEW m_globalVBView;
//
//	ComPtr<ID3D12Resource> m_globalIndexBuffer;
//	D3D12_INDEX_BUFFER_VIEW m_globalIBView;
//
//	// Buffers globaux (membres de la classe)
//	std::vector<VertexParam> m_globalVertices;
//	std::vector<uint16_t>  m_globalIndices;
//
//	// Bibliotheque de meshs
//	ResourceManager<MeshData> m_meshLibrary;
//
//};
//


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
