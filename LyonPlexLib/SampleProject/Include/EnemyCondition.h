#pragma once
#include "Condition.h"
#include "Ennemy.h"

class EnnemyCondition_PlayerIsNear : public Condition<Ennemy>
{
public:
	bool OnTest(Ennemy* owner) override;
};

class EnnemyCondition_PlayerIsNotNear : public Condition<Ennemy>
{
public:
	bool OnTest(Ennemy* owner) override;
};
