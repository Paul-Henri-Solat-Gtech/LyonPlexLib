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

	void SpawnPortal(XMFLOAT3 newPos, int nbEnemy);
	void SpawnPortal(XMFLOAT3 newPos, int nbEnemy, EnemyType enemyType);

	void PortalSystem();

private:
	Player m_playerTest;
	//Enemy m_enemyTest;

	//win
	bool m_youWin;
	float m_chronoChangeScene;

	//Portals for the lvl1
	Portals* m_portal = nullptr;

	// firstPortalHasSpawned = p_1Spawned
	bool m_p1Spawned, m_p2Spawned, m_p3Spawned, m_p4Spawned, m_p5Spawned, m_pBossSpawned;
	bool m_p1Finished, m_p2Finished, m_p3Finished, m_p4Finished, m_p5Finished, m_pBossFinished;

	//GameObject m_player;
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

