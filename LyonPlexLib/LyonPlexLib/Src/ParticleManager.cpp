//#include "pch.h"
//#include "ParticleManager.h"
#include "SceneResources.h"
//
//
//// Compile helper
//static ComPtr<ID3DBlob> CompileShader(const std::wstring& file, const std::string& entry, const std::string& target)
//{
//	ComPtr<ID3DBlob> code, errors;
//	HRESULT hr = D3DCompileFromFile(file.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), target.c_str(), 0, 0, &code, &errors);
//
//	if (errors) OutputDebugStringA((char*)errors->GetBufferPointer());
//	assert(SUCCEEDED(hr));
//	return code;
//}
//
//void ParticleManager::CreateParticleBuffers()
//{
//	// default buffer
//
//	const UINT elementSize = sizeof(Particle);
//	D3D12_RESOURCE_DESC descDefault = CD3DX12_RESOURCE_DESC::Buffer(elementSize * kMaxParticles);
//	descDefault.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
//	auto heapPropDEFAULT = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
//	mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapPropDEFAULT, D3D12_HEAP_FLAG_NONE, &descDefault, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&g_particleBuffer));
//
//	// upload buffer
//	D3D12_RESOURCE_DESC descUpload = CD3DX12_RESOURCE_DESC::Buffer(elementSize * kMaxParticles);
//
//	auto heapPropUPLOAD = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
//	mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapPropUPLOAD, D3D12_HEAP_FLAG_NONE, &descUpload, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&g_particleUploadBuffer));
//
//}
//
//void ParticleManager::MapUploadBuffer(TextureManager* textureManager)
//{
//	//Particle* init = nullptr;
//	//g_particleUploadBuffer->Map(0, nullptr, (void**)&init);
//	//for (UINT i = 0; i < kMaxParticles; ++i)
//	//{
//	//	init[i].age = 1e6f;
//	//	init[i].lifetime = 10.0f;
//	//	// tu peux aussi zero les autres champs si tu veux :
//	//	init[i].position = { 0,0,0 };
//	//	init[i].velocity = { 0,0,0 };
//	//	init[i].color = { 1,1,1,1 };
//	//	init[i].size = 1.0f;
//	//}
//	//g_particleUploadBuffer->Unmap(0, nullptr);
//
//
//	//auto cb = CD3DX12_RESOURCE_BARRIER::Transition(
//	//	g_particleBuffer.Get(),
//	//	D3D12_RESOURCE_STATE_COMMON,
//	//	D3D12_RESOURCE_STATE_COPY_DEST);
//	//mp_cmdManager->GetCommandList()->ResourceBarrier(1, &cb);
//
//	//mp_cmdManager->GetCommandList()->CopyResource(g_particleBuffer.Get(), g_particleUploadBuffer.Get());
//
//	//mp_descriptorManager->CreateBufferSRV(
//	//	g_particleBuffer.Get(),
//	//	kMaxParticles,
//	//	sizeof(Particle)
//	//);
//
//	//D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
//	//	g_particleBuffer.Get(),
//	//	D3D12_RESOURCE_STATE_COPY_DEST,
//	//	D3D12_RESOURCE_STATE_UNORDERED_ACCESS
//	//);
//	//mp_cmdManager->GetCommandList()->ResourceBarrier(1, &barrier);
//
//
//		// 1) Map l’upload-buffer et écrire la particule manuelle
//	Particle* mapped = nullptr;
//	D3D12_RANGE readRange{ 0, 0 };
//	HRESULT hr = g_particleUploadBuffer->Map(0, &readRange, reinterpret_cast<void**>(&mapped));
//	if (FAILED(hr) || !mapped) {
//		OutputDebugStringA("Erreur MapUploadBuffer(): Map failed\n");
//		return;
//	}
//	// Initialise une seule particule
//	mapped[0].position = { 0.0f, 0.0f, 5.0f };
//	mapped[0].size = 1.0f;
//	mapped[0].color = { 1, 1, 1, 1 };
//	mapped[0].age = 0;
//	mapped[0].lifetime = 10.0f;
//	g_particleUploadBuffer->Unmap(0, nullptr);
//
//	// 2) Copier vers le buffer GPU
//	//   ? Assure-toi que g_particleBuffer est en COPY_DEST (via barrier COMMON?COPY_DEST si nécessaire)
//	mp_cmdManager->GetCommandList()->CopyResource(
//		g_particleBuffer.Get(),
//		g_particleUploadBuffer.Get());
//
//	// 3) Créer la SRV du buffer (il faut que ça soit exécuté **avant** le draw)
//	mp_descriptorManager->CreateBufferSRV(
//		g_particleBuffer.Get(),
//		kMaxParticles,           // tu peux laisser la taille max ici
//		sizeof(Particle));
//
//	// 4) Transition ? UNORDERED_ACCESS pour le compute (même si tu ne dispatches pas)
//	D3D12_RESOURCE_BARRIER uavBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
//		g_particleBuffer.Get(),
//		D3D12_RESOURCE_STATE_COPY_DEST,
//		D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
//	mp_cmdManager->GetCommandList()->ResourceBarrier(1, &uavBarrier);
//}
//
//
//
//void ParticleManager::CreateParamBuffer()
//{
//	// CBV for ParticleParameters
//	UINT size = (sizeof(ParticleParam) + 255) & ~255u;
//
//	auto heapPropUPLOAD = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
//	auto resDesc = CD3DX12_RESOURCE_DESC::Buffer(size);
//	mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapPropUPLOAD, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&g_paramBuffer));
//}
//
//void ParticleManager::CreateComputeParamBuffer()
//{
//	// Create upload heap for compute shader parameters
//	UINT size = (sizeof(float) * 3 + 255) & ~255u; // dt, totalTime, gravity
//	auto heapPropUPLOAD = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
//	auto resDesc = CD3DX12_RESOURCE_DESC::Buffer(size);
//	mp_graphicsDevice->GetDevice()->CreateCommittedResource(
//		&heapPropUPLOAD,
//		D3D12_HEAP_FLAG_NONE,
//		&resDesc,
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&g_computeParamBuffer));
//}
//
//void ParticleManager::CreateQuadVertexBuffer()
//{
//	struct V { float pos[2], uv[2]; };
//	V verts[4] = { {-0.5f,-0.5f,0,1},{-0.5f,.5f,0,0},{.5f,-.5f,1,1},{.5f,.5f,1,0} };
//	UINT size = sizeof(verts);
//	auto& up = m_quadUploadBuffer;
//	auto heapPropUPLOAD = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
//	auto resDesc = CD3DX12_RESOURCE_DESC::Buffer(size);
//	mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapPropUPLOAD, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&up));
//
//	void* d;
//	up->Map(0, nullptr, &d);
//	memcpy(d, verts, size);
//	up->Unmap(0, nullptr);
//
//	auto heapPropDEFAULT = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
//	mp_graphicsDevice->GetDevice()->CreateCommittedResource(&heapPropDEFAULT, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&g_quadVB));
//	mp_cmdManager->GetCommandList()->CopyResource(g_quadVB.Get(), up.Get());
//
//
//	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
//		g_quadVB.Get(),
//		D3D12_RESOURCE_STATE_COPY_DEST,
//		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER
//	);
//	mp_cmdManager->GetCommandList()->ResourceBarrier(1, &barrier);
//}
//
//void ParticleManager::CreateRootSignaturesAndPSOs()
//{
//	// Compute RS+PSO
//	CD3DX12_ROOT_PARAMETER csP[2];
//	csP[0].InitAsUnorderedAccessView(0);
//	csP[1].InitAsConstantBufferView(0);
//	CD3DX12_ROOT_SIGNATURE_DESC csD(2, csP);
//	ComPtr<ID3DBlob> sig, err;
//	D3D12SerializeRootSignature(&csD, D3D_ROOT_SIGNATURE_VERSION_1, &sig, &err);
//	mp_graphicsDevice->GetDevice()->CreateRootSignature(0, sig->GetBufferPointer(), sig->GetBufferSize(), IID_PPV_ARGS(&g_computeRootSig));
//	auto csBlob = CompileShader(L"../LyonPlexLib/Ressources/ParticlesShader.hlsl", "CSMain", "cs_5_0");
//	D3D12_COMPUTE_PIPELINE_STATE_DESC csPSO = {}; csPSO.pRootSignature = g_computeRootSig.Get(); csPSO.CS = { csBlob->GetBufferPointer(),csBlob->GetBufferSize() };
//	mp_graphicsDevice->GetDevice()->CreateComputePipelineState(&csPSO, IID_PPV_ARGS(&g_computePSO));
//
//	// Graphics RS
//
//	// range 0 : smokeTex t0
//	// range 1 : particles SRV t1
//	CD3DX12_DESCRIPTOR_RANGE ranges[2];
//	ranges[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // smokeTex
//	ranges[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 1); // particles
//
//	CD3DX12_ROOT_PARAMETER gP[3];
//	gP[0].InitAsDescriptorTable(2, ranges);   // t0 smokeTex + t1 particles
//	gP[1].InitAsConstantBufferView(1);   // b1 viewProj
//	gP[2].InitAsConstantBufferView(2);   // b2 ParticleParameters
//
//	// 2 rootParams dédiés, un pour la smoke, un pour les particules
//	//CD3DX12_DESCRIPTOR_RANGE texRange;
//	//texRange.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // smokeTex:t0
//
//	//CD3DX12_DESCRIPTOR_RANGE partRange;
//	//partRange.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 1); // particles:t1
//
//	//CD3DX12_ROOT_PARAMETER gP[4];
//	//gP[0].InitAsDescriptorTable(1, &texRange);   // slot t0
//	//gP[1].InitAsDescriptorTable(1, &partRange);  // slot t1
//	//gP[2].InitAsConstantBufferView(1);           // b1 viewProj
//	//gP[3].InitAsConstantBufferView(2);           // b2 ParticleParams
//
//
//	D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
//	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
//	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
//	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
//	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
//	samplerDesc.ShaderRegister = 0;
//	samplerDesc.RegisterSpace = 0;
//	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
//
//	D3D12_ROOT_SIGNATURE_DESC rootSigDesc = {};
//	rootSigDesc.NumParameters = _countof(gP);
//	rootSigDesc.pParameters = gP;
//	rootSigDesc.NumStaticSamplers = 1;
//	rootSigDesc.pStaticSamplers = &samplerDesc;
//	rootSigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
//
//	D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &sig, &err);
//	mp_graphicsDevice->GetDevice()->CreateRootSignature(0, sig->GetBufferPointer(), sig->GetBufferSize(), IID_PPV_ARGS(&g_graphicsRootSig));
//
//	// Compile VS/PS
//	auto vs = CompileShader(L"../LyonPlexLib/Ressources/ParticlesShader.hlsl", "VSMain", "vs_5_0");
//	auto ps = CompileShader(L"../LyonPlexLib/Ressources/ParticlesShader.hlsl", "PSMain", "ps_5_0");
//	D3D12_INPUT_ELEMENT_DESC layout[] = {
//		{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
//		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,8,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0}
//	};
//	auto ds = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
//	ds.DepthEnable = FALSE;
//	ds.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
//	ds.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;
//
//	auto createPSO = [&](D3D12_BLEND_DESC bDesc, ComPtr<ID3D12PipelineState>& outPSO) {
//		D3D12_GRAPHICS_PIPELINE_STATE_DESC d = {};
//		d.InputLayout = { layout,_countof(layout) };
//		d.pRootSignature = g_graphicsRootSig.Get();
//		d.VS = { vs->GetBufferPointer(),vs->GetBufferSize() };
//		d.PS = { ps->GetBufferPointer(),ps->GetBufferSize() };
//		d.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
//		d.BlendState = bDesc;
//		//d.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
//		d.DepthStencilState = ds;
//		d.SampleMask = UINT_MAX;
//		d.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
//		d.NumRenderTargets = 1;
//		d.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
//		d.SampleDesc.Count = 1;
//		d.DSVFormat = DXGI_FORMAT_D32_FLOAT;
//		mp_graphicsDevice->GetDevice()->CreateGraphicsPipelineState(&d, IID_PPV_ARGS(&outPSO));
//		};
//	// Alpha blend
//	D3D12_BLEND_DESC alpha = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
//	alpha.RenderTarget[0].BlendEnable = TRUE;
//	alpha.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
//	alpha.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
//	createPSO(alpha, g_graphicsPSO_Alpha);
//	// Additive
//	D3D12_BLEND_DESC add = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
//	add.RenderTarget[0].BlendEnable = TRUE;
//	add.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
//	add.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;
//	createPSO(add, g_graphicsPSO_Additive);
//}
//
//void ParticleManager::Init(GraphicsDevice* graphicsDevice, CommandManager* cmdManager, DescriptorManager* descriptorManager)
//{
//	mp_graphicsDevice = graphicsDevice;
//	mp_cmdManager = cmdManager;
//	mp_descriptorManager = descriptorManager;
//}
//
//void ParticleManager::CreateParticles(TextureManager* textureManager)
//{
//	mp_cmdManager->Begin();
//
//	CreateParticleBuffers();
//
//	TextureID smokeID = textureManager->LoadTexture("../LyonPlexLib/Ressources/bois2.jpg");
//
//	// 4) recalcule l’index exact de ta smoke dans le heap
//	m_smokeSrvIndex = textureManager->GetSrvGpuHandle(smokeID).ptr;
//
//	UINT a = mp_descriptorManager->GetSrvNextOffset();
//	//idTemp = textureManager->LoadTexture("../LyonPlexLib/Ressources/bois2.jpg"); // TEST POUR SMOKE
//
//	UINT b = mp_descriptorManager->GetSrvNextOffset();
//	MapUploadBuffer(textureManager);
//
//	char buf[128];
//	sprintf_s(buf, "\nSmoke index = %u / Last index = %u / Particle index = %u / Last index = %u\n",
//		TEXTURES::SMOKE_TEX, a,
//		mp_descriptorManager->GetSrvNextOffset(), b);
//	OutputDebugStringA(buf);
//
//
//	CreateParamBuffer();
//	CreateComputeParamBuffer();
//	CreateQuadVertexBuffer();
//
//	mp_cmdManager->End();
//	mp_cmdManager->ExecuteCmdLists();
//	mp_cmdManager->SignalAndWait();
//
//	CreateRootSignaturesAndPSOs();
//}
//
//void ParticleManager::UpdateParticles(float dt, float t, float gravity)
//{
//	if (!g_computeParamBuffer) {
//		OutputDebugStringA("\nErreur : computeParamBuffer non initialisé !\n");
//		return;
//	}
//	auto& cmdList = mp_cmdManager->GetCommandList();
//	// Bind compute PSO and root signature
//	cmdList->SetPipelineState(g_computePSO.Get());
//	cmdList->SetComputeRootSignature(g_computeRootSig.Get());
//
//	// UAV for particles
//	cmdList->SetComputeRootUnorderedAccessView(0, g_particleBuffer->GetGPUVirtualAddress());
//
//	// Update compute parameter buffer
//	struct CSParams { float dt; float totalTime; float gravity; } cs{ dt, t, gravity };
//	void* mapped;
//	g_computeParamBuffer->Map(0, nullptr, &mapped);
//	memcpy(mapped, &cs, sizeof(cs));
//	g_computeParamBuffer->Unmap(0, nullptr);
//
//	// Bind CBV to slot 1 (b0 in HLSL)
//	cmdList->SetComputeRootConstantBufferView(1, g_computeParamBuffer->GetGPUVirtualAddress());
//
//	// Dispatch compute shader
//	cmdList->Dispatch((kMaxParticles + kCSGroupSize - 1) / kCSGroupSize, 1, 1);
//
//	// 1) Fence mémoire pour toutes les écritures UAV
//	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::UAV(g_particleBuffer.Get());
//	cmdList->ResourceBarrier(1, &barrier);
//
//	// 2) Transition vers lecture par le pixel/vertex shader
//	barrier = CD3DX12_RESOURCE_BARRIER::Transition(
//		g_particleBuffer.Get(),
//		D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
//		/*D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE*/
//		D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
//	cmdList->ResourceBarrier(1, &barrier);
//}
//
//void ParticleManager::RenderParticles(const D3D12_VIEWPORT& vp, const D3D12_RECT& sc, const D3D12_GPU_VIRTUAL_ADDRESS viewProjCBAdress, const D3D12_GPU_DESCRIPTOR_HANDLE srvHandle, const ParticleParam& params)
////{
////	// update param CB
////	ParticleParam* mp; g_paramBuffer->Map(0, nullptr, (void**)&mp); *mp = p; g_paramBuffer->Unmap(0, nullptr);
////	mp_cmdManager->GetCommandList()->RSSetViewports(1, &vp); mp_cmdManager->GetCommandList()->RSSetScissorRects(1, &sc);
////	// choose PSO by blendMode
////	bool isAdd = (p.blendMode == BlendMode::Additive);
////	mp_cmdManager->GetCommandList()->SetPipelineState(isAdd ? g_graphicsPSO_Additive.Get() : g_graphicsPSO_Alpha.Get());
////
////	ID3D12DescriptorHeap* heaps[] = { mp_descriptorManager->GetSrvHeap() };
////	mp_cmdManager->GetCommandList()->SetDescriptorHeaps(_countof(heaps), heaps);
////
////	mp_cmdManager->GetCommandList()->SetGraphicsRootSignature(g_graphicsRootSig.Get());
////
////	mp_cmdManager->GetCommandList()->SetGraphicsRootDescriptorTable(0, srvHandle);
////
////	mp_cmdManager->GetCommandList()->SetGraphicsRootConstantBufferView(1, viewProjCBAdress);
////	// params CBV
////	mp_cmdManager->GetCommandList()->SetGraphicsRootConstantBufferView(2, g_paramBuffer->GetGPUVirtualAddress());
////	D3D12_VERTEX_BUFFER_VIEW vbv{ g_quadVB->GetGPUVirtualAddress(),sizeof(float) * 4 * 4,sizeof(float) * 4 };
////	mp_cmdManager->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
////	mp_cmdManager->GetCommandList()->IASetVertexBuffers(0, 1, &vbv);
////	mp_cmdManager->GetCommandList()->DrawInstanced(4, kMaxParticles, 0, 0);
////}
//{
//	auto cmd = mp_cmdManager->GetCommandList();
//
//	// 1) Rebind du heap SRV (pour être sûr après tout changement de rootSig/PSO)
//	ID3D12DescriptorHeap* heaps[] = { mp_descriptorManager->GetSrvHeap() };
//	cmd->SetDescriptorHeaps(_countof(heaps), heaps);
//
//	// 2) Mettre à jour le CB des paramètres particules
//	{
//		ParticleParam* pData = nullptr;
//		g_paramBuffer->Map(0, nullptr, (void**)&pData);
//		*pData = params;
//		g_paramBuffer->Unmap(0, nullptr);
//	}
//
//	// 3) Pipeline & root signature
//	cmd->SetGraphicsRootSignature(g_graphicsRootSig.Get());
//	bool isAdd = (params.blendMode == BlendMode::Additive);
//	cmd->SetPipelineState(isAdd ? g_graphicsPSO_Additive.Get()
//		: g_graphicsPSO_Alpha.Get());
//
//	UINT descSize = mp_descriptorManager->GetSrvDescriptorSize();
//	// 4) Table de 2 SRV : smokeTex à t0 et particlesRender à t1
//	//    srvHeapStart devrait être le handle du début du heap.
//	D3D12_GPU_DESCRIPTOR_HANDLE smokeHandle = { srvHandle.ptr + m_smokeSrvIndex * descSize };
//	D3D12_GPU_DESCRIPTOR_HANDLE particleHandle = { srvHandle.ptr + (m_smokeSrvIndex + 1) * descSize };
//	//cmd->SetGraphicsRootDescriptorTable(0, srvHandle);
//	//cmd->SetGraphicsRootDescriptorTable(0, smokeHandle);
//	cmd->SetGraphicsRootDescriptorTable(0, mp_textureManager->GetSrvGpuHandle(m_smokeSrvIndex));
//	//cmd->SetGraphicsRootDescriptorTable(1, particleHandle);
//
//	//D3D12_GPU_DESCRIPTOR_HANDLE table[2] = { smokeHandle, particleHandle };
//	//cmd->SetGraphicsRootDescriptorTable(0, table[0]);
//
//	// 5) CBVs : viewProj (b1) et params (b2)
//	cmd->SetGraphicsRootConstantBufferView(1, viewProjCBAdress);
//	//cmd->SetGraphicsRootConstantBufferView(2, viewProjCBAdress);
//	cmd->SetGraphicsRootConstantBufferView(2, g_paramBuffer->GetGPUVirtualAddress());
//	//cmd->SetGraphicsRootConstantBufferView(3, g_paramBuffer->GetGPUVirtualAddress());
//
//	// 6) IA + Draw
//	cmd->RSSetViewports(1, &vp);
//	cmd->RSSetScissorRects(1, &sc);
//
//	D3D12_VERTEX_BUFFER_VIEW vbv{
//		/*BufferLocation=*/ g_quadVB->GetGPUVirtualAddress(),
//		/*SizeInBytes=*/    sizeof(float) * 4 * 4,
//		/*StrideInBytes=*/  sizeof(float) * 4
//	};
//	cmd->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//	cmd->IASetVertexBuffers(0, 1, &vbv);
//	//cmd->DrawInstanced(4, kMaxParticles, 0, 0);
//	cmd->DrawInstanced(4, 1, 0, 0);
//}

/* ParticleManager.cpp */
#include "ParticleManager.h"
#include <pch.h>

// helper to compile
static ComPtr<ID3DBlob> CompileShader(const std::wstring& file, const std::string& entry, const std::string& target) {
	ComPtr<ID3DBlob> code, err;
	D3DCompileFromFile(file.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entry.c_str(), target.c_str(), 0, 0, &code, &err);
	return code;
}

void ParticleManager::Initialize(GraphicsDevice* graphicsDevice, CommandManager* cmdManager, DescriptorManager* descriptorManager/*ID3D12DescriptorHeap* srvHeap*/) {
	m_srvHeap = descriptorManager->GetSrvHeap();
	m_srvDescriptorSize = descriptorManager->GetSrvDescriptorSize();

	m_descMgr = descriptorManager;
	m_cmdMgr = cmdManager;
	m_graphicsDevice = graphicsDevice;
	auto device = graphicsDevice->GetDevice().Get();
	auto cmd = cmdManager->GetCommandList();

	// Begin recording
	cmdManager->Begin();

	// 1) Create GPU & upload buffers
	const UINT es = sizeof(Particle);
	D3D12_RESOURCE_DESC bufDesc = CD3DX12_RESOURCE_DESC::Buffer(es * kNumParticles);

	auto a = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	auto b = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto c = CD3DX12_RESOURCE_BARRIER::UAV(m_particleBuffer.Get());

	device->CreateCommittedResource(
		&b,
		D3D12_HEAP_FLAG_NONE,
		&bufDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_particleUpload));

	device->CreateCommittedResource(
		&a,
		D3D12_HEAP_FLAG_NONE,
		&bufDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&m_particleBuffer));

	// 2) Initialize upload buffer
	Particle* mapped = nullptr;
	m_particleUpload->Map(0, nullptr, reinterpret_cast<void**>(&mapped));
	mapped[0] = { {0.0f, 0.0f, 5.0f}, 1.0f, {1,1,1,1} };
	m_particleUpload->Unmap(0, nullptr);

	// 3) Copy and transition to SRV
	cmd->CopyResource(m_particleBuffer.Get(), m_particleUpload.Get());
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
			m_particleBuffer.Get(),
			D3D12_RESOURCE_STATE_COPY_DEST,
			D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
	cmd->ResourceBarrier(1, &barrier);

	// 4) Create SRV via DescriptorManager
	m_descMgr->CreateBufferSRV(
		m_particleBuffer.Get(),
		kNumParticles,
		es);

	// 5) Create quad VB
	float quadVerts[] = { -0.5f,-0.5f,  0.5f,-0.5f,  -0.5f,0.5f,  0.5f,0.5f };
	D3D12_RESOURCE_DESC vbDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(quadVerts));
	ComPtr<ID3D12Resource> quadUpload;
	device->CreateCommittedResource(
		&b,
		D3D12_HEAP_FLAG_NONE,
		&vbDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&quadUpload));
	void* vbData = nullptr;
	quadUpload->Map(0, nullptr, &vbData);
	memcpy(vbData, quadVerts, sizeof(quadVerts));
	quadUpload->Unmap(0, nullptr);

	device->CreateCommittedResource(
		&a,
		D3D12_HEAP_FLAG_NONE,
		&vbDesc,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
		nullptr,
		IID_PPV_ARGS(&m_quadVB));
	cmd->CopyResource(m_quadVB.Get(), quadUpload.Get());

	// 6) Root signature (SRV t0 + CBV b0)
	CD3DX12_DESCRIPTOR_RANGE range;
	range.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);
	CD3DX12_ROOT_PARAMETER rp[2];
	rp[0].InitAsDescriptorTable(1, &range);
	rp[1].InitAsConstantBufferView(0);
	CD3DX12_ROOT_SIGNATURE_DESC rsd(
		_countof(rp), rp,
		0, nullptr,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	ComPtr<ID3DBlob> sigBlob;
	D3D12SerializeRootSignature(
		&rsd, D3D_ROOT_SIGNATURE_VERSION_1,
		&sigBlob, nullptr);
	device->CreateRootSignature(
		0,
		sigBlob->GetBufferPointer(),
		sigBlob->GetBufferSize(),
		IID_PPV_ARGS(&m_rootSig));

	// 7) Create minimal PSO
	auto vs = CompileShader(L"../LyonPlexLib/Ressources/ParticlesShader.hlsl", "VSMain", "vs_5_0");
	auto ps = CompileShader(L"../LyonPlexLib/Ressources/ParticlesShader.hlsl", "PSMain", "ps_5_0");
	D3D12_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0,
		 D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0}
	};
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
	psoDesc.pRootSignature = m_rootSig.Get();
	psoDesc.VS = { vs->GetBufferPointer(), vs->GetBufferSize() };
	psoDesc.PS = { ps->GetBufferPointer(), ps->GetBufferSize() };
	psoDesc.InputLayout = { layout, _countof(layout) };
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	auto ds = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	ds.DepthEnable = FALSE;
	ds.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	psoDesc.DepthStencilState = ds;
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc.Count = 1;
	device->CreateGraphicsPipelineState(
		&psoDesc,
		IID_PPV_ARGS(&m_pso));

	// End recording
	cmdManager->End();
	cmdManager->ExecuteCmdLists();
	cmdManager->SignalAndWait();



	//cmdManager->Begin();
	//
	//
	//// 1) Création des buffers GPU/upload pour 1 particule
	//const UINT es = sizeof(Particle);
	//auto bufDesc = CD3DX12_RESOURCE_DESC::Buffer(es * kNumParticles);
	//auto a = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	//device->CreateCommittedResource(
	//	&a,
	//	D3D12_HEAP_FLAG_NONE, &bufDesc,
	//	D3D12_RESOURCE_STATE_COMMON,
	//	nullptr, IID_PPV_ARGS(&m_particleBuffer));

	//auto b = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	//device->CreateCommittedResource(
	//	&b,
	//	D3D12_HEAP_FLAG_NONE, &bufDesc,
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr, IID_PPV_ARGS(&m_particleUpload));

	//// 2) Initialisation de l'upload-buffer
	//Particle* pData = nullptr;
	//m_particleUpload->Map(0, nullptr, reinterpret_cast<void**>(&pData));
	//pData[0] = { {0,2,5}, 1.0f, {1,1,1,1} };
	//m_particleUpload->Unmap(0, nullptr);

	//// 3) Copy + barrières pour lecture VS
	//cmd->CopyResource(m_particleBuffer.Get(), m_particleUpload.Get());

	//auto c = CD3DX12_RESOURCE_BARRIER::UAV(m_particleBuffer.Get());
	//cmd->ResourceBarrier(1, &c);
	//D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
	//	m_particleBuffer.Get(),
	//	D3D12_RESOURCE_STATE_COPY_DEST,
	//	D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
	//cmd->ResourceBarrier(1, &barrier);
	//// 4) Création du SRV via ton descriptorManager
	//m_descMgr->CreateBufferSRV(
	//	m_particleBuffer.Get(),
	//	kNumParticles,
	//	es);

	//// 5) Création du VB quad
	//float quad[] = { -0.5f,-0.5f,  0.5f,-0.5f,  -0.5f,0.5f,  0.5f,0.5f };
	//auto vbDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(quad));
	//ComPtr<ID3D12Resource> quadUpload;
	//device->CreateCommittedResource(
	//	&b,
	//	D3D12_HEAP_FLAG_NONE, &vbDesc,
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr, IID_PPV_ARGS(&quadUpload));
	//void* vbPtr = nullptr;
	//quadUpload->Map(0, nullptr, &vbPtr);
	//memcpy(vbPtr, quad, sizeof(quad));
	//quadUpload->Unmap(0, nullptr);

	//device->CreateCommittedResource(
	//	&a,
	//	D3D12_HEAP_FLAG_NONE, &vbDesc,
	//	D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
	//	nullptr, IID_PPV_ARGS(&m_quadVB));
	//cmd->CopyResource(m_quadVB.Get(), quadUpload.Get());

	//// 6) Root signature (SRV t0 + CBV b0 pour viewProj)
	//CD3DX12_DESCRIPTOR_RANGE range;
	//range.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);
	//CD3DX12_ROOT_PARAMETER params[2];
	//params[0].InitAsDescriptorTable(1, &range);
	//params[1].InitAsConstantBufferView(0);
	//CD3DX12_ROOT_SIGNATURE_DESC rsd(
	//	_countof(params), params,
	//	0, nullptr,
	//	D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	//ComPtr<ID3DBlob> sig;
	//D3D12SerializeRootSignature(
	//	&rsd, D3D_ROOT_SIGNATURE_VERSION_1, &sig, nullptr);
	//device->CreateRootSignature(
	//	0, sig->GetBufferPointer(), sig->GetBufferSize(),
	//	IID_PPV_ARGS(&m_rootSig));

	//// 7) Création du PSO minimal
	//auto vs = Compile(L"../LyonPlexLib/Ressources/ParticlesShader.hlsl", "VSMain", "vs_5_0");
	//auto ps = Compile(L"../LyonPlexLib/Ressources/ParticlesShader.hlsl", "PSMain", "ps_5_0");
	//D3D12_INPUT_ELEMENT_DESC layout[] = {
	//	{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0,
	//	 D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0}
	//};
	//D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
	//psoDesc.pRootSignature = m_rootSig.Get();
	//psoDesc.VS = { vs->GetBufferPointer(), vs->GetBufferSize() };
	//psoDesc.PS = { ps->GetBufferPointer(), ps->GetBufferSize() };
	//psoDesc.InputLayout = { layout, _countof(layout) };
	//psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	//psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	//auto ds = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	//ds.DepthEnable = FALSE;
	//ds.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	//psoDesc.DepthStencilState = ds;
	//psoDesc.SampleMask = UINT_MAX;
	//psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	//psoDesc.NumRenderTargets = 1;
	//psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	//psoDesc.SampleDesc.Count = 1;
	//device->CreateGraphicsPipelineState(
	//	&psoDesc, IID_PPV_ARGS(&m_pso));


	//cmdManager->End();
	//cmdManager->ExecuteCmdLists();
	//cmdManager->SignalAndWait();

	
}

void ParticleManager::Render(ID3D12GraphicsCommandList* cmdList,
	D3D12_GPU_DESCRIPTOR_HANDLE bufferHandle,
	const D3D12_VIEWPORT& vp,
	const D3D12_RECT& scissor,
	D3D12_GPU_VIRTUAL_ADDRESS viewProjCB)
{
	// Bind heap
	ID3D12DescriptorHeap* heaps[] = { m_srvHeap };
	cmdList->SetDescriptorHeaps(_countof(heaps), heaps);
	cmdList->SetGraphicsRootSignature(m_rootSig.Get());
	cmdList->SetPipelineState(m_pso.Get());

	cmdList->SetGraphicsRootDescriptorTable(0, bufferHandle);
	cmdList->SetGraphicsRootConstantBufferView(1, viewProjCB);


	D3D12_VERTEX_BUFFER_VIEW vbv{ m_quadVB->GetGPUVirtualAddress(), sizeof(float) * 8, sizeof(float) * 2 };
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	cmdList->IASetVertexBuffers(0, 1, &vbv);
	cmdList->DrawInstanced(4, kNumParticles, 0, 0);

}