#include "pch.h"
#include "Enemy.h"
#include "EnemyAction.h"
#include "EnemyCondition.h"


Enemy::Enemy(ECSManager* ecsManager, GameManager* gameManager, GameObject& gameObjectPlayer, Scene* scene, EnemyType type) : m_stateMachine(this, State::Count), m_deltatime(0), m_playerGm(gameObjectPlayer), m_type(type)
{
	InitGameObj(ecsManager, scene);
	Init(gameManager);
}

void Enemy::Init(GameManager* gameManager)
{
	AddComponent<Tag_Enemy>(new Tag_Enemy());
	auto enemyScale = this->GetScale();
	AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ enemyScale.x / 2, enemyScale.y / 2, enemyScale.z / 2 }))); //not colliding with terrain Or just not work

	mp_gameManager = gameManager;
	m_deltatime = 0;

	m_initialized = true;

	SetStateMachine();
	
	OutputDebugStringA("\nINIT ENNEMIE REUSSI !\n");
}

const char* Enemy::GetStateName(State state) const
{
	switch (state)
	{
	case Idle: return "Idle";
	case Move: return "Move";
	case Shoot: return "Shoot";
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

void Enemy::CreateProjectile(XMFLOAT3 posStart, XMFLOAT3 posTarget, float lifeTime)
{
	auto& newProjectile = mp_scene->CreateGameObject<Projectile>(mp_scene, GetPosition(), m_playerGm.GetPosition(), ProjectileType::Laser);
}

void Enemy::OnUdpdate(float deltatime)
{
	m_stateMachine.Update();
	m_deltatime = deltatime;

	m_distanceBetweenEnnemyPlayer.x = m_playerGm.GetPosition().x - GetPosition().x;
	m_distanceBetweenEnnemyPlayer.y = m_playerGm.GetPosition().y - GetPosition().y;
	m_distanceBetweenEnnemyPlayer.z = m_playerGm.GetPosition().z - GetPosition().z;

	CollisionManager();
}

void Enemy::CollisionManager()
{
	EventBus::instance().subscribe<CollisionEvent>([&](CollisionEvent::Payload const& p)
		{
			Entity enemyE = p.a, otherE = p.b;
			// permute pour que playerE soit vraiment le joueur
			if (otherE.id == GetEntity().id)
			{
				enemyE = p.b; otherE = p.a;
			}
			// si aucun des deux nest le joueur, on sort
			if (enemyE.id != GetEntity().id) return;

			auto tag = mp_scene->GetGameObjectByID(p.b).GetTag();
			GameObject& otherGO = mp_scene->GetGameObjectByID(otherE);

			switch (tag)
			{
			case TAG_Floor:
				break;
			case TAG_Environment:
				break;
			case TAG_ProjectilePlayer:
			{
				OutputDebugStringA("\n OUCH ! \n");
				if (m_life > 0)
				{
					mp_scene->DestroyGameObject(otherGO);
					TakeDamage();
				}
				else
				{
					OutputDebugStringA("\n Ennemy is already dead ! \n");
				}
			}
			default:
				break;
			}
		});
}

void Enemy::SetStateMachine()
{
	switch (m_type)
	{
	case EnemyType::Crabe:
	{
		// Enemy Properties >

		m_life = 3;
		m_moveSpeed = 5.f;
		m_reloadSpeed = 2.f;

		// Enemy States >

		// --- IDLE ---
		{
			auto* sIdle = m_stateMachine.CreateBehaviour(State::Idle);
			sIdle->AddAction(new EnnemyAction_Idle());
			//-> FLEE TRANSITION
			{
				auto transition = sIdle->CreateTransition(State::Flee);
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
			//-> ROAM TRANSITION
			{
				auto transition = sMove->CreateTransition(State::Roam);
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
			//-> ROAM TRANSITION
			{
				auto transition = sShoot->CreateTransition(State::Roam);
				auto condition = transition->AddCondition<EnnemyCondition_PlayerIsNotNear>();
			}
			//-> FLEE TRANSITION
			{
				auto transition = sShoot->CreateTransition(State::Flee);
				auto condition = transition->AddCondition<EnnemyCondition_PlayerIsVeryNear>();
			}
		}

		// --- FLEE ---
		{
			auto* sFlee = m_stateMachine.CreateBehaviour(State::Flee);
			sFlee->AddAction(new EnnemyAction_Flee());
			//-> SHOOT TRANSITION
			{
				auto transition = sFlee->CreateTransition(State::Shoot);
				auto condition = transition->AddCondition<EnnemyCondition_PlayerIsNear>();
			}
		}

		// --- ROAM ---
		{
			auto* sRoam = m_stateMachine.CreateBehaviour(State::Roam);
			
			sRoam->AddAction(new EnnemyAction_Roam());
			//-> SHOOT TRANSITION
			{
				auto transition = sRoam->CreateTransition(State::Shoot);
				auto condition = transition->AddCondition<EnnemyCondition_PlayerIsNear>();
			}
		}
	}
		break;
	case EnemyType::Golem:
	{
		// Enemy Properties >

		m_life = 5;
		m_moveSpeed = 1.f;
		m_reloadSpeed = 5.f;

		// Enemy States >

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
	}
		break;
	default:
	{
		// Enemy Properties >

		m_life = 3;
		m_moveSpeed = 2.f;

		// Enemy States >

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
	}
		break;
	}
	
	// Base State
	m_stateMachine.SetState(State::Idle);
}
