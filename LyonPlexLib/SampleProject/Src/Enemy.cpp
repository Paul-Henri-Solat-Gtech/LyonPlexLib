#include "pch.h"
#include "Enemy.h"
#include "EnemyAction.h"
#include "EnemyCondition.h"


Enemy::Enemy(ECSManager* ecsManager, GameManager* gameManager, GameObject& gameObjectPlayer, Scene* scene) : m_stateMachine(this, State::Count), m_deltatime(0), m_playerGm(gameObjectPlayer)
{
	InitGameObj(ecsManager, scene);
	Init(/*gameObjectPlayer,*/ gameManager);

}

void Enemy::Init(/*GameObject gameObjectPlayer,*/ GameManager* gameManager)
{
	AddComponent<Tag_Enemy>(new Tag_Enemy());

	//m_playerGm = gameObjectPlayer;

	mp_gameManager = gameManager;
	m_deltatime = 0;

	m_moveSpeed = 2.f;
	m_initialized = true;

	// --- IDLE ---
	{
		auto* sIdle = m_stateMachine.CreateBehaviour(State::Idle);
		sIdle->AddAction(new EnnemyAction_Idle());
		//-> MOVE TRANSITION
		{
			auto transition = sIdle->CreateTransition(State::Move);
			auto condition = transition->AddCondition<EnnemyCondition_PlayerIsVeryNear>();
			//transition->AddCondition<PlayerCondition_IsAttacking>();
		}
		//-> SHOOT TRANSITION
		{
			auto transition = sIdle->CreateTransition(State::Shoot);
			auto condition = transition->AddCondition<EnnemyCondition_PlayerIsNear>();
		}
	}

	// --- MOVE ---
	{
		auto* sMove = m_stateMachine.CreateBehaviour(State::Move);
		sMove->AddAction(new EnnemyAction_Move());
		//-> IDLE TRANSITION
		{
			auto transition = sMove->CreateTransition(State::Idle);
			auto condition = transition->AddCondition<EnnemyCondition_PlayerIsNotNear>();
		}
		//-> SHOOT TRANSITION
		{
			auto transition = sMove->CreateTransition(State::Shoot);
			auto condition = transition->AddCondition<EnnemyCondition_PlayerIsNear>();
		}
	}

	// --- SHOOT ---
	{
		auto* sShoot = m_stateMachine.CreateBehaviour(State::Shoot);
		sShoot->AddAction(new EnnemyAction_Shoot());
		//-> IDLE TRANSITION
		{
			auto transition = sShoot->CreateTransition(State::Idle);
			auto condition = transition->AddCondition<EnnemyCondition_PlayerIsNotNear>();
		}
		//-> MOVE TRANSITION
		{
			auto transition = sShoot->CreateTransition(State::Move);
			auto condition = transition->AddCondition<EnnemyCondition_PlayerIsVeryNear>();
		}
	}

	// Base State
	m_stateMachine.SetState(State::Idle);

	OutputDebugStringA("\nINIT PLAYER REUSSI !\n");

}

const char* Enemy::GetStateName(State state) const
{
	switch (state)
	{
	case Idle: return "Idle";
	case Move: return "Move";
	default: return "Unknown";
	}
}

const char* Enemy::GetCurrentStateName() const
{
	int state = m_stateMachine.GetCurrentState();
	return GetStateName(static_cast<State>(state));
}

void Enemy::TakeDamage()
{
	m_life--;

	if (m_life <= 0)
	{
		alive = false;
		mp_scene->DestroyGameObject(*this);
		mp_gameManager->GetSoundManager()->PlaySoundPlex("deathScream"); // need to adapt sound to frame (like adding pause)
	}
	else 
	{
		mp_gameManager->GetSoundManager()->PlaySoundPlex("HUGH"); // need to adapt sound to frame (like adding pause)
	}
}

void Enemy::OnUdpdate(float deltatime)
{
	m_stateMachine.Update();
	m_deltatime = deltatime;

	m_distanceBetweenEnnemyPlayer.x = m_playerGm.GetPosition().x - GetPosition().x;
	m_distanceBetweenEnnemyPlayer.y = m_playerGm.GetPosition().y - GetPosition().y;
	m_distanceBetweenEnnemyPlayer.z = m_playerGm.GetPosition().z - GetPosition().z;
}