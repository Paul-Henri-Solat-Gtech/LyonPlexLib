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

//class PlantCondition_FullAmmo : public Condition<Player>
//{
//public:
//	bool OnTest(Plant* owner) override;
//};