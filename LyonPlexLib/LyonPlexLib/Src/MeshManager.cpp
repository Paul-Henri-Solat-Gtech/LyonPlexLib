//#include "pch.h"
//#include "MeshManager.h"
//
//#define TINYOBJLOADER_IMPLEMENTATION
//#include <tiny_obj_loader.h>
//
////void MeshManager::Init(GraphicsDevice* graphicsDevice)
////{
////	mp_graphicsDevice = graphicsDevice;
////
////	// Initialisation de tous les mesh
////	//InitializeMesh_Cube();
////	InitializeMesh_Triangle();
////	InitializeMesh_Square();
////	InitializeMesh_Cube();
////	// ...
////
////
////	// Build & upload meshs
////	BuildAndUploadGlobalBuffers();
////
////	//InitConstantBuffer();
////
////}
//


// MeshManager.cpp
#include "pch.h"
#include "MeshManager.h"

// NEEDED FOR TINY_OBJECT_LOADER
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"


MeshData MeshManager::CreateMesh_Triangle()
{
	MeshData m;
	m.vertices =
	{
		{{ 0.0f,  0.5f, 0.0f}, { 1, 1, 0, 1}, {0,1}, { 0,  0, -1}},
		{{ 0.5f,-0.5f, 0.0f}, { 0, 0, 0, 1}, {0,1}, { 0,  0, -1}},
		{{-0.5f,-0.5f, 0.0f}, { 0, 0, 0, 1}, {0,1}, { 0,  0, -1}},
	};

	// Definition des indices pour dessiner 2 triangles
	m.indices = { 0, 1, 2 };

	m.subMeshes.push_back(SubMesh{
		/* IndexOffset = */ 0,
		/* IndexCount  = */ static_cast<uint32_t>(m.indices.size()),
		/* MaterialIndex = */ 0
		});

	m.vSize = static_cast<uint32_t>(m.vertices.size());
	m.iSize = static_cast<uint32_t>(m.indices.size());


	return m;
}
MeshData MeshManager::CreateMesh_Square()
{
	MeshData m;
	m.vertices =
	{
		// coin haut-gauche
		{{ -1, 1, 0.0f},	{ 5, 1, 0, 1}, {0,1}, { 0,  0, -1}},
		// coin bas-gauche
		{{ -1, -1, 0.0f},	{ 0, 0, 0, 1}, {0,1}, { 0,  0, -1}},
		// coin bas-droit
		{{ 1, -1, 0.0f},	{ 0, 0, 0, 1}, {0,1}, { 0,  0, -1}},
		// coin haut-droit
		{{ 1, 1, 0.0f},		{ 0, 0, 0, 1}, {0,1}, { 0,  0, -1}},
	};

	// Definition des indices pour dessiner 2 triangles
	m.indices =
	{
		0, 2, 1,  // triangle bas-gauche → bas-droit
		0, 3, 2   // triangle bas-gauche → haut-droit
	};

	m.subMeshes.push_back(SubMesh{
		/* IndexOffset = */ 0,
		/* IndexCount  = */ static_cast<uint32_t>(m.indices.size()),
		/* MaterialIndex = */ 0
		});

	m.vSize = static_cast<uint32_t>(m.vertices.size());
	m.iSize = static_cast<uint32_t>(m.indices.size());
	return m;
}
MeshData MeshManager::CreateMesh_Cube()
{
	MeshData m;
	m.vertices =
	{
		// Face avant (z = -0.25)
		{{-0.5f,  0.5f, -0.5f}, {1,0,0,1}, {0,0}, { 0,  0, -1}},
		{{-0.5f, -0.5f, -0.5f}, {0,1,0,1}, {0,1}, { 0,  0, -1}},
		{{ 0.5f, -0.5f, -0.5f}, {0,0,1,1}, {1,1}, { 0,  0, -1}},
		{{ 0.5f,  0.5f, -0.5f}, {1,1,0,1}, {1,0}, { 0,  0, -1}},

		// Face arrière (z = +0.25)
		{{ 0.5f,  0.5f,  0.5f}, {1,0,1,1}, {0,0}, { 0,  0, 1}},
		{{ 0.5f, -0.5f,  0.5f}, {0,1,1,1}, {0,1}, { 0,  0, 1}},
		{{-0.5f, -0.5f,  0.5f}, {1,1,1,1}, {1,1}, { 0,  0, 1}},
		{{-0.5f,  0.5f,  0.5f}, {0,0,0,1}, {1,0}, { 0,  0, 1}},

		// Face gauche (x = -0.25)
		{{-0.5f,  0.5f,  0.5f}, {1,0,1,1}, {0,0}, { -1,  0, 0}},
		{{-0.5f, -0.5f,  0.5f}, {0,1,1,1}, {0,1}, { -1,  0, 0}},
		{{-0.5f, -0.5f, -0.5f}, {0,1,0,1}, {1,1}, { -1,  0, 0}},
		{{-0.5f,  0.5f, -0.5f}, {1,0,0,1}, {1,0}, { -1,  0, 0}},

		// Face droite (x = +0.25)
		{{ 0.5f,  0.5f, -0.5f}, {1,1,0,1}, {0,0}, { 1,  0, 0}},
		{{ 0.5f, -0.5f, -0.5f}, {0,0,1,1}, {0,1}, { 1,  0, 0}},
		{{ 0.5f, -0.5f,  0.5f}, {1,1,1,1}, {1,1}, { 1,  0, 0}},
		{{ 0.5f,  0.5f,  0.5f}, {1,0,1,1}, {1,0}, { 1,  0, 0}},

		// Face haut (y = +0.25)
		{{-0.5f,  0.5f,  0.5f}, {1,0,1,1}, {0,0}, { 0,  1, 0}},
		{{-0.5f,  0.5f, -0.5f}, {1,0,0,1}, {0,1}, { 0,  1, 0}},
		{{ 0.5f,  0.5f, -0.5f}, {1,1,0,1}, {1,1}, { 0,  1, 0}},
		{{ 0.5f,  0.5f,  0.5f}, {0,0,0,1}, {1,0}, { 0,  1, 0}},

		// Face bas (y = -0.25)
		{{-0.5f, -0.5f, -0.5f}, {0,1,0,1}, {0,0}, { 0,  -1, 0}},
		{{-0.5f, -0.5f,  0.5f}, {0,1,1,1}, {0,1}, { 0,  -1, 0}},
		{{ 0.5f, -0.5f,  0.5f}, {1,1,1,1}, {1,1}, { 0,  -1, 0}},
		{{ 0.5f, -0.5f, -0.5f}, {0,0,1,1}, {1,0}, { 0,  -1, 0}},
	};

	// Indices : chaque face fait 2 triangles, on incrémente de 4 à chaque fois
	m.indices =
	{
		0,  1,  2,   0,  2,  3,    // avant
		4,  5,  6,   4,  6,  7,    // arrière
		8,  9, 10,   8, 10, 11,    // gauche
	   12, 13, 14,  12, 14, 15,    // droite
	   16, 17, 18,  16, 18, 19,    // haut
	   20, 21, 22,  20, 22, 23     // bas
	};

	m.subMeshes.push_back(SubMesh{
		/* IndexOffset = */ 0,
		/* IndexCount  = */ static_cast<uint32_t>(m.indices.size()),
		/* MaterialIndex = */ 0
		});

	m.vSize = static_cast<uint32_t>(m.vertices.size());
	m.iSize = static_cast<uint32_t>(m.indices.size());
	return m;
}
//
//HRESULT MeshManager::BuildAndUploadGlobalBuffers()
//{
//	std::vector<VertexParam> globalVerts;
//	std::vector<uint16_t>  globalIdxs;
//	size_t vertexCursor = 0;
//	size_t indexCursor = 0;
//
//	// Parcours chaque MeshData enregistre (du plus petit ID au plus grand)
//	for (uint32_t id = 0; id < m_meshLibrary.Count(); ++id)
//	{
//		MeshData& md = m_meshLibrary.Get(id);
//
//		// 1) Calculer et stocker les offsets
//		md.vOffset = static_cast<uint32_t>(vertexCursor);
//		md.vSize = static_cast<uint32_t>(md.vertices.size());
//		md.iOffset = static_cast<uint32_t>(indexCursor);
//		md.iSize = static_cast<uint32_t>(md.indices.size());
//
//		// 2) Ajouter les sommets de ce maillage a la suite
//		globalVerts.insert(globalVerts.end(), md.vertices.begin(), md.vertices.end());
//
//		// 3) Ajouter les indices, corriges par le decalage vOffset
//		for (auto idx : md.indices)
//		{
//			globalIdxs.push_back(static_cast<uint16_t>(idx + md.vOffset));
//		}
//
//		vertexCursor += md.vSize;
//		indexCursor += md.iSize;
//	}
//
//
//	UINT vByteSize = UINT(globalVerts.size() * sizeof(VertexParam));
//	UINT iByteSize = UINT(globalIdxs.size() * sizeof(uint16_t));
//
//	D3D12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
//
//	// Vertex Buffer
//	{
//		auto vbDesc = CD3DX12_RESOURCE_DESC::Buffer(vByteSize);
//		mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &vbDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_globalVertexBuffer));
//
//		void* pData = nullptr;
//		CD3DX12_RANGE readRange(0, 0);
//		m_globalVertexBuffer->Map(0, &readRange, &pData);
//		memcpy(pData, globalVerts.data(), vByteSize);
//		m_globalVertexBuffer->Unmap(0, nullptr);
//
//		m_globalVBView.BufferLocation = m_globalVertexBuffer->GetGPUVirtualAddress();
//		m_globalVBView.StrideInBytes = sizeof(VertexParam);
//		m_globalVBView.SizeInBytes = vByteSize;
//	}
//
//	// Index Buffer
//	{
//		auto ibDesc = CD3DX12_RESOURCE_DESC::Buffer(iByteSize);
//		mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &ibDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_globalIndexBuffer));
//
//		void* pData = nullptr;
//		CD3DX12_RANGE readRange(0, 0);
//		m_globalIndexBuffer->Map(0, &readRange, &pData);
//		memcpy(pData, globalIdxs.data(), iByteSize);
//		m_globalIndexBuffer->Unmap(0, nullptr);
//
//		m_globalIBView.BufferLocation = m_globalIndexBuffer->GetGPUVirtualAddress();
//		m_globalIBView.Format = DXGI_FORMAT_R16_UINT;
//		m_globalIBView.SizeInBytes = iByteSize;
//	}
//
//	return E_NOTIMPL;
//}
//
//void MeshManager::InitializeBasicShapes()
//{
//	InitializeMesh_Triangle();
//}
//
//void MeshManager::InitializeMesh_Triangle()
//{
//	MeshData tri = CreateMesh_Triangle();
//	auto triID = m_meshLibrary.Add(tri);
//}
//
//void MeshManager::InitializeMesh_Square()
//{
//	MeshData square = CreateMesh_Square();
//	auto squareID = m_meshLibrary.Add(square);
//}
//
//void MeshManager::InitializeMesh_Cube()
//{
//	MeshData cube = CreateMesh_Cube();
//	auto cubeID = m_meshLibrary.Add(cube);
//
//}
//
//



bool MeshData::LoadFromFile(const std::string& path)
{
	OutputDebugStringA(">> Entering MeshData::LoadFromFile()\n");

	tinyobj::attrib_t					attrib;
	std::vector<tinyobj::shape_t>		shapes;
	std::vector<tinyobj::material_t>	materials;
	std::string warn, err;
	/*if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str(), nullptr, true, true)) 
	{
		OutputDebugStringA(warn.c_str());
		OutputDebugStringA(err.c_str());
		return false;
	}*/
	std::string baseDir = std::filesystem::path(path).remove_filename().string();

	bool ok = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err,
		path.c_str(), baseDir.empty() ? nullptr : baseDir.c_str(), /*Triangulate*/true, /*FallBack*/true); // Triangulate = triangles geometry ; FB = default color
	// Affiche warn/err même si ok==true
	if (!warn.empty())   OutputDebugStringA(warn.c_str());
	if (!err.empty())    OutputDebugStringA(err.c_str());

	if (!ok)
	{
		OutputDebugStringA(">> LoadObj FAILED\n");
		return false;
	}
	OutputDebugStringA(">> LoadObj SUCCEEDED\n");

	//// DEBUG
	//for (size_t mi = 0; mi < materials.size(); ++mi)
	//{
	//	auto& m = materials[mi];
	//	const char* tex = m.diffuse_texname.empty() ? "<empty>" : m.diffuse_texname.c_str();
	//	char buf[256];
	//	// Note bien le sizeof(buf) en second param
	//	sprintf_s(buf, sizeof(buf),
	//		"  Material[%zu]: name='%s', diffuse_texname='%s'\n",
	//		mi, m.name.c_str(), tex);
	//	OutputDebugStringA(buf);
	////}
	//// DEBUG
	//// 1) juste après avoir appelé LoadObj, vérifie le nombre de coordonnées UV brutes :
	//{
	//	char buf[128];
	//	sprintf_s(buf, sizeof(buf),
	//		"OBJ '%s' has %zu raw texcoords\n",
	//		path.c_str(),
	//		attrib.texcoords.size() / 2);
	//	OutputDebugStringA(buf);
	//}

	// 2) avant la déduplication, imprime quelques indices de texcoord :
	//for (size_t f = 0; f < std::min<size_t>(indices.size(), 6); ++f)
	//{
	//	auto idx = indices[f];
	//	char buf[128];
	//	sprintf_s(buf, sizeof(buf),
	//		" face[%zu] -> v=%d, vt=%d, vn=%d\n",
	//		f,
	//		idx.vertex_index,
	//		idx.texcoord_index,
	//		idx.normal_index);
	//	OutputDebugStringA(buf);
	//}



	// store material names
	materialNames.clear();
	for (auto& m : materials)
		materialNames.push_back(m.diffuse_texname);
	
	// dedupe and build global vertex list
	vertices.clear(); indices.clear(); subMeshes.clear();
	std::unordered_map<VertexParam, uint32_t> uniqueVertices;
	uint32_t indexCursor = 0;
	for (size_t s = 0; s < shapes.size(); ++s)
	{
		auto& mesh = shapes[s].mesh;
		SubMesh sub;
		sub.IndexOffset = (uint32_t)indices.size();
		sub.MaterialID = (uint32_t)mesh.material_ids.empty() ? 0u : mesh.material_ids[0];
		for (size_t f = 0; f < mesh.indices.size(); ++f)
		{
			auto idx = mesh.indices[f];
			VertexParam v{};
			size_t vi = 3 * idx.vertex_index;
			v.Position = { attrib.vertices[vi], attrib.vertices[vi + 1], attrib.vertices[vi + 2] };
			if (!attrib.normals.empty()) {
				size_t ni = 3 * idx.normal_index;
				v.Normal = { attrib.normals[ni], attrib.normals[ni + 1], attrib.normals[ni + 2] };
			}
			if (!attrib.texcoords.empty()) {
				size_t ti = 2 * idx.texcoord_index;
				v.TexCoord = { attrib.texcoords[ti], attrib.texcoords[ti + 1] };
				//{
				//	// DEBUG
				//	char buf[128];
				//	sprintf_s(buf, sizeof(buf),
				//		"  build vert[%zu]  UV=(%.3f, %.3f)\n",
				//		vertices.size(),
				//		v.TexCoord.x, v.TexCoord.y);
				//	OutputDebugStringA(buf);
				//}
			}
			auto it = uniqueVertices.find(v);
			if (it == uniqueVertices.end())
			{
				uint32_t newIndex = (uint32_t)vertices.size();
				uniqueVertices[v] = newIndex;
				vertices.push_back(v);
				indices.push_back(newIndex);
			}
			else
			{
				indices.push_back(it->second);
			}
		}

		sub.IndexCount = (uint32_t)indices.size() - sub.IndexOffset;
		subMeshes.push_back(sub);
	}
	return true;
}

void MeshManager::Init(GraphicsDevice* graphicsDevice, TextureManager* textureManager)
{
	mp_graphicsDevice = graphicsDevice;
	mp_textureManager = textureManager;

	// basic shapes
	MeshData tri	= CreateMesh_Triangle(); 
	tri.materialNames = { "" };               // pas de nom de texture
	tri.materialTextureIDs = { 0 };
	m_meshLibrary.Add(tri);

	MeshData sq		= CreateMesh_Square();
	sq.materialNames = { "" };               // pas de nom de texture
	sq.materialTextureIDs = { 0 };
	
	m_meshLibrary.Add(sq);

	MeshData cb		= CreateMesh_Cube();
	cb.materialNames = { "" };               // pas de nom de texture
	cb.materialTextureIDs = { 0 };
	m_meshLibrary.Add(cb);

	LoadMeshFromFile("../LyonPlexLib/Ressources/ArbreTest.obj");
	LoadMeshFromFile("../LyonPlexLib/Ressources/Cepha1.obj");
	BuildAndUploadGlobalBuffers();
}

void MeshManager::LoadMeshFromFile(const std::string& path)
{

	MeshData mesh;
    if (!mesh.LoadFromFile(path))
        return;
    // after loading geometry & material names, load textures:
    mesh.materialTextureIDs.resize(mesh.materialNames.size());
    for (size_t i = 0; i < mesh.materialNames.size(); ++i)
    {
        const auto& name = mesh.materialNames[i];
        // assume relative to path's folder
        std::string baseDir = std::filesystem::path(path).remove_filename().string();
        mesh.materialTextureIDs[i] = mp_textureManager->LoadTexture(baseDir + name);
    }
	// DEBUG
	for (size_t i = 0; i < std::min<size_t>(mesh.vertices.size(), 6); ++i)
	{
		auto& vp = mesh.vertices[i];
		char buf[128];
		sprintf_s(buf, sizeof(buf),
			"Final Vertex[%zu]: UV=(%.3f, %.3f)\n",
			i, vp.TexCoord.x, vp.TexCoord.y);
		OutputDebugStringA(buf);
	}
    m_meshLibrary.Add(mesh);
}

HRESULT MeshManager::BuildAndUploadGlobalBuffers()
{
	// collect all MeshData into global arrays
	m_globalVertices.clear();
	m_globalIndices.clear();

	for (uint32_t id = 0; id < m_meshLibrary.Count(); ++id)
	{
		auto& md = m_meshLibrary.Get(id);
		// record offsets
		md.vOffset = static_cast<uint32_t>(m_globalVertices.size());
		md.iOffset = static_cast<uint32_t>(m_globalIndices.size());

		// append vertices
		m_globalVertices.insert(
			m_globalVertices.end(),
			md.vertices.begin(), md.vertices.end());

		// append indices (corrected by vOffset)
		for (auto i : md.indices)
		{
			m_globalIndices.push_back(static_cast<uint32_t>(i + md.vOffset));
		}

		// record counts
		md.vSize = static_cast<uint32_t>(md.vertices.size());
		md.iSize = static_cast<uint32_t>(md.indices.size());
	}

	// upload to GPU buffers
	UINT vByteSize = static_cast<UINT>(m_globalVertices.size() * sizeof(VertexParam));
	UINT iByteSize = static_cast<UINT>(m_globalIndices.size() * sizeof(uint32_t));

	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);

	// Vertex Buffer
	{
		auto vbDesc = CD3DX12_RESOURCE_DESC::Buffer(vByteSize);
		ThrowIfFailed(mp_graphicsDevice->GetDevice()
			->CreateCommittedResource(
				&heapProps, D3D12_HEAP_FLAG_NONE, &vbDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
				IID_PPV_ARGS(&m_globalVertexBuffer)));

		void* pData = nullptr;
		CD3DX12_RANGE readRange(0, 0);
		m_globalVertexBuffer->Map(0, &readRange, &pData);
		memcpy(pData, m_globalVertices.data(), vByteSize);
		m_globalVertexBuffer->Unmap(0, nullptr);

		m_globalVBView.BufferLocation = m_globalVertexBuffer->GetGPUVirtualAddress();
		m_globalVBView.StrideInBytes = sizeof(VertexParam);
		m_globalVBView.SizeInBytes = vByteSize;
	}

	// Index Buffer
	{
		auto ibDesc = CD3DX12_RESOURCE_DESC::Buffer(iByteSize);
		ThrowIfFailed(mp_graphicsDevice->GetDevice()
			->CreateCommittedResource(
				&heapProps, D3D12_HEAP_FLAG_NONE, &ibDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
				IID_PPV_ARGS(&m_globalIndexBuffer)));

		void* pData = nullptr;
		CD3DX12_RANGE readRange(0, 0);
		m_globalIndexBuffer->Map(0, &readRange, &pData);
		memcpy(pData, m_globalIndices.data(), iByteSize);
		m_globalIndexBuffer->Unmap(0, nullptr);

		m_globalIBView.BufferLocation = m_globalIndexBuffer->GetGPUVirtualAddress();
		m_globalIBView.Format = DXGI_FORMAT_R32_UINT;
		m_globalIBView.SizeInBytes = iByteSize;
	}

	return S_OK;
}
