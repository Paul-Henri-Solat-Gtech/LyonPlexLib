#pragma once
#include "Action.h"
#include "Enemy.h"

// Two way to make action:
// void Start(Ennemy* Ennemy) override {} <- Dont need to be defined use the default (can be used on action who do nothing like idle)
// &
// void Start(Ennemy* Ennemy) override    <- Need to be implemented

class EnnemyAction_Idle : public Action<Enemy>
{
public:
	void Start(Enemy* ennemy) override {};
	void Update(Enemy* ennemy) override {};
	void End(Enemy* ennemy) override {};
};

class EnnemyAction_Move : public Action<Enemy>
{
public:
	void Start(Enemy* ennemy) override;
	void Update(Enemy* ennemy) override;
	void End(Enemy* ennemy) override;
};

class EnnemyAction_Shoot : public Action<Enemy>
{
public:
	void Start(Enemy* ennemy) override;
	void Update(Enemy* ennemy) override;
	void End(Enemy* ennemy) override;

	void CreateProjectile(Enemy* ennemy);
private:
	GameObject* m_newProj = nullptr;
	float m_projLifetime = 3;
	bool m_projAsSpawned = false;
};

class EnnemyAction_Flee : public Action<Enemy>
{
public:
	void Start(Enemy* ennemy) override {};
	void Update(Enemy* ennemy) override;
	void End(Enemy* ennemy) override {};
};

class EnnemyAction_Roam : public Action<Enemy>
{
public:
	void Start(Enemy* ennemy) override;
	void Update(Enemy* ennemy) override;
	void End(Enemy* ennemy) override;

	void SetNextLocation(Enemy* ennemy);
private:
	XMFLOAT3 m_nextPosition;
};