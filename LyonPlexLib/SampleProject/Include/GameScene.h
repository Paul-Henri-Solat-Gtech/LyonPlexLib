#pragma once

#include "Player.h"
#include "Ennemy.h"

class GameScene : public Scene
{
public:
	void Start() override;
	void Update(float deltatime) override;
	void Release() override;

private:
	Player m_playerTest;
	Ennemy m_enemyTest;

	GameObject m_player;

	float m_playerWalkSpeed, m_playerRunSpeed, m_playerSpeed;
};

