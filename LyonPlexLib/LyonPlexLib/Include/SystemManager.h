#pragma once

//#include "ISystem.h"
#include "TransformSystem.h"
#include "CameraSystem.h"
#include "LightSystem.h"
//#include "CollisionSystem.h"

class Render3D;

class SystemManager
{

public:
    SystemManager() {};

    void InitManager(ECSManager* ecs, GraphicsDevice* device, CommandManager* cmdMgr, Render3D* r3d);

    // Getters systems
    TransformSystem& GetTransformSystem() { return *m_transformSys; }
    CameraSystem& GetCameraSystem() { return *m_cameraSys; }
    //PhysicsSystem& GetPhysicsSystem() { return *m_physicsSys; }
    //RenderSystem& GetRenderSystem() { return *m_renderSys; }
    LightSystem& GetLightSystem() { return *m_lightSys; }

    void InitAll();

    void UpdateAll(float dt);

    void RenderAll();

    void Release();

private:
    ECSManager* m_ecs;
    std::vector<ISystem*> m_systems;

    // Pointeurs proprietaires (gerent la duree de vie)
    std::unique_ptr<TransformSystem>   m_transformSys;
    std::unique_ptr<CameraSystem>      m_cameraSys;
    //std::unique_ptr<PhysicsSystem>   m_physicsSys;
    //std::unique_ptr<RenderSystem>    m_renderSys;
    std::unique_ptr<LightSystem>    m_lightSys;
};

