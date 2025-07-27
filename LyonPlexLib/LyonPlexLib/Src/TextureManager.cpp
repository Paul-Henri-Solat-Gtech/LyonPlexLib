#include "pch.h"
#include "TextureManager.h"
#include <comdef.h>

#include "tiny_obj_loader.h"

using TextureID = ResourceManager<TextureData, std::string>::ResourceID;

void TextureManager::Init(GraphicsDevice* graphicsDevice, DescriptorManager* descriptorManager)
{
	m_graphicsDevice = graphicsDevice;
	m_descMgr = descriptorManager;

}
//
//TextureID TextureManager::LoadTexture(const std::string& key)
//{
//    // Normalize extension
//    auto ext = std::filesystem::path(key).extension().string();
//    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
//
//    // Get or add resource entry
//    TextureID id = m_textures.Load(key);
//    TextureData& tex = m_textures.Get(id);
//
//    // Already loaded?
//    if (tex.resource)
//        return id;
//
//    // Convert to wide string
//    std::wstring wpath(key.begin(), key.end());
//
//    // Prepare DX12 upload batch
//    ResourceUploadBatch uploadBatch(m_graphicsDevice->GetDevice().Get());
//    uploadBatch.Begin();
//
//    // DX12: use DirectXTK12 CreateWIC/DDS overloads
//    HRESULT hr = S_OK;
//    if (ext == ".dds") {
//        hr = CreateDDSTextureFromFile(
//            m_graphicsDevice->GetDevice().Get(),
//            uploadBatch,
//            wpath.c_str(),
//            &tex.resource,
//            true // generate mips if available
//        );
//        Utils::log("\n Resource .dds chargee \n");
//    }
//    else {
//        hr = CreateWICTextureFromFile(
//            m_graphicsDevice->GetDevice().Get(),
//            uploadBatch,
//            wpath.c_str(),
//            &tex.resource,
//            true // generate mips
//        );
//    }
//    _com_error err(hr);
//    std::wstring msg = err.ErrorMessage();
//    //OutputDebugStringW((L"Message DirectXTK: " + msg + L"\n").c_str());
//    if (FAILED(hr)) {
//        //m_textures.Remove(id);
//        throw std::runtime_error("Failed to load texture: " + key);
//    }
//
//    // Create SRV descriptor in CPU heap
//    D3D12_CPU_DESCRIPTOR_HANDLE srvCpu = m_descMgr->AllocateSrvCPU();
//    m_graphicsDevice->GetDevice()->CreateShaderResourceView(
//        tex.resource.Get(),
//        nullptr,
//        srvCpu
//    );
//    
//    tex.descriptorIndex = m_descMgr->GetSrvNextOffset() - 1;
//
//    // Execute the upload commands on the GPU queue
//    auto uploadOp = uploadBatch.End(m_graphicsDevice->GetCommandQueue().Get());
//    uploadOp.wait();
//
//    return id;
//}


TextureID TextureManager::LoadTexture(const std::string& key)
{
    // register as 2D
    auto id = m_textures.Load(key);
    auto& tex = m_textures.Get(id);
    if (tex.resource)
        return id;

    // Mark dimension
    tex.dimension = D3D12_SRV_DIMENSION_TEXTURE2D;

    // Load from file (use DirectXTK CreateWICTextureFromFile)
    std::wstring wpath = std::filesystem::path(key).wstring();
    ResourceUploadBatch uploadBatch(m_graphicsDevice->GetDevice().Get());
    uploadBatch.Begin();
    HRESULT hr = CreateWICTextureFromFile(
        m_graphicsDevice->GetDevice().Get(),
        uploadBatch,
        wpath.c_str(),
        &tex.resource,
        true);
    if (FAILED(hr)) throw std::runtime_error("Failed to load 2D texture: " + key);
    auto uploadOp = uploadBatch.End(m_graphicsDevice->GetCommandQueue().Get());
    uploadOp.wait();

    // Create SRV
    CreateShaderResourceView(id);
    return id;
}

TextureID TextureManager::LoadCubeTexture(const std::string& key)
{
    auto id = m_textures.Load(key);
    auto& tex = m_textures.Get(id);
    if (tex.resource)
        return id;

    // Mark dimension as cube
    tex.dimension = D3D12_SRV_DIMENSION_TEXTURECUBE;

    std::wstring wpath = std::filesystem::path(key).wstring();
    ResourceUploadBatch uploadBatch(m_graphicsDevice->GetDevice().Get());
    uploadBatch.Begin();
    HRESULT hr = CreateDDSTextureFromFile(
        m_graphicsDevice->GetDevice().Get(),
        uploadBatch,
        wpath.c_str(),
        &tex.resource,
        true);
    if (FAILED(hr)) throw std::runtime_error("Failed to load cube texture: " + key);
    auto uploadOp = uploadBatch.End(m_graphicsDevice->GetCommandQueue().Get());
    uploadOp.wait();

    // Create SRV
    CreateShaderResourceView(id);

    // DEBUG
    auto d = tex.resource->GetDesc();
    char buf[256];
    sprintf_s(buf,
        "\n\nDesc: Dimension = %u, ArraySize = %u, MipLevels = %u, Width = %llu, Height = %llu\n\n",
        (UINT)d.Dimension,
        (UINT)d.DepthOrArraySize,   // doit valoir 6
        (UINT)d.MipLevels,
        (unsigned long long)d.Width,
        (unsigned long long)d.Height
    );
    OutputDebugStringA(buf);


    return id;
}

void TextureManager::CreateShaderResourceView(TextureID id)
{
    auto& tex = m_textures.Get(id);
    // Allocate descriptor
    D3D12_CPU_DESCRIPTOR_HANDLE srvCpu = m_descMgr->AllocateSrvCPU();
    // Describe SRV
    D3D12_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    desc.Format = tex.resource->GetDesc().Format;
    desc.ViewDimension = tex.dimension;
    if (tex.dimension == D3D12_SRV_DIMENSION_TEXTURE2D) {
        desc.Texture2D.MostDetailedMip = 0;
        desc.Texture2D.MipLevels = tex.resource->GetDesc().MipLevels;
        desc.Texture2D.ResourceMinLODClamp = 0;
    }
    else if (tex.dimension == D3D12_SRV_DIMENSION_TEXTURECUBE) { // TEXTURECUBE
        desc.TextureCube.MostDetailedMip = 0;
        desc.TextureCube.MipLevels = tex.resource->GetDesc().MipLevels;
        desc.TextureCube.ResourceMinLODClamp = 0;
    }
    // Create SRV
    m_graphicsDevice->GetDevice()->CreateShaderResourceView(
        tex.resource.Get(),
        &desc,
        srvCpu);
    // Store index
    tex.descriptorIndex = m_descMgr->GetSrvNextOffset() - 1;
}


D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::GetSrvGpuHandle(TextureID id) const
{
	UINT offset = static_cast<UINT>(m_textures.Get(id).descriptorIndex);
	auto base = m_descMgr->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart();
	return { base.ptr + offset * m_descMgr->GetSrvDescriptorSize() };
}