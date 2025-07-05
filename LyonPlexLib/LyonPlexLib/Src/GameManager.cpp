#include "pch.h"
#include "GameManager.h"
#include "Utils.h"

// Scenes
#include "SampleScene.h"
#include "DevScene.h"

GameManager::GameManager(HINSTANCE hInstance) : m_hInstance(hInstance)
{
}

GameManager::~GameManager()
{
	// Nettoyage si besoin
}

bool GameManager::Init()
{
	CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);

	// 1) Creer la fenetre
	if (!m_window.Init(m_hInstance, L"MonJeuDX12", 800, 600))
		return false;

	// 2) Configurer le renderer avec le handle de la fenetre
	HWND hwnd = m_window.GetWindowHandle();
	m_renderer.SetWindowHandle(hwnd);
	m_renderer.Init(&m_ECS); // A VOIR MODIFIER ET METTRE HWND COMME ARGUMENT EN POINTEUR (et mettre le init en bool)
	//m_renderer.OnWindowResize(800, 600);

	m_ECS.Init(m_renderer.GetGraphicsDevice(), m_renderer.GetCommandManager(), m_renderer.GetRender3D()); // A MODIFIER AUSSI => ne doit pas avoir besoin de renderer

	m_isRunning = true;

	// 3) Init sceneManager
	m_sceneManager.Init(&m_ECS, this, hwnd);

	// 4) Create new scene (OPTIONAL IN LIB)
	m_sceneManager.RegisterScene("SampleScene", []() { return new SampleScene(); });
	m_sceneManager.RegisterScene("DevScene", []() { return new DevScene(); });

	// 5) Init Textures & Meshes Resources
	m_sceneResources.Init(this);

	// 6) Init sounds
	m_soundManager.Init();
	m_soundManager.CreateSound("pop", L"../LyonPlexLib/Ressources/pop.wav");

	m_window.SetGameManager(this);

	return true;
}

int GameManager::Run()
{

	// Message et boucle de rendu
	MSG msg = {};

	// Delatime
	double t = Utils::getTimeSeconds();

	while (m_isRunning)
	{
		// Delatime
		m_deltaTime = Utils::getTimeSeconds() - t;
		t = Utils::getTimeSeconds();


		// 1) Gestion des messages Windows
		//ProcessMessage();

		// 2) Traitement manuel des messages restants
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
			{
				// Si on recoit WM_QUIT, on sort de la boucle
				m_isRunning = false;
			}
			TranslateMessage(&msg); // Prepare le message (gestion du clavier, etc.)
			DispatchMessage(&msg); // Appelle la WindowProcedure correspondante
		}
		// UPDATE
		m_renderer.Update();
		m_ECS.m_systemMgr.UpdateAll(0);
		m_sceneManager.UpdateScene(m_deltaTime);

		// Enregistrement et envoi des commandes

		// 3) Enregistrement des commandes de rendu dans la CommandList
		m_renderer.RecordCommands();

		// 4) Soumission des commandes au GPU pour execution
		m_renderer.ExecuteCommands();

		// 5) Presentation du back buffer a l’ecran (swap buffers)
		m_renderer.Present();

		// Synchronisation CPU/GPU (on attend que le GPU ait fini)
		m_renderer.SynchroGPUCPU();

		m_ECS.EndFrame();
	}

	Release();

	return static_cast<int>(msg.wParam);
}

void GameManager::Release()
{
	m_renderer.Release();
	m_sceneManager.ReleaseScene();
	m_soundManager.Release();
}

void GameManager::OnResize(UINT newW, UINT newH)
{
	// 1) Mets d’abord à jour ta classe fenêtre
	m_window.OnResize(newW, newH);
	m_renderer.OnWindowResize(newW, newH);
	OutputDebugStringA(("GameManager::OnResize: " + std::to_string(newW) + "×" + std::to_string(newH) + "\n").c_str());
	// 2) Resize du swap‑chain et des render targets
	//m_renderer.GetGraphicsDevice()->ResizeBuffers(newW, newH, &m_renderer.GetDescriptorManager());

	// 3) Mettre à jour l’aspect ratio de la caméra
	{
		// Récupère le système caméra
		auto& camSys = m_ECS.m_systemMgr.GetCameraSystem();
		// Parcours de toutes les entités caméra (ici on suppose une seule)
		ComponentMask camMask = (1ULL << CameraComponent::StaticTypeID) | (1ULL << TransformComponent::StaticTypeID);
		m_ECS.ForEach(camMask, [&](Entity e) 
		{
			auto* cam = m_ECS.GetComponent<CameraComponent>(e);
			if (!cam) return;
			cam->aspectRatio = float(newW) / float(newH);
			cam->projectionDirty = true;    // forcera le recalcule lors du prochain Update()
		});
	}
	m_ECS.m_systemMgr.UpdateAll(0.0f);

	// 4) Resize des passes 3D et 2D
	/*m_renderer.GetRender3D()->Resize(newW, newH);
	m_renderer.GetRender2D()->Resize(newW, newH);*/
}

void GameManager::ProcessMessage()
{
	MSG msg;
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_SIZE && msg.wParam != SIZE_MINIMIZED)
		{
			UINT newW = LOWORD(msg.lParam);
			UINT newH = HIWORD(msg.lParam);
			OnResize(newW, newH);
		}

		if (msg.message == WM_QUIT)
			m_isRunning = false;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}