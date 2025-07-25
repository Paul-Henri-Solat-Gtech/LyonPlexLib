#include "pch.h"
#include "EnemyAction.h"

void EnnemyAction_Move::Start(Enemy* ennemy)
{
	OutputDebugStringA("-ENEMY START MOVING !");
}

void EnnemyAction_Move::Update(Enemy* ennemy)
{
	//OutputDebugStringA("ENEMY IS MOVING !");
	//ennemy->SetPosition({ ennemy->GetPosition().x + 0.5f * ennemy->m_deltatime, ennemy->GetPosition().y, ennemy->GetPosition().z });
	ennemy->LookAt(ennemy->m_playerGm);
	ennemy->MoveForward(ennemy->m_deltatime * 2);
}

void EnnemyAction_Move::End(Enemy* ennemy)
{
	//OutputDebugStringA("ENEMY STOP MOVING !-");
}

void EnnemyAction_Shoot::Start(Enemy* ennemy)
{
	OutputDebugStringA("-ENEMY START SHOOTING !");

	CreateProjectile(ennemy);
}

void EnnemyAction_Shoot::Update(Enemy* ennemy)
{
	ennemy->LookAt(ennemy->m_playerGm);

	if (m_newProj != nullptr && m_projLifetime > 0.0f)
	{
		m_newProj->MoveForward(ennemy->m_deltatime * 30);
		m_projLifetime -= ennemy->m_deltatime;
	}
	else if (m_newProj != nullptr && m_projLifetime <= 0.0f)
	{
		ennemy->mp_scene->DestroyGameObject(*m_newProj);
		m_newProj = nullptr;
		m_projAsSpawned = false;
		CreateProjectile(ennemy);
	}
	// make player take damge here with collider
	// maybe use another class to update bullets
}

void EnnemyAction_Shoot::End(Enemy* ennemy)
{
	//ennemy->mp_scene->DestroyGameObject(*m_newProj);
}

void EnnemyAction_Shoot::CreateProjectile(Enemy* ennemy)
{
	if (!m_projAsSpawned)
	{
		std::string projName = "newProjectile" + std::to_string(ennemy->mp_scene->GetSceneGameObjects().size());
		OutputDebugStringA(projName.c_str());
		m_newProj = &ennemy->mp_scene->CreateGameObject(projName);
		m_newProj->SetPosition(ennemy->GetPosition());
		m_newProj->SetScale({0.2,0.2,0.8});
		m_newProj->LookAt(ennemy->m_playerGm);
		m_projAsSpawned = true;
		m_projLifetime = 3.f;
		// ADD COLLISION
	}
}
