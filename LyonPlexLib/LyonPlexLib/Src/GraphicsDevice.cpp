#include "pch.h"
#include "GraphicsDevice.h"




bool GraphicsDevice::Init(HWND windowWP)
{
	m_windowWP = windowWP;

	m_renderTargets.resize(FRAMECOUNT);

	return true;
}

void GraphicsDevice::CreateGraphicsDevice()
{
	CreateDevice();
	CreateCommandQueue();
	CreateSwapChain();
}

void GraphicsDevice::CreateDevice()
{
#if defined(_DEBUG)
	{
		ComPtr<ID3D12Debug> debugController;
		HRESULT hr = D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
		if (SUCCEEDED(hr) && debugController)   // <- on teste aussi que debugController n’est pas null
		{
			debugController->EnableDebugLayer();
			OutputDebugStringA("D3D12 Debug Layer active.\n");
		}
		else
		{
			OutputDebugStringA("Impossible d'activer le D3D12 Debug Layer.\n");
		}
	}
#endif
// Creer le device
//ComPtr<IDXGIFactory6> factory;
CreateDXGIFactory1(IID_PPV_ARGS(&m_factory));

/*ComPtr<IDXGIAdapter1> adapter;
m_factory->EnumAdapters1(0, &adapter);
D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device));*/

if (FAILED(D3D12CreateDevice(
	nullptr,              // adapter par defaut
	D3D_FEATURE_LEVEL_11_0,
	IID_PPV_ARGS(&m_device))))
{
	throw std::runtime_error("Échec de D3D12CreateDevice");
}

// Activation du D3D12 Debug Layer
ComPtr<ID3D12Debug> debugController;
if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
	debugController->EnableDebugLayer();
}
}

void GraphicsDevice::CreateCommandQueue()
{
	// Creer la Command queue
	D3D12_COMMAND_QUEUE_DESC cqDesc = {};
	m_device->CreateCommandQueue(&cqDesc, IID_PPV_ARGS(&m_commandQueue));
}

void GraphicsDevice::CreateSwapChain()
{
	// Creer le Swap chain
	DXGI_SWAP_CHAIN_DESC1 scDesc = {};
	scDesc.BufferCount = FRAMECOUNT;
	scDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.Width = 800;  // ou la taille de ta fenetre
	scDesc.Height = 600;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scDesc.SampleDesc.Count = 1;

	ComPtr<IDXGISwapChain1> tempSwapChain;

	HRESULT hrSC = m_factory->CreateSwapChainForHwnd(
		m_commandQueue.Get(), m_windowWP, &scDesc, nullptr, nullptr, &tempSwapChain);
	//tempSwapChain.As(&m_swapChain);

	if (FAILED(hrSC) || !tempSwapChain)
	{
		OutputDebugStringA("❌ CreateSwapChainForHwnd a echoue ou a produit un swapChain nul\n");
		// Gerez l’erreur ou throw
	}
	else
	{
		// Si vous stockez m_swapChain en IDXGISwapChain3 par exemple,
		// faites un QueryInterface en toute securite :
		hrSC = tempSwapChain->QueryInterface(IID_PPV_ARGS(&m_swapChain));
		if (FAILED(hrSC) || !m_swapChain)
		{
			OutputDebugStringA("❌ QueryInterface vers IDXGISwapChain3 a echoue\n");
			// Gerez l’erreur
		}
		else
		{
			OutputDebugStringA("✅ SwapChain cree et caste avec succes.\n");
		}
	}

	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
}

void GraphicsDevice::SetRenderTargets(DescriptorManager* descManager)
{
	m_renderTargets.resize(FRAMECOUNT);

	for (UINT i = 0; i < FRAMECOUNT; i++)
	{
		m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_renderTargets[i]));

		// alloue le prochain descriptor RTV dans le heap
		D3D12_CPU_DESCRIPTOR_HANDLE RtvHandle = descManager->AllocateRtvCPU();

		m_device->CreateRenderTargetView(m_renderTargets[i].Get(), nullptr, RtvHandle);
		m_rtvHandle.Offset(1, descManager->GetRtvDescriptorSize());
	}
}


void GraphicsDevice::Present()
{
	m_swapChain->Present(1, 0);
	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
}

void GraphicsDevice::Release()
{

}
