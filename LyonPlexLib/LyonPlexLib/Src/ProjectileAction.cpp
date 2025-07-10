#include "pch.h"
#include "ProjectileAction.h"

void ProjectileAction_Move::Start(Projectile* projectile)
{
	OutputDebugStringA("\n-PROJECTILE START MOVING !\n");
}

void ProjectileAction_Move::Update(Projectile* projectile)
{
	auto& proj = projectile->m_projectileGameObject;

	proj.SetPosition({ proj.GetPosition().x, proj.GetPosition().y, proj.GetPosition().z + 0.5f * projectile->m_deltatime });
}

void ProjectileAction_Move::End(Projectile* projectile)
{
	OutputDebugStringA("\nPROJECTILE STOP MOVING !-\n");
}


void ProjectileAction_Collide::Start(Projectile* projectile)
{
	OutputDebugStringA("\n-PROJECTILE IS COLLIDING !\n");
}

void ProjectileAction_Collide::Update(Projectile* projectile)
{
	/*auto& proj = projectile->m_projectileGameObject;

	proj.SetPosition({ proj.GetPosition().x, proj.GetPosition().y, proj.GetPosition().z + 0.5f * projectile->GetDeltatime()});*/
}

void ProjectileAction_Collide::End(Projectile* projectile)
{
	OutputDebugStringA("\nPROJECTILE STOP COLLIDING !-\n");
}