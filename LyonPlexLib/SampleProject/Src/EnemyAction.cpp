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
	ennemy->CreateProjectile(ennemy->GetPosition(), ennemy->m_playerGm.GetPosition());
}
void EnnemyAction_Shoot::Update(Enemy* ennemy)
{
	ennemy->LookAt(ennemy->m_playerGm);
}
void EnnemyAction_Shoot::End(Enemy* ennemy)
{
}

void EnnemyAction_Flee::Update(Enemy* ennemy)
{
	ennemy->LookAt(ennemy->m_playerGm);
	ennemy->MoveBackward(ennemy->GetDeltatime() * 8);
}

void EnnemyAction_Roam::Start(Enemy* ennemy)
{
	m_maxX = ennemy->GetPosition().x + 100;
	m_minX = ennemy->GetPosition().x - 100;
	m_maxZ = ennemy->GetPosition().z + 100;
	m_minZ = ennemy->GetPosition().z - 100;
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
	int randX = 0, randZ = 0;
	float currX = ennemy->GetPosition().x;
	float currZ = ennemy->GetPosition().z;

	do {
		int randChoice = std::rand() % 3;  // on recalcule a chaque tour
		switch (randChoice)
		{
		case 0: // uniquement X
			randX = std::rand() % 41 - 20;
			randZ = 0;
			break;
		case 1: // uniquement Z
			randX = 0;
			randZ = std::rand() % 41 - 20;
			break;
		case 2: // X et Z
			randX = std::rand() % 41 - 20;
			randZ = std::rand() % 41 - 20;
			break;
		}
		// on boucle tant que la pos sort des bornes X ou Z
	} while (currX + randX < m_minX || currX + randX > m_maxX || currZ + randZ < m_minZ || currZ + randZ > m_maxZ);

	// enfin on fixe la vraie prochaine position
	m_nextPosition = {currX + randX,ennemy->GetPosition().y,currZ + randZ};
}
