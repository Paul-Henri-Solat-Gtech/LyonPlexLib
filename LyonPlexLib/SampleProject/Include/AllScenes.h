#pragma once

// Includes scenes in .h

class AllScenes
{
public:
	void Init(GameManager* gameManager);
	void CreateAllScenes();
	void StartScene(std::string sceneName);
	void CreateAllTextures();
private:
	GameManager* mp_gameManager;
};

