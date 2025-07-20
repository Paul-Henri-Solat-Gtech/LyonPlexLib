#pragma once

#include "StateMachine.h"

class Enemy : public GameObject
{
	StateMachine<Enemy> m_stateMachine;

	enum State
	{
		Idle,
		Move,

		Count
	};

	int m_hp = 10;
	float m_moveSpeed = 2.f;
	float m_jumpPower = 5.0f;

	float m_deltatime;

public:
	
	Enemy(ECSManager* ecsManager, GameManager* gameManager, GameObject gameObjectPlayer/*, std::vector<std::unique_ptr<GameObject>>& sceneGameObjects*/);


	//Enemy(const std::string& name, ECSManager* ecsManager);
	//Enemy(const std::string& name, ECSManager* ecsManager, uint32_t meshId, uint32_t textureId);
	//Enemy(const std::string& name, ECSManager* ecsManager, DimensionalType type, bool useMesh);


	//void Init(GameObject gameObjectEnemy, GameObject gameObjectPlayer, GameManager* gameManager);

	void Init(GameObject gameObjectPlayer, GameManager* gameManager);



	void OnUdpdate(float deltatime) override;

	const char* GetStateName(State state) const;
	const char* GetCurrentStateName() const;
	float GetDeltatime() { return m_deltatime; };

	//GameObject m_ennemyGm;
	GameObject m_playerGm;

	//GameObject& GetGameObject() { return m_ennemyGm; };

	void SetMoveSpeed(float speedValue) { m_moveSpeed = speedValue; };
	
	float GetMoveSpeed() { return m_moveSpeed; };
	bool m_initialized = false;

	/*void SetID(int enemyID) { m_enemyID = enemyID; };
	int m_enemyID = -1;*/

private:
	GameManager* mp_gameManager = nullptr;

protected:
	friend class EnnemyAction_Idle;
	friend class EnnemyAction_Move;
};

