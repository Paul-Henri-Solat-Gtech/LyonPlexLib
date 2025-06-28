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

	float m_moveSpeed = 2.0f;
	float m_jumpPower = 5.0f;

public:
	Player();
	
	void OnUdpdate();

	const char* GetStateName(State state) const;

protected:

	friend class PlayerAction_Idle;
	friend class PlayerAction_Move;
	friend class PlayerAction_Jump;
};

