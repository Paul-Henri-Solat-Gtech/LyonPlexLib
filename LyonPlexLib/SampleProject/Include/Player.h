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

		Count
	};

	float m_walkSpeed = 2.0f;
	float m_runSpeed = 5.0f;
	float m_moveSpeed;
	float m_jumpPower = 5.0f;

public:
	Player();
	void Init(GameObject gameObject);
	
	void OnUdpdate();

	const char* GetStateName(State state) const;
	const char* GetCurrentStateName() const;

	GameObject m_playerGameObject;

protected:

	friend class PlayerAction_Idle;
	friend class PlayerAction_Move;
	friend class PlayerAction_Jump;
};

