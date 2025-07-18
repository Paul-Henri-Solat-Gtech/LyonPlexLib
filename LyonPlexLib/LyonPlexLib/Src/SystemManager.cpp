#include "pch.h"
#include "SystemManager.h"


//void SystemManager::InitManager(ECSManager* ecs, GraphicsDevice* device, CommandManager* cmdMgr, Render3D* r3d)
//{
//    m_ecs = ecs;
//   
//
//    m_cameraSys = std::make_unique<CameraSystem>();
//    m_transformSys = std::make_unique<TransformSystem>();
//    m_lightSys = std::make_unique<LightSystem>();
//    //, m_physicsSys(std::make_unique<PhysicsSystem>()), m_renderSys(std::make_unique<RenderSystem>())
//   
//    m_cameraSys->InitRenderVariables(device, cmdMgr/*, r3d*/);
//    m_lightSys->InitVariables(device, cmdMgr);
//
//
//    m_systems.push_back(m_transformSys.get());
//    m_systems.push_back(m_cameraSys.get());
//    //m_systems.push_back(m_physicsSys.get());
//    //m_systems.push_back(m_renderSys.get());
//    m_systems.push_back(m_lightSys.get());
//
//    InitAll();
//}
void SystemManager::InitManager(ECSManager* ecs, RenderingManager* rendMngr)
{
    m_ecs = ecs;
   

    m_cameraSys = std::make_unique<CameraSystem>();
    m_transformSys = std::make_unique<TransformSystem>();
    m_lightSys = std::make_unique<LightSystem>();
    //, m_physicsSys(std::make_unique<PhysicsSystem>()), m_renderSys(std::make_unique<RenderSystem>())
   
    m_cameraSys->InitRenderVariables(rendMngr->GetGraphicsDevice(), rendMngr->GetCommandManager() /*, r3d*/);
    //m_lightSys->InitVariables(rendMngr->GetGraphicsDevice(), rendMngr->GetCommandManager());
    m_lightSys->InitVariables(rendMngr);


    m_systems.push_back(m_transformSys.get());
    m_systems.push_back(m_cameraSys.get());
    //m_systems.push_back(m_physicsSys.get());
    //m_systems.push_back(m_renderSys.get());
    m_systems.push_back(m_lightSys.get());

    InitAll();
}

void SystemManager::InitAll()
{
    for (auto& sys : m_systems)
        sys->Init(*m_ecs);
}

void SystemManager::UpdateAll(float dt)
{
    for (auto& sys : m_systems)
        sys->Update(*m_ecs, dt);
}

void SystemManager::RenderAll()
{
    for (auto& sys : m_systems)
        sys->Render(*m_ecs);
}

void SystemManager::Release()
{
    m_ecs = nullptr;
    delete m_ecs;
}
