#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Portals.h"
#include "FpsCamera.h"

class GameScene : public Scene
{
public:
	void Start() override;
	void Update(float deltatime) override;
	void Release() override;

	void SpawnMenu();

	void RemoveMenu();

private:
	Player m_playerTest;
	//Enemy m_enemyTest;
	Portals* portal = nullptr;

	GameObject m_player;
	GameObject m_cam;
	FpsCamera m_fpsCam;

	float m_playerWalkSpeed, m_playerRunSpeed, m_playerSpeed;

	float m_spawnTimer = 0;

	bool m_pauseIsOpen;
	GameObject pauseMenu;
	Button* mp_btnMainMenu;

	//debug fps
	std::chrono::high_resolution_clock::time_point s_lastReport = std::chrono::high_resolution_clock::now();
	uint64_t s_frameCount = 0;
	double s_accumMs = 0.0;
	uint64_t g_drawCalls = 0;
};

