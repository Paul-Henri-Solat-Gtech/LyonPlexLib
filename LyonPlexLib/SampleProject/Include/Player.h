#pragma once
#include "StateMachine.h"

class Player
{
	StateMachine<Player> m_StateMachine;

	enum State
	{
		Idle,
		Move,
		Jump,

		Count
	};

	int mAmmo;
	int mMaxAmmo = 6;

	float mShootCadence = 1.0f;

	float mReloadDuration = 2.0f;

	int mAreaIndex;

public:
	Player();

	const char* GetStateName(State state) const;

protected:

	friend class PlayerAction_Idle;
	friend class PlayerAction_Move;
	friend class PlayerAction_Jump;
};

