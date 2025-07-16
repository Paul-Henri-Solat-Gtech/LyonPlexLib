#pragma once

#include "Condition.h"
#include "Player.h"

class PlayerCondition_IsAirBorne : public Condition<Player>	// Indique si le joueur a deja commence son saut ou sa chute 
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsOnGround : public Condition<Player>	// Indique s'il y a contact depuis le dessous du joueur
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsNotOnGround : public Condition<Player>	// indique s'il n'y a PAS contact depuis le dessous du joueur
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsJumping : public Condition<Player>
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

class PlayerCondition_IsCloseToEnemy : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};