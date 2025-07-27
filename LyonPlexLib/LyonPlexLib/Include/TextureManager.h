#pragma once

#include "ResourceManager.h"
#include "GraphicsDevice.h"
#include "DescriptorManager.h"

//#include <d3d12.h>
#include <filesystem>

//#include "WICTextureLoader.h"   // DirectXTK12 helper
//#include "DDSTextureLoader.h"   // DirectXTK12 helper
#include "../../ExternalLib/DirectXTK12-main/Inc/WICTextureLoader.h"
#include "../../ExternalLib/DirectXTK12-main/Inc/DDSTextureLoader.h"

#include "ResourceUploadBatch.h"   // DirectXTK12 helper

//using Microsoft::WRL::ComPtr;
//using namespace DirectX;

//-----------------------------------------------------------------------------//
// TextureData: holds GPU resource + descriptor index
//-----------------------------------------------------------------------------//
struct TextureData {
    ComPtr<ID3D12Resource>  resource;
    size_t                  descriptorIndex = SIZE_MAX;
    D3D12_SRV_DIMENSION     dimension = D3D12_SRV_DIMENSION_TEXTURE2D;

    bool LoadFromFile(const std::string& path)
    {
        // suppr ?
        return true;
    }
    void Unload()
    {
        // suppr ?
    }
};

//-----------------------------------------------------------------------------//
// TextureManager: loads and caches textures via ResourceManager<TextureData>
//-----------------------------------------------------------------------------//
class TextureManager {
public:
    using TextureID = ResourceManager<TextureData, std::string>::ResourceID;


    void Init(GraphicsDevice* graphicsDevice, DescriptorManager* descriptorManager);

    // Load or retrieve existing texture       2D ONLY !!
    TextureID LoadTexture(const std::string& key);

    // Load a cube texture (DDS with cubemap)
    TextureID LoadCubeTexture(const std::string& key);

    // Retrieve GPU handle for a texture
    D3D12_GPU_DESCRIPTOR_HANDLE GetSrvGpuHandle(TextureID id) const;

private:
    ResourceManager<TextureData, std::string> m_textures;
    GraphicsDevice* m_graphicsDevice;
    DescriptorManager* m_descMgr;

    // internal helper to create SRV
    void CreateShaderResourceView(TextureID id);
};
