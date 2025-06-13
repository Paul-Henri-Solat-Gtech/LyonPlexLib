#include "pch.h"
#include "GraphicsPipeline.h"

#include "../../ExternalLib/DirectXTK12-main/Src/d3dx12.h"


void GraphicsPipeline::Init(GraphicsDevice* graphicsDevice, DescriptorManager* descriptorManager, CommandManager* commandManager)
{
    mp_graphicsDevice = graphicsDevice;
    mp_descriptorManager = descriptorManager;
    mp_commandManager = commandManager;
}

void GraphicsPipeline::CreatePipeline()
{
    CreateRootSignature();
    CompileShader();
    CreatePipelineStateObject();
}

void GraphicsPipeline::CreateRootSignature()
{
    // La range[] sert à placer toutes les textures dans un meme slot de rootParam

    // 1. Définit un descriptor range pour SRV (RangeCount = nombre max de textures)
    CD3DX12_DESCRIPTOR_RANGE1  ranges[1];
    // Table 0 : textures 2D
    ranges[0].Init(
        D3D12_DESCRIPTOR_RANGE_TYPE_SRV,   // type
        15,                              // NumDescriptors
        0,                                 // BaseShaderRegister (t0)
        0,                                 // register space
        D3D12_DESCRIPTOR_RANGE_FLAG_NONE,
        0                                  // offset in descriptors (auto) -> autre possibilite : D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND
    );

    // 2. Définit un descriptor range pour Sampler (optionnel)
    CD3DX12_DESCRIPTOR_RANGE1 samplerRanges[1];
    samplerRanges[0].Init(
        D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER,
        1,      // un sampler "linear wrap" par défaut
        0,      // s0
        0
    );          // A REVOIR


    // 0) shader with camera
    // 1) Definition des deux root parameters (slot b0 et b1)
    CD3DX12_ROOT_PARAMETER1 rootParams[4];
    // Slot 0 : Camera View & Proj
    rootParams[0].InitAsConstantBufferView(0); // <- b0 côte shader pour camera (view & proj)

    // Slot 1 : Object world matrix
    rootParams[1].InitAsConstantBufferView(1); // <- b1 côte shader pour transform (world)

    // Slot 2 : SRV descriptor table (textures)
    rootParams[2].InitAsDescriptorTable(
        1,          // RangeCount
        &ranges[0], // pointeur sur notre range SRV
        D3D12_SHADER_VISIBILITY_PIXEL
    );
    // Slot 3 : Sampler descriptor table
    rootParams[3].InitAsDescriptorTable(
        1,
        &samplerRanges[0],
        D3D12_SHADER_VISIBILITY_PIXEL
    );
    /* rootParams supplementaires   */


    //// 2) Construire la root signature
    D3D12_VERSIONED_ROOT_SIGNATURE_DESC rootSigDesc = {};
    rootSigDesc.Version = D3D_ROOT_SIGNATURE_VERSION_1_1;
    rootSigDesc.Desc_1_1.NumParameters = _countof(rootParams);
    rootSigDesc.Desc_1_1.pParameters = rootParams;
    rootSigDesc.Desc_1_1.NumStaticSamplers = 0;         // A REVOIR
    rootSigDesc.Desc_1_1.pStaticSamplers = nullptr;     // A REVOIR
    rootSigDesc.Desc_1_1.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    // 3) Serialiser et creer
    ComPtr<ID3DBlob> signature, error;
    HRESULT hr = D3D12SerializeVersionedRootSignature(&rootSigDesc, &signature, &error);

    if (FAILED(hr))
    {
        // Si errorBlob n’est pas null, on peut afficher son contenu (c'est un ID3DBlob)
        if (error)
        {
            // Le message d’erreur est au format ASCII (car D3DCompile et D3D12Serialize renvoient des blobs d’erreur ASCII)
            const char* msg = reinterpret_cast<const char*>(error->GetBufferPointer());
            OutputDebugStringA("D3D12SerializeRootSignature failed:\n");
            OutputDebugStringA(msg);
            OutputDebugStringA("\n");
        }
        else
        {
            OutputDebugStringA("D3D12SerializeRootSignature failed: aucun error blob retourne.\n");
        }
        // Ici, vous pouvez choisir de retourner ou de planter proprement
        return;
    }
    mp_graphicsDevice->GetDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature));
}

void GraphicsPipeline::CompileShader()
{

    // Compilation des shaders

    // Ce bloc permet de vérifier si un chemin/fichier existe
   /* DWORD len = GetFullPathNameW(L"..\\LyonPlexLib\\Ressources\\PixelShader.hlsl", 0, nullptr, nullptr);
    std::wstring fullpath(len, L'\0');
    GetFullPathNameW(L"..\\LyonPlexLib\\Ressources\\PixelShader.hlsl", len, fullpath.data(), nullptr);
    MessageBoxW(nullptr, fullpath.c_str(), L"Full path", MB_OK);*/


    // ==> Déclare deux blobs distincts
 /*   ComPtr<ID3DBlob>  vsErrorBlob;
    ComPtr<ID3DBlob>  psErrorBlob;*/

    // 1) VS
    HRESULT hr = D3DCompileFromFile(
        L"../LyonPlexLib/Ressources/VertexShader.hlsl",
        nullptr, nullptr,
        "VSMain", "vs_5_1",
        D3DCOMPILE_ENABLE_STRICTNESS, 0,
        &m_vsBlob, &m_errorBlob);

    if (FAILED(hr)) {
        if (m_errorBlob) {
            std::string msg{ (char*)m_errorBlob->GetBufferPointer(),
                             m_errorBlob->GetBufferSize() };
            MessageBoxA(nullptr, msg.c_str(), "VS Compilation Error", MB_OK | MB_ICONERROR);
        }
        throw std::runtime_error("VS compilation failed");
    }

    // 2) PS (fichier ou entry pont corrigé)
    hr = D3DCompileFromFile(
        L"../LyonPlexLib/Ressources/VertexShader.hlsl", // ← fichier dédié
        nullptr, nullptr,
        "PSMain", "ps_5_1",
        D3DCOMPILE_ENABLE_STRICTNESS, 0,
        &m_psBlob, &m_errorBlob);

    if (FAILED(hr)) {
        // Affiche l'HRESULT hex et le blob d'erreur s'il y en a un
        std::ostringstream oss;
        oss << "PS compilation failed (hr = 0x"
            << std::hex << hr << ")\n";
        if (m_errorBlob) {
            oss << static_cast<char*>(m_errorBlob->GetBufferPointer());
        }
        MessageBoxA(nullptr, oss.str().c_str(), "Shader Error", MB_OK | MB_ICONERROR);
        throw std::runtime_error("PS compilation failed");
    }


}

void GraphicsPipeline::CreatePipelineStateObject()
{
    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
  { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0,   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
  { "COLOR",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
  { "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,    0, 28,  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
  /*{ "TEXCOORD",  1, DXGI_FORMAT_R32_UINT,        0, 36,  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }, Si textures differentes sur chaque pixel */
    };

    // 4) PSO
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.InputLayout = { inputLayout, _countof(inputLayout) };
    psoDesc.pRootSignature = m_rootSignature.Get();
    psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsBlob.Get());
    psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psBlob.Get());
    
    // ) Rasterizer State : on veut afficher la face extérieure, winding CCW = front
    D3D12_RASTERIZER_DESC rasterDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    rasterDesc.CullMode = D3D12_CULL_MODE_BACK;          // On élimine les faces arrière (celles qu'on ne veut pas voir)
    rasterDesc.FrontCounterClockwise = TRUE;             // CCW = face avant, CW = face arrière 
    rasterDesc.FillMode = D3D12_FILL_MODE_SOLID;         // Remplir normalement
    rasterDesc.DepthClipEnable = TRUE;

    psoDesc.RasterizerState = rasterDesc;

    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    
    // 5) Depth-Stencil State : ON et test LESS pour un cube « normal »
    D3D12_DEPTH_STENCIL_DESC depthDesc = {};
    depthDesc.DepthEnable = TRUE;
    depthDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
    depthDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
    depthDesc.StencilEnable = FALSE; // Pas de stencil pour l'instant

    psoDesc.DepthStencilState = depthDesc;

    // Render Target & Sample
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
    psoDesc.SampleDesc.Count = 1;

    // Ajouter params supplementaires

    mp_graphicsDevice->GetDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pipelineState));
}
