#pragma once
#include "Action.h"
#include "Player.h"

// Two way to make action:
// void Start(Player* player) override {} <- Dont need to be defined use the default (can be used on action who do nothing like idle)
// &
// void Start(Player* player) override    <- Need to be implemented

class PlayerAction_Idle : public Action<Player>
{
public:
	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;

	AnimationManager m_idleAnim;
};

class PlayerAction_Move : public Action<Player>
{
public:
	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;

	bool m_canMoveArm,m_armIsUp;
	float m_cooldownArmMovement, m_cooldownArmMovementActual;
};

class PlayerAction_Jump : public Action<Player>
{
public:
	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;
};

class PlayerAction_Attack : public Action<Player>
{
public:
	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;

	AnimationManager m_attackAnim;
};

class PlayerAction_Fall : public Action<Player>
{
public:
	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;
};

class PlayerAction_PickUp : public Action<Player>
{
public:
	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;
};

