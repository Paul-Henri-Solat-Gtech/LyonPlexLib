#pragma once

#include "FpsCamera.h"
#include <Player.h>

class ArenaScene : public Scene
{
public:
	void Start() override;
	void Update(float deltatime) override;
	void Release() override;

	void SpawnMenu();
	void RemoveMenu();

	void WaveSystem();
	void WeaponSystem();

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
	bool m_waveFinished;
};

