#include "pch.h"
#include "Enemy.h"
#include "EnemyAction.h"
#include "EnemyCondition.h"


Enemy::Enemy(ECSManager* ecsManager, GameManager* gameManager, GameObject& gameObjectPlayer, Scene* scene, EnemyType type) : m_stateMachine(this, State::Count), m_deltatime(0), m_playerGm(gameObjectPlayer), m_type(type)
{
	InitGameObj(ecsManager, scene);
	Init(gameManager);
}

Enemy::~Enemy()
{
	//EventBus::instance().unsubscribe<CollisionEvent>(m_subId);
}

void Enemy::Init(GameManager* gameManager)
{
	AddComponent<Tag_Enemy>(new Tag_Enemy());
	SetMesh(MESHES::LOCAL_SQUARE);
	auto enemyScale = this->GetScale();
	AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ enemyScale.x / 2, enemyScale.y / 2, enemyScale.z / 2 }))); //not colliding with terrain Or just not work

	mp_gameManager = gameManager;
	m_deltatime = 0;

	m_initialized = true;

	CollisionManager();

	SetStateMachine();
	
	OutputDebugStringA("\nINIT ENNEMIE REUSSI !\n");

	mp_scene->SetEnnemyNb(mp_scene->GetEnnemyNb() + 1);
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

		if (mp_gameManager) {
			if (auto* sm = mp_gameManager->GetSoundManager()) {
				sm->PlaySoundPlex("deathScream");
			}
		}

		mp_scene->SetEnnemyNb(mp_scene->GetEnnemyNb() - 1);
		mp_scene->DestroyGameObject(*this);
	}
	else
	{
		if (mp_gameManager) {
			auto* sm = mp_gameManager->GetSoundManager();
			if (sm && sm->IsAlive()) {   // ajoute un flag m_alive
				sm->PlaySoundPlex("HUGH");
			}
		}
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

	//CollisionManager();
}

void Enemy::CollisionManager()
{
	const uint32_t myId = GetEntity().id;
	Scene* scenePtr = mp_scene;

	if (m_collisionSubscribed) return;
	m_collisionSubscribed = true;

	EventBus::instance().subscribe<CollisionEvent>([myId, scenePtr](CollisionEvent::Payload const& p)
		{
			if (p.a.id != myId && p.b.id != myId) return;

			Entity otherE = (p.a.id == myId) ? p.b : p.a;
			if (otherE.id == 0 || otherE.id == static_cast<uint32_t>(-1)) {
				OutputDebugStringA("Enemy collision: otherE id invalid -> ignore\n");
				return;
			}

			// get pointer (peut retourner nullptr si l'objet a été détruit)
			GameObject* otherGO = scenePtr->GetGameObjectByID(otherE);
			if (!otherGO) return; // évite deref null

			auto tag = otherGO->GetTag();

			if (tag == TAG_ProjectilePlayer)
			{
				// détruire le projectile (marque pour suppression)
				scenePtr->DestroyGameObject(*otherGO);

				// retrouver l'enemy de façon sûre avant d'appeler TakeDamage
				GameObject* maybeEnemyGO = scenePtr->GetGameObjectByID(Entity{ myId });
				if (!maybeEnemyGO) return;

				Enemy* enemyPtr = static_cast<Enemy*>(maybeEnemyGO);
				if (enemyPtr) enemyPtr->TakeDamage();
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
		SetTexture(TEXTURES::CRABE_WALK_1);

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
