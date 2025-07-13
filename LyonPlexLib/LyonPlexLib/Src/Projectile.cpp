#include "pch.h"
#include "Projectile.h"

#include "ProjectileAction.h"
#include "ProjectileCondition.h"

Projectile::Projectile() : m_stateMachine(this, State::Count)
{
	// --- IDLE ---
	{
		auto* sIdle = m_stateMachine.CreateBehaviour(State::Idle);
		sIdle->AddAction(new ProjectileAction_Idle());
		//-> MOVE TRANSITION
		{
			auto transition = sIdle->CreateTransition(State::Move);
			auto condition = transition->AddCondition<ProjectileCondition_ProjectileIsNotColliding>();
			//transition->AddCondition<PlayerCondition_IsAttacking>();
		}
	}

	// --- MOVE ---
	{
		auto* sMove = m_stateMachine.CreateBehaviour(State::Move);
		sMove->AddAction(new ProjectileAction_Move());
		//-> IDLE TRANSITION
		{
			auto transition = sMove->CreateTransition(State::Collide);
			auto condition = transition->AddCondition<ProjectileCondition_ProjectileIsColliding>();
			//auto condition = transition->AddCondition<ProjectileCondition_PlayerIsNotNear>();
		}
	}
	// --- COLLIDE ---
	{
		auto* sIdle = m_stateMachine.CreateBehaviour(State::Collide);
		sIdle->AddAction(new ProjectileAction_Collide());
		//-> MOVE TRANSITION
		{
			auto transition = sIdle->CreateTransition(State::Idle);
			auto condition = transition->AddCondition<ProjectileCondition_ProjectileIsColliding>();
			//auto condition = transition->AddCondition<ProjectileCondition_ProjectileIsColliding>();
			//transition->AddCondition<PlayerCondition_IsAttacking>();
		}
	}

	// Base State
	m_stateMachine.SetState(State::Idle);
}

void Projectile::Init(GameObject gameObjectProjectile, GameObject gameObjectPlayer, GameManager* gameManager)
{
	m_projectileGameObject = gameObjectProjectile;
	m_playerGameObject = gameObjectPlayer;

	mp_gameManager = gameManager;
	m_deltatime = 0;

	m_moveSpeed = 2.f;

	// sounds
	//mp_gameManager->GetSoundManager()->CreateSound("swordSlash1", L"../LyonPlexLib/Ressources/swordSlash1.wav");

	EventBus::instance().subscribe<CollisionEvent>([&](CollisionEvent::Payload const& p) {
		// si c est notre joueur qui entre en collision
		if (p.a.id == m_projectileGameObject.GetEntity().id || p.b.id == m_projectileGameObject.GetEntity().id) {
			// on change directement detat
			m_hasCollided = true;
		}
		});

	OutputDebugStringA("\nINIT PLAYER REUSSI !\n");


}

const char* Projectile::GetStateName(State state) const
{
	switch (state)
	{
	case Idle: return "Idle";
	case Move: return "Move";
	default: return "Unknown";
	}
}

const char* Projectile::GetCurrentStateName() const
{
	int state = m_stateMachine.GetCurrentState();
	return GetStateName(static_cast<State>(state));
}

void Projectile::OnUdpdate(float deltatime)
{
	m_stateMachine.Update();
	m_deltatime = deltatime;


	//if (m_hasCollided)
	//{
	//	OutputDebugStringA("\nPLAYER COLLIDINGGIGIGIGIGIGIIGIGGIGI !\n");
	//}

}