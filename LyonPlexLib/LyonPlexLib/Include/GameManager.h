#pragma once

#include "WindowPlex.h"
#include "RenderingManager.h"
#include "ECSManager.h"
#include "SceneManager.h"
#include "SceneResources.h"
#include "SoundManager.h"
#include "AnimationManager.h"
#include "CollisionSystem.h"
#include "LightSystem.h"
#include "chrono"

class GameManager 
{
public:
    GameManager(HINSTANCE hInstance);
    ~GameManager();

    // Initialisation Window with directx
    bool Init();

    // Boucle principale
    int Run();

    void Release();
    void OnResize(UINT newW, UINT newH);

    TextureManager& GetTextureManager() { return m_renderer.GetTextureManager(); }
    MeshManager& GetMeshManager() { return m_renderer.GetMeshManager(); }
    ECSManager& GetECSManager() { return m_ECS; }

    SceneManager* GetSceneManager() { return &m_sceneManager; };
    SoundManager* GetSoundManager() { return &m_soundManager; };
    double& GetDeltaTime() { return m_deltaTime; };


private:
    void ProcessMessage(); // Gestion messages windows
    
    HINSTANCE m_hInstance;
    WindowPlex m_window;

    // Entity & Component
    ECSManager m_ECS; // DOIT ETRE RESEPARE en EntityManager (avec components) & Systems separes

    // Systems
    RenderingManager m_renderer;
    CollisionSystem m_collisionSystem;
    //LightSystem m_lightSystem;

    bool m_isRunning = false;

    // Deltatime
    double m_deltaTime;

    // Scene
    SceneManager m_sceneManager;
    SceneResources m_sceneResources;

    // Sound
    SoundManager m_soundManager;
};

