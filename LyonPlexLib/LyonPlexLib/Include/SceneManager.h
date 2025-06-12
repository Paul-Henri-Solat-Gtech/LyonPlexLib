#pragma once

#include "Scene.h"
#include <functional>

class GameManager;

class SceneManager
{
public:
	~SceneManager();

	void Init(ECSManager* ecsManager,GameManager* gameManager , HWND windowHandle);

	//void StartScene();
	void UpdateScene(float deltatime);
	void ReleaseScene();

	// Set active scene and launch it
	void SetScene(const std::string& sceneName);

	// Save a scene model
	void RegisterScene(const std::string& sceneName, std::function<Scene*()> sceneModel);

	GameManager* GetGameManager() { return mp_gameManager; };

private:
	// Ressources
	ECSManager* mp_ecsManager;
	GameManager* mp_gameManager;
	HWND m_windowHandle; // Just for debug and window name

	// Model scenes list
	std::unordered_map<std::string, std::function<Scene* ()>> m_sceneModels;
	// Scene active
	std::unique_ptr<Scene> m_currentScene;
};

