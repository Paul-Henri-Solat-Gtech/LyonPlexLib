#pragma once

#include "Player.h"
#include "Enemy.h"
#include "FpsCamera.h"

class GameScene : public Scene
{
public:
	void Start() override;
	void Update(float deltatime) override;
	void Release() override;

private:
	Player m_playerTest;
	Enemy m_enemyTest;

	GameObject m_player;
	GameObject m_cam;
	FpsCamera m_fpsCam;

	float m_playerWalkSpeed, m_playerRunSpeed, m_playerSpeed;
};

