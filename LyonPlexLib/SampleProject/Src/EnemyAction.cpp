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
		m_newProj->MoveForward(ennemy->m_deltatime * 50);
		m_projLifetime -= ennemy->m_deltatime;
		//if (m_newProj->GetComponent<CollisionComponent>()) 
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
	ennemy->mp_scene->DestroyGameObject(*m_newProj);
	m_newProj = nullptr;
	m_projAsSpawned = false;
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
		auto projScale = m_newProj->GetScale();
		m_newProj->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ projScale.x / 2, projScale.y / 2, projScale.z / 2 })));
		m_newProj->SetTag(Tag::TAG_Projectile);
		m_newProj->LookAt(ennemy->m_playerGm);
		m_projAsSpawned = true;
		m_projLifetime = 3.f;
		// ADD COLLISION
	}
}

void EnnemyAction_Flee::Update(Enemy* ennemy)
{
	ennemy->LookAt(ennemy->m_playerGm);
	ennemy->MoveBackward(ennemy->GetDeltatime() * 8);
}

void EnnemyAction_Roam::Start(Enemy* ennemy)
{
	SetNextLocation(ennemy);
}
void EnnemyAction_Roam::Update(Enemy* ennemy)
{
	if (ennemy->GetPosition().x != m_nextPosition.x || ennemy->GetPosition().y != m_nextPosition.y)
	{
		ennemy->LookAt(m_nextPosition);
		ennemy->MoveForward(ennemy->GetDeltatime() * ennemy->m_moveSpeed);
	}
	else
	{
		SetNextLocation(ennemy);
	}
}
void EnnemyAction_Roam::End(Enemy* ennemy)
{

}

void EnnemyAction_Roam::SetNextLocation(Enemy* ennemy)
{
	int randChoice = std::rand() % 3;  // 0=X, 1=Z, 2=les deux
	int randX = 0, randZ = 0;
	switch (randChoice)
	{
	case 0:
		randX = std::rand() % 41 - 20; //entre -40 et 40
		break;
	case 1:
		randZ = std::rand() % 41 - 20;
		break;
	case 2:
		randX = std::rand() % 41 - 20;
		randZ = std::rand() % 41 - 20;
		break;
	default:
		break;
	}
	m_nextPosition = { ennemy->GetPosition().x + randX,ennemy->GetPosition().y,ennemy->GetPosition().z + randZ };
}
