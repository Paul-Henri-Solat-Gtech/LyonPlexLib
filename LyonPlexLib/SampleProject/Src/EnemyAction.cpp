#include "pch.h"
#include "EnemyAction.h"

void EnnemyAction_Move::Start(Ennemy* ennemy)
{
	OutputDebugStringA("-ENEMY START MOVING !");
}

void EnnemyAction_Move::Update(Ennemy* ennemy)
{
	//OutputDebugStringA("ENEMY IS MOVING !");
	ennemy->m_ennemyGm.SetPosition({ ennemy->m_ennemyGm.GetPosition().x + 0.5f * ennemy->m_deltatime, ennemy->m_ennemyGm.GetPosition().y, ennemy->m_ennemyGm.GetPosition().z });
}

void EnnemyAction_Move::End(Ennemy* ennemy)
{
	OutputDebugStringA("ENEMY STOP MOVING !-");
}
