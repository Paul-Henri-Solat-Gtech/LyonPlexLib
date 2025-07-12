#pragma once

#include "Condition.h"
#include "Player.h"

class PlayerCondition_IsInTheAir : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsOnGround : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsMoving : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsNotMoving : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsAttacking : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_AttackFinished : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsPickingUp : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsCloseToObject : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsNotPickingUp : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};
