#pragma once
#include "Enemy.h"

class Portals : public GameObject
{
public:

	Portals(GameObject& gameObjectPlayer, Scene* scene, int ennemyNb, float groundY);
	Portals(GameObject& gameObjectPlayer, Scene* scene, int ennemyNb, float groundY, EnemyType enemyType);
	//~Portals();

	void OnUpdate(float deltatime) override;

	bool SpawnIsFinished() { return m_finishedSpawning; };

	GameObject& m_playerGm;
private:
	GameManager* mp_gameManager = nullptr;
	ECSManager* mp_ecs = nullptr;
	//GameObject& m_portalGm;

	float m_timer = 0;
	int m_capacity = 3;
	float m_groundY;
	bool m_finishedSpawning;

	bool m_chooseEnemy;
	EnemyType m_choosedEnemy;

	float m_rotation;
};

