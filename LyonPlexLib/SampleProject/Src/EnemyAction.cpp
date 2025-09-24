#include "pch.h"
#include "EnemyAction.h"


void EnnemyAction_Idle::Start(Enemy* ennemy)
{
	m_idleAnim.Init(0.05f, ennemy);

	switch (ennemy->m_type)
	{
	case EnemyType::Crabe:
	case EnemyType::CrabeImmobile:
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
	case EnemyType::GolemBoss:
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
		case EnemyType::GolemBoss:
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
		case EnemyType::GolemBoss:
			ennemy->SetTexture(TEXTURES::GOLEM_IDLE_1);
			break;
	}
}

void EnnemyAction_Shoot::Start(Enemy* ennemy)
{
	//OutputDebugStringA("-ENEMY START SHOOTING !");
	m_nextShootTimer = ennemy->m_reloadSpeed;

	m_hasShot = false;

	//animation
	InitShootAnimation(ennemy);

}
void EnnemyAction_Shoot::Update(Enemy* ennemy)
{

	m_nextShootTimer += 1.0f * ennemy->m_deltatime;

	//Stop if the cooldown havent been finished
	if (m_nextShootTimer < ennemy->m_reloadSpeed)
	{
		ennemy->LookAt(ennemy->m_playerGm);
		return;
	}

	m_shootAnim.AnimationSequence(ennemy->GetDeltatime());

	if (m_shootAnim.GetAnimationThirdQuarterDuration() && !m_hasShot)
	{
		ennemy->CreateProjectile(ennemy->GetPosition(), ennemy->m_playerGm.GetPosition(), 5.f);
		m_hasShot = true;
	}
	if (m_shootAnim.GetAnimationHisFinished())
	{
		InitShootAnimation(ennemy);
		m_nextShootTimer = 0.0f;
		m_hasShot = false;
	}

	ennemy->LookAt(ennemy->m_playerGm);
}
void EnnemyAction_Shoot::End(Enemy* ennemy)
{
	switch (ennemy->m_type)
	{
	case EnemyType::Crabe:
	case EnemyType::CrabeImmobile:
		ennemy->SetTexture(TEXTURES::CRABE_IDLE_1);
		break;
	case EnemyType::Golem:
	case EnemyType::GolemBoss:
		ennemy->SetTexture(TEXTURES::GOLEM_IDLE_1);
		break;
	}
}

void EnnemyAction_Shoot::InitShootAnimation(Enemy* ennemy)
{
	m_shootAnim.Init(0.05f, ennemy);

	switch (ennemy->m_type)
	{
	case EnemyType::Crabe:
	case EnemyType::CrabeImmobile:
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
		break;

	case EnemyType::Golem:
	case EnemyType::GolemBoss:
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
	case EnemyType::GolemBoss:
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
	case EnemyType::GolemBoss:
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
	// keep looking at player
	ennemy->LookAt(ennemy->m_playerGm);

	// animation move
	m_moveAnim.AnimationSequence(ennemy->GetDeltatime());

	// position courante
	XMFLOAT3 pos = ennemy->m_spawnPos;

	// vecteur direction vers la cible (XZ)
	float dx = m_nextPosition.x - pos.x;
	float dz = m_nextPosition.z - pos.z;

	// distance 2D au carre
	float dist2 = dx * dx + dz * dz;

	// epsilon pour considerer qu'on est arrive
	const float arriveEpsilon = 0.05f;

	if (dist2 <= arriveEpsilon * arriveEpsilon)
	{
		// cible atteinte -> calcule la suivante
		SetNextLocation(ennemy);
		return;
	}

	// distance reelle
	float dist = sqrtf(dist2);

	// deplacement pour cette frame
	float move = ennemy->m_moveSpeed * ennemy->GetDeltatime();

	// si on dépasse la cible, on snap dessus et demande la suivante
	if (move >= dist)
	{
		pos.x = m_nextPosition.x;
		pos.z = m_nextPosition.z;
		ennemy->SetPosition(pos);
		SetNextLocation(ennemy);
		return;
	}

	// sinon avance dans la direction
	float invDist = 1.0f / dist;
	float nx = dx * invDist;
	float nz = dz * invDist;

	pos.x += nx * move;
	pos.z += nz * move;

	ennemy->SetPosition(pos);
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
	// zone max roam
	const int LOCAL_MAX = 20;

	float currX = ennemy->GetPosition().x;
	float currZ = ennemy->GetPosition().z;

	// offset random
	int randX = (std::rand() % (LOCAL_MAX * 2 + 1)) - LOCAL_MAX;
	int randZ = (std::rand() % (LOCAL_MAX * 2 + 1)) - LOCAL_MAX;

	// calcul de la candidate
	float candX = currX + (float)randX;
	float candZ = currZ + (float)randZ;

	// clamp dans les bornes globales du roam
	if (candX < m_minX) candX = m_minX;
	if (candX > m_maxX) candX = m_maxX;
	if (candZ < m_minZ) candZ = m_minZ;
	if (candZ > m_maxZ) candZ = m_maxZ;

	// if too close
	const float MIN_DIST = 1.0f;
	if (fabsf(candX - currX) < MIN_DIST && fabsf(candZ - currZ) < MIN_DIST)
	{
		// retry
		if (std::rand() % 2 == 0) candX = std::clamp(currX + (float)((std::rand() % 2 ? 1 : -1) * LOCAL_MAX), m_minX, m_maxX);
		else candZ = std::clamp(currZ + (float)((std::rand() % 2 ? 1 : -1) * LOCAL_MAX), m_minZ, m_maxZ);
	}

	m_nextPosition = { candX, ennemy->GetPosition().y, candZ };
}


