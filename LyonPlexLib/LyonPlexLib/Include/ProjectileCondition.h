#pragma once
#include "Condition.h"
#include "Projectile.h"

class ProjectileCondition_ProjectileIsColliding : public Condition<Projectile>
{
public:
	bool OnTest(Projectile* owner) override;
};

class ProjectileCondition_ProjectileIsNotColliding : public Condition<Projectile>
{
public:
	bool OnTest(Projectile* owner) override;
};

