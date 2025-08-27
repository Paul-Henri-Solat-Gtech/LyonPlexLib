#pragma once

#include "FpsCamera.h"
#include "Portals.h"
#include <Player.h>

class ArenaScene : public Scene
{
public:
	void Start() override;
	void Update(float deltatime) override;
	void Release() override;

	void SpawnMenu();
	void RemoveMenu();

	void WeaponSystem();

	void WaveSystem(float deltatime);
	void SpawnPortal();

private:
	//Camera
	GameObject m_cam;
	FpsCamera m_fpsCam;

	//Player
	Player m_player;

	//Pause menu
	bool m_pauseIsOpen;
	GameObject pauseMenu;
	Button* mp_btnMainMenu;

	//Wave
	int m_waveNow, m_waveMax;
	bool m_waveStarted, m_waveFinished;
	float m_cooldownNextWave;

	//Portal
	Portals* m_portal = nullptr;
	int m_portalNbSpawned;
	bool m_portalHasSpawned, m_fisrtEnnemyHasSpawned;
};

