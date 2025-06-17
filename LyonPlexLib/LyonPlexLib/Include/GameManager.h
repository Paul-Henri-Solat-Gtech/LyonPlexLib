#pragma once

#include "WindowPlex.h"
#include "RenderingManager.h"
#include "ECSManager.h"
#include "SceneManager.h"
//#include "WICTextureLoader.h"
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

    TextureManager& GetTextureManager() { return m_renderer.GetTextureManager(); }

    SceneManager* GetSceneManager() { return &m_sceneManager; };
    double& GetDeltaTime() { return m_deltaTime; };

private:
    void ProcessMessage(); // Gestion messages windows

    HINSTANCE m_hInstance;
    WindowPlex m_window;

    // Entity & Component
    ECSManager m_ECS; // DOIT ETRE RESEPARE en EntityManager (avec components) & Systems separes

    // Systems
    RenderingManager m_renderer;


    bool m_isRunning = false;

    // Deltatime
    double m_deltaTime;

    // Scene
    SceneManager m_sceneManager;
};

