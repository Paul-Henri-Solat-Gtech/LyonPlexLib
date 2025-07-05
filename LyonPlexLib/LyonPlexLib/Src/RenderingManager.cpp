#include "pch.h"
#include "RenderingManager.h"

bool RenderingManager::Init(ECSManager* ECS)
{
    mp_ECS = ECS;

    // Graphics Device
    if (!m_graphicsDevice.Init(m_windowWP)) 
    {
        return false;
    }
    m_graphicsDevice.CreateGraphicsDevice();

    // Descriptor Manager
    if (!m_descriptorManager.Init(&m_graphicsDevice))
    {
        return false;
    }
    m_descriptorManager.CreateDescriptors();

    m_graphicsDevice.SetRenderTargets(&m_descriptorManager);

    // Command Manager
    if (!m_commandManager.Init(&m_graphicsDevice, &m_descriptorManager))
    {
        return false;
    }
    m_commandManager.CreateCommandManager();

    m_textureManager.Init(&m_graphicsDevice, &m_descriptorManager);
    m_meshManager.Init(&m_graphicsDevice, &m_textureManager);

    // Render 3D
    if (!m_render3D.Init(m_windowWP, ECS, &m_graphicsDevice, &m_descriptorManager, &m_commandManager, &m_meshManager))
    {
        return false;
    }
    //m_render3D.CreatePipeline();

    // Render 2D
    if (!m_render2D.Init(m_windowWP, ECS, &m_graphicsDevice, &m_descriptorManager, &m_commandManager, &m_meshManager))
    {
        return false;
    }
    //m_render2D.CreatePipeline();


    return true;
}

void RenderingManager::RecordCommands()
{
    // 1) Demarre l’enregistrement des commandes
    m_commandManager.Begin();

    // 2) Barrier pour faire la transition du back buffer de l'etat PRESENT a RENDER_TARGET
    CD3DX12_RESOURCE_BARRIER barrier;
    SetBarrierToRenderTarget(barrier);

    UINT frameIdx = m_graphicsDevice.GetFrameIndex();
    // Clear RTV
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
        m_descriptorManager.GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(),
        frameIdx,
        m_descriptorManager.GetRtvDescriptorSize()
    );
    const float clearColor[] = { 0.1f, 0.8f, 0.3f, 1.0f };
    m_commandManager.GetCommandList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

    // Clear DSV
    CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(m_descriptorManager.GetDsvHeap()->GetCPUDescriptorHandleForHeapStart(), frameIdx, m_descriptorManager.GetDsvDescriptorSize());
    m_commandManager.GetCommandList()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

    // 3) OMSetRenderTargets (RTV + DSV)
    m_commandManager.GetCommandList()->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);
    
    //-
    // 4) Update du viewport et du scissor pour toute la surface de la fenêtre
    D3D12_VIEWPORT vp{ 0.0f, 0.0f, m_windowWidth, m_windowHeight,0.0f, 1.0f };
    D3D12_RECT sc{ 0, 0,static_cast<LONG>(m_windowWidth), static_cast<LONG>(m_windowHeight)};
    m_commandManager.GetCommandList()->RSSetViewports(1, &vp);
    m_commandManager.GetCommandList()->RSSetScissorRects(1, &sc);
    //-
    
    // Classes Render
    // 5) Dessine la scene 3D (Render3D, PSO, viewports, etc.)
    m_render3D.RecordCommands();
    m_render2D.RecordCommands();

    // 6) Transition render target : present -> fin d’enregistrement
    SetBarrierToPresent(barrier);   
    m_commandManager.End();
}


void RenderingManager::SetBarrierToRenderTarget(CD3DX12_RESOURCE_BARRIER& barrier)
{
    barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_graphicsDevice.GetRenderTargetResource(m_graphicsDevice.GetFrameIndex()), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    m_commandManager.GetCommandList()->ResourceBarrier(1, &barrier);

    // On fixe le RTV sur la bonne frame 
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_descriptorManager.GetRtvHeap()->GetCPUDescriptorHandleForHeapStart(), m_graphicsDevice.GetFrameIndex(), m_descriptorManager.GetRtvDescriptorSize());
}
void RenderingManager::SetBarrierToPresent(CD3DX12_RESOURCE_BARRIER& barrier)
{
    // Transition du back buffer de RENDER_TARGET a PRESENT pour la presentation
    barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_graphicsDevice.GetRenderTargetResource(m_graphicsDevice.GetFrameIndex()), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
    m_commandManager.GetCommandList()->ResourceBarrier(1, &barrier);
}



void RenderingManager::ExecuteCommands()
{
    m_commandManager.ExecuteCmdLists();
}

void RenderingManager::Present()
{
    m_graphicsDevice.Present();
}

void RenderingManager::SynchroGPUCPU()
{
    m_commandManager.SignalAndWait();
}

void RenderingManager::Release()
{
    mp_ECS = nullptr;

    m_graphicsDevice.Release();
    m_descriptorManager.Release();
    m_commandManager.Release();
    m_render3D.Release();
    m_render2D.Release();

    delete mp_ECS;
}

void RenderingManager::Update()
{
}

void RenderingManager::OnWindowResize(UINT newW, UINT newH)
{
    // 1) mémoriser la taille pour le viewport
    m_windowWidth = float(newW);
    m_windowHeight = float(newH);

    // 2) redimensionner la swap‑chain / RTV / DSV
    m_graphicsDevice.ResizeBuffers(newW, newH, &m_descriptorManager);

    // 3) informer les passes 3D & 2D
    m_render3D.Resize(newW, newH);
    m_render2D.Resize(newW, newH);
}
