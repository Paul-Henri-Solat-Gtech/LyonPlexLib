#include "pch.h"
#include "ProjectileCondition.h"
#include "Utils.h"

bool ProjectileCondition_ProjectileIsColliding::OnTest(Projectile* owner)
{
		return owner->GetHasCollided();
	
}
bool ProjectileCondition_ProjectileIsNotColliding::OnTest(Projectile* owner)
{
		return !owner->GetHasCollided();
	
}