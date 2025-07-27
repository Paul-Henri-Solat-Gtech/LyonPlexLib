#include "pch.h"
#include "WaterPipeline.h"

void WaterPipeline::Init(GraphicsDevice* graphicsDevice, DescriptorManager* descriptorManager, CommandManager* commandManager)
{
	mp_graphicsDevice = graphicsDevice;
	mp_descriptorManager = descriptorManager;
	mp_commandManager = commandManager;
}


void WaterPipeline::CreatePipeline()
{
	CreateRootSignature();
	CompileShader();
	CreatePipelineStateObject();
}

void WaterPipeline::CreateRootSignature()
{



	// 1) Définition des descriptor ranges (un par SRV)
	CD3DX12_DESCRIPTOR_RANGE1 ranges[2];
	// Range pour la normal map (t0)
	ranges[0].Init(
		D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
		1,    // un seul descripteur
		0,    // register t0
		0,    // space 0
		D3D12_DESCRIPTOR_RANGE_FLAG_NONE,
		0);
	// Range pour la cubemap (t1)
	ranges[1].Init(
		D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
		1,    // un seul descripteur
		1,    // register t1
		0,    // space 0
		D3D12_DESCRIPTOR_RANGE_FLAG_NONE,
		0);

	// 2) Création des root parameters
	CD3DX12_ROOT_PARAMETER1 rootParams[4];
	// b0 : constant buffer (worldViewProj, scrollOffset)
	rootParams[0].InitAsConstantBufferView(
		/*shaderRegister=*/0,
		/*space=*/0,
		D3D12_ROOT_DESCRIPTOR_FLAG_NONE,
		D3D12_SHADER_VISIBILITY_ALL);
	// b1 : constant buffer (worldViewProj, scrollOffset)
	rootParams[1].InitAsConstantBufferView(
		/*shaderRegister=*/1,
		/*space=*/0,
		D3D12_ROOT_DESCRIPTOR_FLAG_NONE,
		D3D12_SHADER_VISIBILITY_VERTEX);
	// t0 : table SRV pour la normal map
	rootParams[2].InitAsDescriptorTable(
		/*numRanges=*/1,
		&ranges[0],
		D3D12_SHADER_VISIBILITY_PIXEL);
	// t1 : table SRV pour la cubemap
	rootParams[3].InitAsDescriptorTable(
		/*numRanges=*/1,
		&ranges[1],
		D3D12_SHADER_VISIBILITY_PIXEL);

	CD3DX12_STATIC_SAMPLER_DESC staticSampler(
		0,                                       // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR,        // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,        // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,        // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP);       // addressW
	
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_1(
		_countof(rootParams), rootParams,
		1, &staticSampler,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	// Création de la root signature
	ComPtr<ID3DBlob> signature;
	ComPtr<ID3DBlob> error;
	HRESULT hrSer = D3DX12SerializeVersionedRootSignature(
		&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_1,
		&signature, &error);

	if (FAILED(hrSer)) {
		if (error) {
			OutputDebugStringA("RootSignature serialization error:\n");
			OutputDebugStringA(static_cast<char*>(error->GetBufferPointer()));
		}
		throw std::runtime_error("RootSignature serialization failed");
	}
	if (error) {
		OutputDebugStringA("Serialization warning:\n");
		OutputDebugStringA(static_cast<char*>(error->GetBufferPointer()));
	}

	HRESULT hrRS = mp_graphicsDevice->GetDevice()->CreateRootSignature(
		0, signature->GetBufferPointer(), signature->GetBufferSize(),
		IID_PPV_ARGS(&m_rootSignature));

	//if (FAILED(hrRS)) {
	//	OutputDebugStringA("Échec CreateRootSignature\n");
	//	throw std::runtime_error("CreateRootSignature failed");
	//	__debugbreak();
	//}
	if (FAILED(hrRS)) {
		char msg[512] = {};
		FormatMessageA(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, hrRS,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			msg, (sizeof(msg) / sizeof(char)) - 1,
			nullptr);
		OutputDebugStringA("CreateRootSignature failed (HRESULT): ");
		OutputDebugStringA(msg);
		throw std::runtime_error("CreateRootSignature failed");
	}


}

void WaterPipeline::CompileShader()
{


	// 1) VS
	HRESULT hr = D3DCompileFromFile(L"../LyonPlexLib/Ressources/WavesShader.hlsl", nullptr, nullptr, "VSMain", "vs_5_1", D3DCOMPILE_ENABLE_STRICTNESS, 0, &m_vsBlob, &m_errorBlob);

	if (FAILED(hr)) {
		if (m_errorBlob) {
			std::string msg{ (char*)m_errorBlob->GetBufferPointer(),
							 m_errorBlob->GetBufferSize() };
			MessageBoxA(nullptr, msg.c_str(), "VS Compilation Error", MB_OK | MB_ICONERROR);
		}
		throw std::runtime_error("VS compilation failed");
	}

	// 2) PS (fichier ou entry pont corrige)
	hr = D3DCompileFromFile(
		L"../LyonPlexLib/Ressources/WavesShader.hlsl",
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

void WaterPipeline::CreatePipelineStateObject()
{

	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
	{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0,   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,    0, 12,  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20,  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	// 4) PSO
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
	psoDesc.InputLayout = { inputLayout, _countof(inputLayout) };
	psoDesc.pRootSignature = m_rootSignature.Get();
	psoDesc.VS = CD3DX12_SHADER_BYTECODE(m_vsBlob.Get());
	psoDesc.PS = CD3DX12_SHADER_BYTECODE(m_psBlob.Get());

	// ) Rasterizer State : on veut afficher la face exterieure, winding CCW = front
	D3D12_RASTERIZER_DESC rasterDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	rasterDesc.CullMode = D3D12_CULL_MODE_BACK;          // On elimine les faces arriere (celles qu'on ne veut pas voir)	/!\/!\/!\	A REMETTRE SI PB DE PERFS /!\/!\/!\/
	//rasterDesc.CullMode = D3D12_CULL_MODE_NONE;          // On elimine aucune face
	rasterDesc.FrontCounterClockwise = TRUE;             // CCW = face avant, CW = face arriere 
	rasterDesc.FillMode = D3D12_FILL_MODE_SOLID;         // Remplir normalement
	//rasterDesc.DepthClipEnable = TRUE;
	rasterDesc.DepthClipEnable = FALSE;

	psoDesc.RasterizerState = rasterDesc;

	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	// enable alpha blending
	psoDesc.BlendState.RenderTarget[0].BlendEnable = TRUE;
	//psoDesc.BlendState.RenderTarget[0].BlendEnable = FALSE;
	psoDesc.BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	psoDesc.BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	psoDesc.BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	psoDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	// 5) Depth-Stencil State : ON et test LESS pour un cube « normal »
	D3D12_DEPTH_STENCIL_DESC depthDesc = {};
	//depthDesc.DepthEnable = FALSE;
	depthDesc.DepthEnable = TRUE;
	depthDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	depthDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	//depthDesc.StencilEnable = FALSE; // Pas de stencil pour l'instant

	psoDesc.DepthStencilState = depthDesc;

	// Render Target & Sample
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	//psoDesc.DSVFormat = DXGI_FORMAT_UNKNOWN;
	psoDesc.SampleDesc.Count = 1;

	// Ajouter params supplementaires

	HRESULT hr = mp_graphicsDevice->GetDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pipelineState));

	if (FAILED(hr))
	{
		// 1) Loguez l’HRESULT en hexadécimal
		char buffer[256];
		sprintf_s(buffer, "CreateGraphicsPipelineState failed: hr = 0x%08X\n", static_cast<unsigned>(hr));
		OutputDebugStringA(buffer);

		// 2) Dump quelques paramètres du PSO
		sprintf_s(buffer,
			" PSO Desc dump:\n"
			"  NumRenderTargets     = %u\n"
			"  RTVFormats[0]        = 0x%X\n"
			"  DSVFormat            = 0x%X\n"
			"  SampleDesc.Count     = %u\n"
			"  PrimitiveTopology    = %u\n"
			"  RootSignature ptr    = %p\n",
			psoDesc.NumRenderTargets,
			psoDesc.RTVFormats[0],
			psoDesc.DSVFormat,
			psoDesc.SampleDesc.Count,
			psoDesc.PrimitiveTopologyType,
			psoDesc.pRootSignature);
		OutputDebugStringA(buffer);

		// 3) (Optionnel) Pseudo?dump des states Blend/Depth/RS
		sprintf_s(buffer,
			"  Blend.Enable[0]      = %u\n"
			"  DepthEnable          = %u\n"
			"  CullMode             = %u\n",
			psoDesc.BlendState.RenderTarget[0].BlendEnable,
			psoDesc.DepthStencilState.DepthEnable,
			psoDesc.RasterizerState.CullMode
		);
		OutputDebugStringA(buffer);

		// 4) Vous pouvez aussi injecter un breakpoint ici si vous debuggez.
		__debugbreak();
	}
	else
	{
		OutputDebugStringA("PSO WATER cree avec succes.\n");
	}

}