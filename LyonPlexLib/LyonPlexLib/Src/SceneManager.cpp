#include "pch.h"
#include "SceneManager.h"
#include "GameManager.h"

SceneManager::~SceneManager()
{
	if (m_currentScene) 
	{
		m_currentScene->Release();
		mp_ecsManager->ClearAllEntities();
		m_currentScene.reset();
	}
}

void SceneManager::Init(ECSManager* ecsManager, GameManager* gameManager, HWND windowHandle)
{
	mp_ecsManager = ecsManager;
	mp_gameManager = gameManager;
	m_windowHandle = windowHandle;
}

void SceneManager::UpdateScene(float deltaTime)
{
	if (m_currentScene) 
	{
		m_currentScene->Update(deltaTime);
	}
}

void SceneManager::ReleaseScene() 
{
	if (m_currentScene) 
	{
		m_currentScene->Release();
		if (mp_ecsManager)
		{
			mp_ecsManager->ClearAllEntities();
		}
		m_currentScene.reset();
	}
}

void SceneManager::SetScene(const std::string& sceneName) {
	
	// 0) Stop les musiques
	mp_gameManager->GetSoundManager()->StopMusic();

	// 1) Release et delete scene active
	ReleaseScene();

	// 2) Trouver la factory
	auto sceneModel = m_sceneModels.find(sceneName);
	if (sceneModel == m_sceneModels.end())
	{
		std::string msg = "\n[SceneManager] Scene '" + sceneName + "' not found.";
		OutputDebugStringA(msg.c_str());
		return;
	}

	// 3) Creer une nouvelle instance
	Scene* newScene = sceneModel->second(); // new SampleScene2() par exemple -> second est la 2eme valeur de lobjet stocker a savoir ici la class derive scene

	// 4) Initialiser la scene
	newScene->SetEcsManager(mp_ecsManager);
	newScene->Init(this);
	m_currentScene.reset(newScene);

	// 5) Mise a jour du titre de la fenetre
	if (m_windowHandle) 
	{
		std::string titleW = "[LyonPlex] [ scene : " + sceneName + " ]";
		std::wstring wname(titleW.begin(), titleW.end());
		SetWindowText(m_windowHandle, wname.c_str());
	}

	// Debug
	std::string msg2 = "\n[SceneManager] Scene '" + sceneName + "' started.";
	OutputDebugStringA(msg2.c_str());
}

void SceneManager::RegisterScene(const std::string& sceneName, std::function<Scene* ()> sceneModel) 
{
	m_sceneModels[sceneName] = sceneModel;
	
	// Debug
	std::string msg = "\n[RegisterScene] " + sceneName + " registered.";
	OutputDebugStringA(msg.c_str());
}

