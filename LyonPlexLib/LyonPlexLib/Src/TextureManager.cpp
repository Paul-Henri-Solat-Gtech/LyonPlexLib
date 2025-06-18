#include "pch.h"
#include "TextureManager.h"
#include <comdef.h>
#include "../../ExternalLib/DirectXTK12-main/Src/PlatformHelpers.h"

//#include <wrl.h>
#include <wincodec.h>
using Microsoft::WRL::ComPtr;

using TextureID = ResourceManager<TextureData, std::string>::ResourceID;

// Helper GUID pour WIC
static ComPtr<IWICImagingFactory> _wicFactory;

static void EnsureWICFactory()
{
	if (!_wicFactory)
	{
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		CoCreateInstance(
			CLSID_WICImagingFactory2,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&_wicFactory)
		);
	}
}

void TextureManager::Init(GraphicsDevice* graphicsDevice, DescriptorManager* descriptorManager, CommandManager* commandManager)
{
	mp_graphicsDevice = graphicsDevice;
	mp_descMgr = descriptorManager;
	mp_commandManager = commandManager;

	LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	LoadTexture("../LyonPlexLib/Ressources/Test.png");
	LoadTexture("../LyonPlexLib/Ressources/TestBRAS.png");
	LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
}

TextureID TextureManager::LoadTexture(const std::string& key)
{
	// Normalize extension
	auto ext = std::filesystem::path(key).extension().string();
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

	// Get or add resource entry
	TextureID id = m_textures.Load(key);
	TextureData& tex = m_textures.Get(id);

	//// Already loaded?
	//if (tex.resource)
	//	return id;


	// Convert to wide string
	std::wstring wpath(key.begin(), key.end());

	// 1) Charge image via WIC
	EnsureWICFactory();
	ComPtr<IWICBitmapDecoder> decoder;

	ThrowIfFailed(_wicFactory->CreateDecoderFromFilename(
		wpath.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&decoder));

	ComPtr<IWICBitmapFrameDecode> frame;
	ThrowIfFailed(decoder->GetFrame(0, &frame));

	// Convert to 32bpp RGBA
	ComPtr<IWICFormatConverter> converter;
	ThrowIfFailed(_wicFactory->CreateFormatConverter(&converter));
	ThrowIfFailed(converter->Initialize(
		frame.Get(),
		GUID_WICPixelFormat32bppRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.f,
		WICBitmapPaletteTypeCustom
	));

	UINT width, height;
	ThrowIfFailed(converter->GetSize(&width, &height));

	std::vector<BYTE> imageData(width * height * 4);
	ThrowIfFailed(converter->CopyPixels(
		nullptr,
		width * 4,
		static_cast<UINT>(imageData.size()),
		imageData.data()
	));

	// 2) Cree la resource GPU en SRGB
	D3D12_RESOURCE_DESC desc = {};
	desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	desc.Alignment = 0;
	desc.Width = width;
	desc.Height = height;
	desc.DepthOrArraySize = 1;
	desc.MipLevels = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // SRGB
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	desc.Flags = D3D12_RESOURCE_FLAG_NONE;

	ComPtr<ID3D12Resource> texResource;
	CD3DX12_HEAP_PROPERTIES defaultHeapProps(D3D12_HEAP_TYPE_DEFAULT);
	ThrowIfFailed(mp_graphicsDevice->GetDevice()->CreateCommittedResource(
		&defaultHeapProps,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&texResource)));

	tex.resource = texResource; // stocke dans ton cache

	// 3) Prepare l’upload heap
	UINT64 uploadSize = GetRequiredIntermediateSize(texResource.Get(), 0, 1);
	ComPtr<ID3D12Resource> uploadHeap;

	CD3DX12_HEAP_PROPERTIES uploadHeapProps(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC   uploadDesc = CD3DX12_RESOURCE_DESC::Buffer(uploadSize);

	ThrowIfFailed(mp_graphicsDevice->GetDevice()->CreateCommittedResource(
		&uploadHeapProps,
		D3D12_HEAP_FLAG_NONE,
		&uploadDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&uploadHeap)));

	// 4) Cree un command list temporaire
	ComPtr<ID3D12CommandAllocator> alloc;
	ComPtr<ID3D12GraphicsCommandList> cmd;
	ThrowIfFailed(mp_graphicsDevice->GetDevice()->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&alloc)));
	ThrowIfFailed(mp_graphicsDevice->GetDevice()->CreateCommandList(
		0, D3D12_COMMAND_LIST_TYPE_DIRECT, alloc.Get(), nullptr, IID_PPV_ARGS(&cmd)));

	// 5) Prepare la structure subresource
	D3D12_SUBRESOURCE_DATA sub = {};
	sub.pData = imageData.data();
	sub.RowPitch = width * 4;
	sub.SlicePitch = width * height * 4;

	// 6) Copie CPU ->GPU
	UpdateSubresources(cmd.Get(),
		texResource.Get(),
		uploadHeap.Get(),
		0, 0, 1, &sub);

	// 7) Transition vers PIXEL_SHADER_RESOURCE
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		texResource.Get(),
		D3D12_RESOURCE_STATE_COPY_DEST,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE
	);
	cmd->ResourceBarrier(1, &barrier);

	// 8) Close + execute + wait
	ThrowIfFailed(cmd->Close());
	ID3D12CommandList* lists[] = { cmd.Get() };
	mp_graphicsDevice->GetCommandQueue()->ExecuteCommandLists(1, lists);
	mp_commandManager->SignalAndWait();

	mp_commandManager->GetCommandAllocator()->Reset();
	mp_commandManager->GetCommandList()->Reset(
		mp_commandManager->GetCommandAllocator().Get(),
		nullptr
	);

	// 9) Cree le SRV
	D3D12_CPU_DESCRIPTOR_HANDLE srvH = mp_descMgr->AllocateSrvCPU();
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.ViewDimension			= D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels		= 1;
	mp_graphicsDevice->GetDevice()
		->CreateShaderResourceView(texResource.Get(), &srvDesc, srvH);

	tex.descriptorIndex = mp_descMgr->GetSrvNextOffset() - 1;
	return id;


	//// Prepare DX12 upload batch
	//ResourceUploadBatch uploadBatch(mp_graphicsDevice->GetDevice().Get());
	//uploadBatch.Begin(D3D12_COMMAND_LIST_TYPE_COPY);

	//// DX12: use DirectXTK12 CreateWIC/DDS overloads
	//HRESULT hr = S_OK;
	//if (ext == ".dds") {
	//    hr = CreateDDSTextureFromFile(
	//        mp_graphicsDevice->GetDevice().Get(),
	//        uploadBatch,
	//        wpath.c_str(),
	//        &tex.resource,
	//        true // generate mips if available
	//    );
	//}
	//else {
	//    hr = CreateWICTextureFromFile(
	//        mp_graphicsDevice->GetDevice().Get(),
	//        uploadBatch,
	//        wpath.c_str(),
	//        &tex.resource,
	//        true // generate mips
	//    );
	//    //D3D12_CPU_DESCRIPTOR_HANDLE srvCpu = m_descMgr->AllocateSrvCPU();
	//    //HRESULT hr = CreateWICTextureFromFile(
	//    //    m_graphicsDevice->GetDevice().Get(), uploadBatch,
	//    //    wpath.c_str(),
	//    //    &tex.resource,
	//    //    srvCpu,                 // <— handle SRV
	//    //    WIC_LOADER_DEFAULT,     // ou WIC_LOADER_FORCE_SRGB
	//    //    true /* generate mips */);
	//    //ThrowIfFailed(hr);
	//}
	//_com_error err(hr);
	//std::wstring msg = err.ErrorMessage();
	//OutputDebugStringW((L"Erreur DirectXTK: " + msg + L"\n").c_str());
	//if (FAILED(hr)) {
	//    //m_textures.Remove(id);
	//    throw std::runtime_error("Failed to load texture: " + key);
	//}

	////// Create SRV descriptor in CPU heap
	////D3D12_CPU_DESCRIPTOR_HANDLE srvCpu = m_descMgr->AllocateSrvCPU();
	////m_graphicsDevice->GetDevice()->CreateShaderResourceView(
	////    tex.resource.Get(),
	////    nullptr,
	////    srvCpu
	////);

	//

	//// Execute the upload commands on the GPU queue
	//auto uploadOp = uploadBatch.End(mp_graphicsDevice->GetCommandQueue().Get());
	//uploadOp.wait();

	////// Create SRV descriptor in CPU heap
	////D3D12_CPU_DESCRIPTOR_HANDLE srvCpu = m_descMgr->AllocateSrvCPU();
	////D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	////srvDesc.Shader4ComponentMapping         = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	////srvDesc.Format                          = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // Force le format pour de gammaiser (gamam rend la couleur plus sombre)
	////srvDesc.ViewDimension                   = D3D12_SRV_DIMENSION_TEXTURE2D;
	////srvDesc.Texture2D.MipLevels             = 1;
	////m_graphicsDevice->GetDevice()->CreateShaderResourceView(tex.resource.Get(), &srvDesc, srvCpu);

	//// 4) Crée le SRV dans le heap CPU
	//D3D12_CPU_DESCRIPTOR_HANDLE srvCpu = m_descMgr->AllocateSrvCPU();
	//D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	//srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	//srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	//srvDesc.Texture2D.MipLevels = tex.resource->GetDesc().MipLevels;
	//mp_graphicsDevice->GetDevice()->CreateShaderResourceView(tex.resource.Get(), &srvDesc, srvCpu);

	//tex.descriptorIndex = m_descMgr->GetSrvNextOffset() - 1;
	//return id;



	//// 2) Préparer l’UploadBatch avec ton device
	//ResourceUploadBatch uploadBatch(mp_graphicsDevice->GetDevice().Get());

	//// 3) Démarrer l’upload en spécifiant le type de liste (Copy suffit)
	//uploadBatch.Begin(D3D12_COMMAND_LIST_TYPE_DIRECT);

	//// 4) Charger la texture dans la resource via DirectXTK
	//HRESULT hr = S_OK;
	//if (ext == ".dds")
	//{
	//    hr = CreateDDSTextureFromFile(
	//        mp_graphicsDevice->GetDevice().Get(),
	//        uploadBatch,
	//        wpath.c_str(),
	//        &tex.resource,
	//        true);
	//}
	//else
	//{
	//    hr = CreateWICTextureFromFile(
	//        mp_graphicsDevice->GetDevice().Get(),
	//        uploadBatch,
	//        wpath.c_str(),
	//        &tex.resource,
	//        true);
	//}
	////ThrowIfFailed(hr);

	//// 5) Terminer l’upload en l’enregistrant sur ta CommandQueue
	//auto uploadOp = uploadBatch.End(mp_graphicsDevice->GetCommandQueue().Get());
	//uploadOp.wait();  // now the texture is fully on GPU

	//// 6) Créer le SRV **après** l’upload
	//D3D12_CPU_DESCRIPTOR_HANDLE srvCpu = m_descMgr->AllocateSrvCPU();
	//D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	//srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	//srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	//srvDesc.Texture2D.MipLevels = tex.resource->GetDesc().MipLevels;
	//mp_graphicsDevice->GetDevice()
	//    ->CreateShaderResourceView(tex.resource.Get(), &srvDesc, srvCpu);

	//tex.descriptorIndex = m_descMgr->GetSrvNextOffset() - 1;
	//return id;

//
//// 1) Instancie le batch avec ton Device
//	ResourceUploadBatch uploadBatch(mp_graphicsDevice->GetDevice().Get());
//
//	// 2) Démarre l’upload sur la même queue que tu utilises pour exécuter tes listes,
//	//    c’est-à-dire une queue de type DIRECT pour ton moteur.
//	//uploadBatch.Begin(D3D12_COMMAND_LIST_TYPE_DIRECT);
//	uploadBatch.Begin();
//
//	// 3) Charge la texture
//	HRESULT hr;
//	if (ext == ".dds")
//	{
//		hr = CreateDDSTextureFromFile(
//			mp_graphicsDevice->GetDevice().Get(),
//			uploadBatch,
//			wpath.c_str(),
//			&tex.resource,
//			true);
//	}
//	else
//	{
//		/*hr = CreateWICTextureFromFile(
//			mp_graphicsDevice->GetDevice().Get(),
//			uploadBatch,
//			wpath.c_str(),
//			&tex.resource,
//			true);*/
//		HRESULT hr = CreateWICTextureFromFileEx(
//			mp_graphicsDevice->GetDevice().Get(),
//			uploadBatch,
//			wpath.c_str(),
//			0, // maxsize: 0 = default
//			D3D12_RESOURCE_FLAG_NONE,
//			WIC_LOADER_FORCE_SRGB | WIC_LOADER_MIP_AUTOGEN, // Important
//			&tex.resource
//		);
//	}
//	//ThrowIfFailed(hr);
//
//	// 4) Termine l’upload sur TA queue DIRECT,
//	//    exactement la même que dans Begin() et celle que tu utilises pour Record/Execute.
//	auto uploadOp = uploadBatch.End(mp_graphicsDevice->GetCommandQueue().Get());
//	uploadOp.wait();  // attend que la copie GPU soit terminée
	//HRESULT hr = CreateWICTextureFromFile(
	//	mp_graphicsDevice->GetDevice().Get(),
	//	uploadBatch,
	//	wpath.c_str(),
	//	&tex.resource,   // <-- c’est ici que la ressource est instanciée
	//	true /* generate mips */
	//);
	//ThrowIfFailed(hr);
	//// 1) Créer un upload heap manuellement
	//UINT64 uploadSize = GetRequiredIntermediateSize(tex.resource.Get(), 0, 1);
	//CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
	//CD3DX12_RESOURCE_DESC   bufDesc = CD3DX12_RESOURCE_DESC::Buffer(uploadSize);
	//ComPtr<ID3D12Resource> uploadHeap;
	//ThrowIfFailed(mp_graphicsDevice->GetDevice()->CreateCommittedResource(
	//	&heapProps, D3D12_HEAP_FLAG_NONE, &bufDesc,
	//	D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
	//	IID_PPV_ARGS(&uploadHeap)
	//));

	//// 2) Obtenir une command list temporaire
	//ComPtr<ID3D12CommandAllocator> alloc;
	//ComPtr<ID3D12GraphicsCommandList> list;
	//ThrowIfFailed(mp_graphicsDevice->GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&alloc)));
	//ThrowIfFailed(mp_graphicsDevice->GetDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, alloc.Get(), nullptr, IID_PPV_ARGS(&list)));

	//// 3) Charger tes données dans la ressource via UpdateSubresources
	//D3D12_SUBRESOURCE_DATA sub = {};
	//// remplit sub.pData, sub.RowPitch, sub.SlicePitch depuis la mémoire CPU de l’image
	//UpdateSubresources(list.Get(), tex.resource.Get(), uploadHeap.Get(), 0, 0, 1, &sub);

	//// 4) Transition to PIXEL_SHADER_RESOURCE
	//CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
	//	tex.resource.Get(),
	//	D3D12_RESOURCE_STATE_COPY_DEST,
	//	D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
	//list->ResourceBarrier(1, &barrier);

	//// 5) Close, execute et wait
	//ThrowIfFailed(list->Close());
	//ID3D12CommandList* ppLists[] = { list.Get() };
	//mp_graphicsDevice->GetCommandQueue()->ExecuteCommandLists(1, ppLists);
	//mp_commandManager->SignalAndWait();


	//// 5) Maintenant la ressource est prête, tu peux créer ton SRV sans crash :
	//D3D12_CPU_DESCRIPTOR_HANDLE srvCpu = mp_descMgr->AllocateSrvCPU();
	//D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	//srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	//srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	//srvDesc.Texture2D.MipLevels = tex.resource->GetDesc().MipLevels;
	//mp_graphicsDevice->GetDevice()
	//	->CreateShaderResourceView(tex.resource.Get(), &srvDesc, srvCpu);

	//tex.descriptorIndex = mp_descMgr->GetSrvNextOffset() - 1;
	//return id;
}

D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::GetSrvGpuHandle(TextureID id) const
{
	UINT offset = static_cast<UINT>(m_textures.Get(id).descriptorIndex);
	auto base = mp_descMgr->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart();
	return { base.ptr + offset * mp_descMgr->GetSrvDescriptorSize() };
}