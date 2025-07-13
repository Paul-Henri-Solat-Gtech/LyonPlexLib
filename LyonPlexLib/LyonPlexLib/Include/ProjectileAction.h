#pragma once
#include "Action.h"
#include "Projectile.h"


class ProjectileAction_Idle : public Action<Projectile>
{
public:
	void Start(Projectile* projectile) override {};
	void Update(Projectile* projectile) override {};
	void End(Projectile* projectile) override {};
};

class ProjectileAction_Move : public Action<Projectile>
{
public:
	void Start(Projectile* projectile) override;
	void Update(Projectile* projectile) override;
	void End(Projectile* projectile) override;
};

class ProjectileAction_Collide : public Action<Projectile>
{
public:
	void Start(Projectile* projectile) override;
	void Update(Projectile* projectile) override;
	void End(Projectile* projectile) override;
};
