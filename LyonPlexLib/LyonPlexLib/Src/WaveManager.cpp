#include "pch.h"
#include "WaveManager.h"

void WaveManager::Init(GraphicsDevice* graphicsDevice, TextureManager* textureManager)
{
	mp_graphicsDevice = graphicsDevice;
	mp_textureManager = textureManager;
}

void WaveManager::InitWave()
{
	m_Vertices =
	{
	{{-1, 0, -1}, {0, 0}, {0, 1, 0}},
	{{ 1, 0, -1}, {1, 0}, {0, 1, 0}},
	{{ 1, 0,  1}, {1, 1}, {0, 1, 0}},
	{{-1, 0,  1}, {0, 1}, {0, 1, 0}}
	};

	m_Indices = { 0,1,2, 0,2,3 };

	//MeshData cb = CreateMesh_Wave();

	BuildAndUploadBuffers();	
}

void WaveManager::Update(float deltaTime)
{
	// 1) calcul du scroll
	m_scrollOffset.x += deltaTime * 0.05f;
	m_scrollOffset.y += deltaTime * 0.03f;

	// 2) upload du CB
	//UINT8* pData = nullptr;
	//CD3DX12_RANGE readRange(0, 0);
	//m_constantBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pData));
	//memcpy(m_mappedCBData, &worldViewProj, sizeof(worldViewProj));
	//memcpy(m_mappedCBData + sizeof(worldViewProj), &scrollOffset, sizeof(scrollOffset));
	//m_constantBuffer->Unmap(0, nullptr);

	UINT64 count = 0;

	ComponentMask mask3D = 1ULL << WaveComponent::StaticTypeID;
	m_ECS->ForEach(mask3D, [&](Entity ent)
		{
			count++;

			auto* wavec = m_ECS->GetComponent<WaveComponent>(ent);
			if (wavec->cubeMapID == 0 || wavec->normalMapID == 0)
			{
				wavec->normalMapID = mp_textureManager->LoadTexture("../SampleProject/Ressources/Environnement3D/Water/WaterNormal.dds");
				wavec->cubeMapID = mp_textureManager->LoadCubeTexture("../SampleProject/Ressources/Environnement3D/Water/CubeMap.dds");
			}
			//// 2) Calculer la matrice monde (XMMATRIX) depuis tc->position/rotation/scale
			//XMMATRIX world = m_ECS->m_systemMgr.GetTransformSystem().worldMatrices[ent.id];

			//// 3) Construire le struct ConstantBuffData
			//CBData cbData;
			//XMStoreFloat4x4(&cbData.World, XMMatrixTranspose(world));

			//cbData.scrollOffset = m_scrollOffset;

			//memcpy(m_mappedCBData, &cbData, sizeof(CBData));
		});

	m_waveCount = count;

}

void WaveManager::LoadTexture(TextureManager::TextureID id)
{

}

MeshData WaveManager::CreateMesh_Wave()
{
	//m_Vertices =
	//{
	//{{-1, 0, -1}, {0, 0}},
	//{{ 1, 0, -1}, {1, 0}},
	//{{ 1, 0,  1}, {1, 1}},
	//{{-1, 0,  1}, {0, 1}}
	//};

	//m_Indices = { 0,1,2, 0,2,3 };

	return MeshData();
}


void WaveManager::UploadData(void const* _Src, UINT64 offset)
{
	memcpy((BYTE*)m_mappedCBData + offset, _Src, sizeof(CBData));
}

HRESULT WaveManager::BuildAndUploadBuffers()
{
	// upload to GPU buffers
	UINT vByteSize = static_cast<UINT>((sizeof(WaveVertex) + 255) & ~255 );
	//UINT vByteSize = static_cast<UINT>(m_Vertices.size() * sizeof(WaveVertex));
	UINT iByteSize = static_cast<UINT>((sizeof(uint32_t) + 255) & ~255);
	//UINT iByteSize = static_cast<UINT>(m_Indices.size() * sizeof(uint32_t));

	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);

	// Vertex Buffer
	{
		auto vbDesc = CD3DX12_RESOURCE_DESC::Buffer(vByteSize);
		ThrowIfFailed(mp_graphicsDevice->GetDevice()
			->CreateCommittedResource(
				&heapProps, D3D12_HEAP_FLAG_NONE, &vbDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
				IID_PPV_ARGS(&m_VertexBuffer)));

		void* pData = nullptr;
		CD3DX12_RANGE readRange(0, 0);
		m_VertexBuffer->Map(0, &readRange, &pData);
		memcpy(pData, m_Vertices.data(), vByteSize);
		m_VertexBuffer->Unmap(0, nullptr);

		m_VBView.BufferLocation = m_VertexBuffer->GetGPUVirtualAddress();
		m_VBView.StrideInBytes = sizeof(WaveVertex);
		m_VBView.SizeInBytes = vByteSize;
	}

	// Index Buffer
	{
		auto ibDesc = CD3DX12_RESOURCE_DESC::Buffer(iByteSize);
		ThrowIfFailed(mp_graphicsDevice->GetDevice()
			->CreateCommittedResource(
				&heapProps, D3D12_HEAP_FLAG_NONE, &ibDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
				IID_PPV_ARGS(&m_IndexBuffer)));

		void* pData = nullptr;
		CD3DX12_RANGE readRange(0, 0);
		m_IndexBuffer->Map(0, &readRange, &pData);
		memcpy(pData, m_Indices.data(), iByteSize);
		m_IndexBuffer->Unmap(0, nullptr);

		m_IBView.BufferLocation = m_IndexBuffer->GetGPUVirtualAddress();
		m_IBView.Format = DXGI_FORMAT_R32_UINT;
		m_IBView.SizeInBytes = iByteSize;
	}


	UINT64 mexWaterEntity = 100;

	// Calcule la taille totale
	UINT64 totalSize = UINT64(m_cbSize) * mexWaterEntity * UINT64(mp_graphicsDevice->GetFrameCount());

	// Libère l'ancien buffer si présent
	if (m_constantBuffer)
	{
		m_constantBuffer->Unmap(0, nullptr);
		m_constantBuffer.Reset();
		m_mappedCBData = nullptr;
	}

	// Propriétés et description
	CD3DX12_HEAP_PROPERTIES heapProps2(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC   bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(totalSize);

	// Création
	HRESULT hr = mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapProps2, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_constantBuffer));
	if (FAILED(hr))
	{
		throw std::runtime_error("Échec création constant buffer");
	}

	// Mapping CPU -> GPU
	CD3DX12_RANGE readRange(0, 0);
	hr = m_constantBuffer->Map(0, &readRange, reinterpret_cast<void**>(&m_mappedCBData));
	if (FAILED(hr))
	{
		throw std::runtime_error("Échec mapping constant buffer");
	}



	return S_OK;
}
