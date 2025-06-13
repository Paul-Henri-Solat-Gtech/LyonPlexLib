#include "pch.h"
#include "TextureManager.h"
#include <comdef.h>

using TextureID = ResourceManager<TextureData, std::string>::ResourceID;

void TextureManager::Init(GraphicsDevice* graphicsDevice, DescriptorManager* descriptorManager)
{
	m_graphicsDevice = graphicsDevice;
	m_descMgr = descriptorManager;
}

TextureID TextureManager::LoadTexture(const std::string& key)
{
    // Normalize extension
    auto ext = std::filesystem::path(key).extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    // Get or add resource entry
    TextureID id = m_textures.Load(key);
    TextureData& tex = m_textures.Get(id);

    // Already loaded?
    if (tex.resource)
        return id;

    // Convert to wide string
    std::wstring wpath(key.begin(), key.end());

    // Prepare DX12 upload batch
    ResourceUploadBatch uploadBatch(m_graphicsDevice->GetDevice().Get());
    uploadBatch.Begin();

    // DX12: use DirectXTK12 CreateWIC/DDS overloads
    HRESULT hr = S_OK;
    if (ext == ".dds") {
        hr = CreateDDSTextureFromFile(
            m_graphicsDevice->GetDevice().Get(),
            uploadBatch,
            wpath.c_str(),
            &tex.resource,
            true // generate mips if available
        );
    }
    else {
        hr = CreateWICTextureFromFile(
            m_graphicsDevice->GetDevice().Get(),
            uploadBatch,
            wpath.c_str(),
            &tex.resource,
            true // generate mips
        );
    }
    _com_error err(hr);
    std::wstring msg = err.ErrorMessage();
    OutputDebugStringW((L"Erreur DirectXTK: " + msg + L"\n").c_str());
    if (FAILED(hr)) {
        //m_textures.Remove(id);
        throw std::runtime_error("Failed to load texture: " + key);
    }

    // Create SRV descriptor in CPU heap
    D3D12_CPU_DESCRIPTOR_HANDLE srvCpu = m_descMgr->AllocateSrvCPU();
    m_graphicsDevice->GetDevice()->CreateShaderResourceView(
        tex.resource.Get(),
        nullptr,
        srvCpu
    );
    tex.descriptorIndex = m_descMgr->GetSrvNextOffset() - 1;

    // Execute the upload commands on the GPU queue
    auto uploadOp = uploadBatch.End(m_graphicsDevice->GetCommandQueue().Get());
    uploadOp.wait();

    return id;
}

D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::GetSrvGpuHandle(TextureID id) const
{
	UINT offset = static_cast<UINT>(m_textures.Get(id).descriptorIndex);
	auto base = m_descMgr->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart();
	return { base.ptr + offset * m_descMgr->GetSrvDescriptorSize() };
}