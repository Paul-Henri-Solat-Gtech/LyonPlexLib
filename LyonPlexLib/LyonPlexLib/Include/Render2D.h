#pragma once

#include "IRender.h"
#include "GraphicsPipeline.h"
#include "TextureManager.h"
#include "MeshManager.h"

// Constant buffer for projection (ortho) - slot b0
struct CB2D_Proj
{
    DirectX::XMFLOAT4X4 proj;      // slot b0 (juste ortho)
};

// Constant buffer per-object (world + material index) - slot b1
struct CB2D_World
{
    DirectX::XMFLOAT4X4     world;          // Matrice world (scale, rotation, translation 2D)
    //DirectX::XMFLOAT4     TintColor;        // Couleur/tint RGBA
    uint32_t                materialIndex = 0;  // 4 bytes, occupe le premier float du slot suivant
    float                   padding[3];                // 12 bytes de « rembourrage » pour remplir le slot 16 bytes
};

class Render2D : public IRender
{
public:
    bool Init(HWND windowHandle, ECSManager* ECS, GraphicsDevice* graphicsDevice, DescriptorManager* descriptorManager, CommandManager* commandManager) override;


    void Resize(int w, int h) override;
    void RecordCommands() override;
    void CreatePipeline() override;


    void Release();

private:
    bool InitConstantBuffer();
    void UpdateCbParams();

    // memes dependances
    GraphicsDevice* mp_graphicsDevice = nullptr;
    DescriptorManager* mp_descriptorManager = nullptr;
    CommandManager* mp_commandManager = nullptr;
    ECSManager* m_ECS = nullptr;

    // pipeline 2D partagee
    GraphicsPipeline    m_graphicsPipeline;

    // managers 2D
    MeshManager			m_meshManager;
    TextureManager*     m_textureManager = nullptr;

    // constant buffer view ortho
    ComPtr<ID3D12Resource>   m_cbProjUpload = nullptr;   // pour la matrice ortho
    void*                    m_mappedProj = nullptr;

    // constant buffer object
    ComPtr<ID3D12Resource>   m_cbUpload = nullptr;
    void*                    m_mappedCB = nullptr;
    UINT                     m_cbSize = Align256(sizeof(CB2D_World));




    // Temporary upload buffer for triangle test
    ComPtr<ID3D12Resource> m_tempUploadBuffer;
    void* m_mappedTemp = nullptr;

};
