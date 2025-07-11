#pragma once
#include "Condition.h"
#include "Enemy.h"

class EnnemyCondition_PlayerIsNear : public Condition<Enemy>
{
public:
	bool OnTest(Enemy* owner) override;
};

class EnnemyCondition_PlayerIsNotNear : public Condition<Enemy>
{
public:
	bool OnTest(Enemy* owner) override;
};
