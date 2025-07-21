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
	
	Enemy(ECSManager* ecsManager, GameManager* gameManager, GameObject& gameObjectPlayer, Scene* scene);


	void Init(/*GameObject gameObjectPlayer,*/ GameManager* gameManager);



	void OnUdpdate(float deltatime) override;

	const char* GetStateName(State state) const;
	const char* GetCurrentStateName() const;
	float GetDeltatime() { return m_deltatime; };

	void TakeDamage();

	//GameObject m_ennemyGm;
	GameObject& m_playerGm;

	//GameObject& GetGameObject() { return m_ennemyGm; };

	void SetMoveSpeed(float speedValue) { m_moveSpeed = speedValue; };
	
	float GetMoveSpeed() { return m_moveSpeed; };
	bool m_initialized = false;




private:
	GameManager* mp_gameManager = nullptr;

	int m_life = 3;

protected:
	friend class EnnemyAction_Idle;
	friend class EnnemyAction_Move;
};

