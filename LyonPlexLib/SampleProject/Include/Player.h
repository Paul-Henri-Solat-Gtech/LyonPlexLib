#pragma once
#include "StateMachine.h"

class Player
{
	StateMachine<Player> m_stateMachine;

	enum State
	{
		Idle,
		Move,
		Jump,
		Attack,
		Fall,

		Count
	};

	int m_hp = 10;

	float m_walkSpeed = 2.0f;
	float m_runSpeed = 5.0f;
	float m_moveSpeed;
	float m_jumpPower = 5.0f;
	float m_invicibilityCooldown = 2.0f;

	float m_deltatime;

public:
	Player();
	void Init(GameObject gameObject, GameManager* gameManager);
	
	void OnUdpdate(float deltatime);

	const char* GetStateName(State state) const;
	const char* GetCurrentStateName() const;

	GameObject m_playerGameObject;
	GameObject m_playerArm;

	GameObject& GetGameObject() { return m_playerGameObject; };
	void SetPlayerArm(GameObject& armGm) { m_playerArm = armGm; };
	GameObject& GetPlayerArm() { return m_playerArm; };

	void SetMoveSpeed(float speedValue) { m_moveSpeed = speedValue; };
	float GetRunSpeed() { return m_runSpeed; };
	float GetWalkSpeed() { return m_walkSpeed; };
	float GetMoveSpeed() { return m_moveSpeed; };

	float GetDeltatime() { return m_deltatime; };

	//Test Animation
	AnimationManager m_testAnimation;
	bool m_attackFinished;

private:
	GameManager* mp_gameManager;

protected:
	friend class PlayerAction_Idle;
	friend class PlayerAction_Move;
	friend class PlayerAction_Jump;
	friend class PlayerAction_Attack;
};

