#include "pch.h"
#include "EnemyAction.h"


void EnnemyAction_Idle::Start(Enemy* ennemy)
{
	m_idleAnim.Init(0.05f, ennemy);

	switch (ennemy->m_type)
	{
	case EnemyType::Crabe:
	{
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_1);
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_2);
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_3);
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_4);
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_5);
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_6);
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_7);
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_8);
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_9);
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_10);
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_11);
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_12);
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_13);
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_14);
		m_idleAnim.AddFrame(TEXTURES::CRABE_IDLE_15);
		break;
	}
	case EnemyType::Golem:
	{
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_1);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_2);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_3);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_4);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_5);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_6);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_7);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_8);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_9);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_10);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_11);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_12);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_13);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_14);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_15);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_16);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_17);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_18);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_19);
		m_idleAnim.AddFrame(TEXTURES::GOLEM_IDLE_20);
	break;
	}
	}
}
void EnnemyAction_Idle::Update(Enemy* ennemy)
{
	m_idleAnim.AnimationSequence(ennemy->GetDeltatime());
	ennemy->LookAt(ennemy->m_playerGm);
}

void EnnemyAction_Move::Start(Enemy* ennemy)
{
	//OutputDebugStringA("-ENEMY START MOVING !");
	//animation
	m_moveAnim.Init(0.05f, ennemy);
	// move frames (switch case enemy type)
	switch (ennemy->m_type)
	{
		case EnemyType::Crabe:
		{
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_1);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_2);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_3);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_4);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_5);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_6);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_7);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_8);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_9);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_10);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_11);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_12);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_13);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_14);

		}
		break;
		case EnemyType::Golem:
		{
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_1);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_2);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_3);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_4);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_5);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_6);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_7);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_8);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_9);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_10);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_11);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_12);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_13);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_14);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_15);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_16);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_17);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_18);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_19);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_20);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_21);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_22);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_23);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_24);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_25);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_26);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_27);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_28);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_29);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_30);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_31);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_32);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_33);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_34);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_35);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_36);
		}
		break;
	}

}
void EnnemyAction_Move::Update(Enemy* ennemy)
{
	//OutputDebugStringA("ENEMY IS MOVING !");
	//ennemy->SetPosition({ ennemy->GetPosition().x + 0.5f * ennemy->m_deltatime, ennemy->GetPosition().y, ennemy->GetPosition().z });
	m_moveAnim.AnimationSequence(ennemy->GetDeltatime());
	ennemy->LookAt(ennemy->m_playerGm);
	ennemy->MoveForward(ennemy->m_deltatime * 2);
}
void EnnemyAction_Move::End(Enemy* ennemy)
{
	//OutputDebugStringA("ENEMY STOP MOVING !-");
	switch (ennemy->m_type)
	{
		case EnemyType::Crabe:
			ennemy->SetTexture(TEXTURES::CRABE_IDLE_1);
			break;
		case EnemyType::Golem:
			ennemy->SetTexture(TEXTURES::GOLEM_IDLE_1);
			break;
	}
}

void EnnemyAction_Shoot::Start(Enemy* ennemy)
{
	//OutputDebugStringA("-ENEMY START SHOOTING !");
	m_nextShootTimer = 0;
	//ennemy->CreateProjectile(ennemy->GetPosition(), ennemy->m_playerGm.GetPosition());

	//animation
	m_shootAnim.Init(0.05f, ennemy);
	// shoot frames (switch case enemy type)
	switch (ennemy->m_type)
	{
		case EnemyType::Crabe:
		{
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_1);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_2);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_3);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_4);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_5);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_6);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_7);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_8);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_9);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_10);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_11);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_12);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_13);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_14);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_15);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_16);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_17);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_18);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_19);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_20);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_21);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_22);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_23);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_24);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_25);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_26);
			m_shootAnim.AddFrame(TEXTURES::CRABE_ATTACK_27);
		}
		break;
		case EnemyType::Golem:
		{
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_1);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_2);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_3);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_4);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_5);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_6);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_7);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_8);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_9);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_10);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_11);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_12);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_13);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_14);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_15);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_16);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_17);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_18);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_19);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_20);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_21);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_22);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_23);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_24);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_25);
			m_shootAnim.AddFrame(TEXTURES::GOLEM_ATTACK_26);
		}
		break;
	}
}
void EnnemyAction_Shoot::Update(Enemy* ennemy)
{
	m_shootAnim.AnimationSequence(ennemy->GetDeltatime());
	//m_shootAnim.Loop(ennemy->GetDeltatime());
	if (m_nextShootTimer >= ennemy->m_reloadSpeed)
	{
		ennemy->CreateProjectile(ennemy->GetPosition(), ennemy->m_playerGm.GetPosition(), 5.f);
		m_nextShootTimer = 0;
	}
	else
	{
		m_nextShootTimer += 1 * ennemy->m_deltatime;
	}
	ennemy->LookAt(ennemy->m_playerGm);
}
void EnnemyAction_Shoot::End(Enemy* ennemy)
{
	switch (ennemy->m_type)
	{
	case EnemyType::Crabe:
		ennemy->SetTexture(TEXTURES::CRABE_IDLE_1);
		break;
	case EnemyType::Golem:
		ennemy->SetTexture(TEXTURES::GOLEM_IDLE_1);
		break;
	}
}

void EnnemyAction_MeleeAttack::Start(Enemy* ennemy)
{
	m_nextShootTimer = 0;
	//animation
	m_atkAnim.Init(0.05f, ennemy);
	// shoot frames (switch case enemy type)
	switch (ennemy->m_type)
	{
	case EnemyType::Crabe:
	{
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_1);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_2);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_3);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_4);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_5);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_6);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_7);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_8);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_9);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_10);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_11);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_12);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_13);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_14);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_15);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_16);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_17);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_18);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_19);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_20);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_21);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_22);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_23);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_24);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_25);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_26);
		m_atkAnim.AddFrame(TEXTURES::CRABE_ATTACK_27);
	}
	break;
	case EnemyType::Golem:
	{
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_1);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_2);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_3);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_4);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_5);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_6);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_7);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_8);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_9);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_10);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_11);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_12);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_13);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_14);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_15);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_16);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_17);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_18);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_19);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_20);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_21);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_22);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_23);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_24);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_25);
		m_atkAnim.AddFrame(TEXTURES::GOLEM_ATTACK_26);
	}
	break;
	}
}
void EnnemyAction_MeleeAttack::Update(Enemy* ennemy)
{
	m_atkAnim.AnimationSequence(ennemy->GetDeltatime());
	//m_shootAnim.Loop(ennemy->GetDeltatime());
	if (m_nextShootTimer >= ennemy->m_reloadSpeed)
	{
		//ennemy->CreateProjectile(ennemy->GetPosition(), ennemy->m_playerGm.GetPosition(), 5.f);
		// inflictdamage
		m_nextShootTimer = 0;
	}
	else
	{
		m_nextShootTimer += 1 * ennemy->m_deltatime;
	}
	ennemy->LookAt(ennemy->m_playerGm);
}
void EnnemyAction_MeleeAttack::End(Enemy* ennemy)
{
	switch (ennemy->m_type)
	{
	case EnemyType::Crabe:
		ennemy->SetTexture(TEXTURES::CRABE_IDLE_1);
		break;
	case EnemyType::Golem:
		ennemy->SetTexture(TEXTURES::GOLEM_IDLE_1);
		break;
	}
}

void EnnemyAction_Flee::Start(Enemy* ennemy)
{
	m_moveAnim.Init(0.05f, ennemy);
	// shoot frames (switch case enemy type
	switch (ennemy->m_type)
	{
		case EnemyType::Crabe:
		{
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_14);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_13);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_12);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_11);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_10);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_9);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_8);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_7);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_6);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_5);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_4);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_3);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_2);
			m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_1);
		}
		break;
		case EnemyType::Golem:
		{
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_36);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_35);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_34);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_33);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_32);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_31);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_30);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_29);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_28);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_27);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_26);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_25);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_24);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_23);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_22);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_21);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_20);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_19);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_18);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_17);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_16);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_15);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_14);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_13);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_12);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_11);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_10);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_9);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_8);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_7);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_6);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_5);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_4);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_3);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_2);
			m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_1);
		}
		break;
	}
}
void EnnemyAction_Flee::Update(Enemy* ennemy)
{
	m_moveAnim.AnimationSequence(ennemy->GetDeltatime());
	ennemy->LookAt(ennemy->m_playerGm);
	ennemy->MoveBackward(ennemy->GetDeltatime() * 8);
}
void EnnemyAction_Flee::End(Enemy* ennemy)
{
	switch (ennemy->m_type)
	{
	case EnemyType::Crabe:
		ennemy->SetTexture(TEXTURES::CRABE_IDLE_1);
		break;
	case EnemyType::Golem:
		ennemy->SetTexture(TEXTURES::GOLEM_IDLE_1);
		break;
	}
}

void EnnemyAction_Roam::Start(Enemy* ennemy)
{
	m_maxX = ennemy->GetPosition().x + 100;
	m_minX = ennemy->GetPosition().x - 100;
	m_maxZ = ennemy->GetPosition().z + 100;
	m_minZ = ennemy->GetPosition().z - 100;
	SetNextLocation(ennemy);
	targetX = false;
	targetZ = false;

	m_moveAnim.Init(0.05f, ennemy);
	// move frames (switch case enemy type)
	switch (ennemy->m_type)
	{
	case EnemyType::Crabe:
	{
		m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_1);
		m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_2);
		m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_3);
		m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_4);
		m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_5);
		m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_6);
		m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_7);
		m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_8);
		m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_9);
		m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_10);
		m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_11);
		m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_12);
		m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_13);
		m_moveAnim.AddFrame(TEXTURES::CRABE_WALK_14);

	}
	break;
	case EnemyType::Golem:
	{
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_1);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_2);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_3);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_4);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_5);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_6);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_7);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_8);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_9);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_10);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_11);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_12);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_13);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_14);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_15);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_16);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_17);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_18);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_19);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_20);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_21);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_22);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_23);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_24);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_25);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_26);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_27);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_28);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_29);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_30);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_31);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_32);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_33);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_34);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_35);
		m_moveAnim.AddFrame(TEXTURES::GOLEM_WALK_36);
	}
	break;
	}
}
void EnnemyAction_Roam::Update(Enemy* ennemy)
{
	ennemy->LookAt(ennemy->m_playerGm);

	if (!targetX || !targetZ)
	{
		m_moveAnim.AnimationSequence(ennemy->GetDeltatime());

		if (ennemy->GetPosition().x < m_nextPosition.x)
		{
			ennemy->GetPosition().x += ennemy->GetDeltatime() * ennemy->m_moveSpeed;

			if (ennemy->GetPosition().x >= m_nextPosition.x)
			{
				SetNextLocation(ennemy);
				targetX = true;
			}
		}
		else if (ennemy->GetPosition().x > m_nextPosition.x)
		{
			ennemy->GetPosition().x -= ennemy->GetDeltatime() * ennemy->m_moveSpeed;

			if (ennemy->GetPosition().x <= m_nextPosition.x)
			{
				SetNextLocation(ennemy);
				targetX = true;
			}
		}
		if (ennemy->GetPosition().z < m_nextPosition.z)
		{
			ennemy->GetPosition().z += ennemy->GetDeltatime() * ennemy->m_moveSpeed;

			if (ennemy->GetPosition().z >= m_nextPosition.z)
			{
				SetNextLocation(ennemy);
				targetZ = true;
			}
		}
		else if (ennemy->GetPosition().z > m_nextPosition.z)
		{
			ennemy->GetPosition().z -= ennemy->GetDeltatime() * ennemy->m_moveSpeed;

			if (ennemy->GetPosition().z <= m_nextPosition.z)
			{
				SetNextLocation(ennemy);
				targetZ = true;
			}
		}

	}
}
void EnnemyAction_Roam::End(Enemy* ennemy)
{
	switch (ennemy->m_type)
	{
	case EnemyType::Crabe:
		ennemy->SetTexture(TEXTURES::CRABE_IDLE_1);
		break;
	case EnemyType::Golem:
		ennemy->SetTexture(TEXTURES::GOLEM_IDLE_1);
		break;
	}
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
	m_nextPosition = { currX + randX,ennemy->GetPosition().y,currZ + randZ };
}


