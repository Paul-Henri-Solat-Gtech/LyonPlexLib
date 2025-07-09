#pragma once
#include "Action.h"
#include "Ennemy.h"

// Two way to make action:
// void Start(Ennemy* Ennemy) override {} <- Dont need to be defined use the default (can be used on action who do nothing like idle)
// &
// void Start(Ennemy* Ennemy) override    <- Need to be implemented

class EnnemyAction_Idle : public Action<Ennemy>
{
public:
	void Start(Ennemy* ennemy) override {};
	void Update(Ennemy* ennemy) override {};
	void End(Ennemy* ennemy) override {};
};

class EnnemyAction_Move : public Action<Ennemy>
{
public:
	void Start(Ennemy* ennemy) override;
	void Update(Ennemy* ennemy) override;
	void End(Ennemy* ennemy) override;
};

