#pragma once

#include "StateMachine.h"

class Enemy
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
	
	Enemy();

	void Init(GameObject gameObjectEnemy, GameObject gameObjectPlayer, GameManager* gameManager);

	void OnUdpdate(float deltatime);

	const char* GetStateName(State state) const;
	const char* GetCurrentStateName() const;
	float GetDeltatime() { return m_deltatime; };

	GameObject m_ennemyGm;
	GameObject m_playerGm;

	GameObject& GetGameObject() { return m_ennemyGm; };

	void SetMoveSpeed(float speedValue) { m_moveSpeed = speedValue; };
	
	float GetMoveSpeed() { return m_moveSpeed; };
	bool m_initialized = false;

private:
	GameManager* mp_gameManager;

protected:
	friend class EnnemyAction_Idle;
	friend class EnnemyAction_Move;
};

