#include "pch.h"
#include "Ennemy.h"
#include "EnemyAction.h"
#include "EnemyCondition.h"

Ennemy::Ennemy() : m_stateMachine(this, State::Count)
{
	// --- IDLE ---
	{
		auto* sIdle = m_stateMachine.CreateBehaviour(State::Idle);
		sIdle->AddAction(new EnnemyAction_Idle());
		//-> MOVE TRANSITION
		{
			auto transition = sIdle->CreateTransition(State::Move);
			auto condition = transition->AddCondition<EnnemyCondition_PlayerIsNear>();
			//transition->AddCondition<PlayerCondition_IsAttacking>();
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
	}

	// Base State
	m_stateMachine.SetState(State::Idle);
}

void Ennemy::Init(GameObject gameObjectEnemy, GameObject gameObjectPlayer, GameManager* gameManager)
{
	m_ennemyGm = gameObjectEnemy;
	m_playerGm = gameObjectPlayer;

	mp_gameManager = gameManager;
	m_deltatime = 0;

	m_moveSpeed = 2.f;

	// sounds
	//mp_gameManager->GetSoundManager()->CreateSound("swordSlash1", L"../LyonPlexLib/Ressources/swordSlash1.wav");

	//EventBus::instance().subscribe<CollisionEvent>([&](CollisionEvent::Payload const& p) {
	//	// si c�est notre joueur qui est entr� en collision
	//	if (p.a.id == m_playerGameObject.GetEntity()->id || p.b.id == m_playerGameObject.GetEntity()->id) {
	//		// on change directement d�etat
	//		m_hasCollided = true;
	//	}
	//	});

	OutputDebugStringA("\nINIT PLAYER REUSSI !\n");

	//AnimationManager newAnim;

	//m_testAnimation.Init(2.f, &m_playerArm);
	//m_testAnimation.AddFrame(TEXTURES::bras);
	//m_testAnimation.AddFrame(TEXTURES::test);
	//m_testAnimation.AddFrame(TEXTURES::tex0);

}

const char* Ennemy::GetStateName(State state) const
{
	switch (state)
	{
	case Idle: return "Idle";
	case Move: return "Move";
	default: return "Unknown";
	}
}

const char* Ennemy::GetCurrentStateName() const
{
	int state = m_stateMachine.GetCurrentState();
	return GetStateName(static_cast<State>(state));
}

void Ennemy::OnUdpdate(float deltatime)
{
	m_stateMachine.Update();
	m_deltatime = deltatime;

	//m_testAnimation.Loop(deltatime);

	//if (m_hasCollided)
	//{
	//	OutputDebugStringA("\nPLAYER COLLIDINGGIGIGIGIGIGIIGIGGIGI !\n");
	//}

}