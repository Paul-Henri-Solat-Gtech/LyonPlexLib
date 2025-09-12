#include "pch.h"
#include "Player.h"

#include "playerAction.h"
#include "playerCondition.h"
#include "EventBus.h"
#include "Utils.h"
#include <Events.h>

bool ObbVsObb(XMFLOAT3 p1, OBBCollider b1, XMFLOAT3 p2, OBBCollider b2);

bool ObbVsAabb(XMFLOAT3 paabb, AABBCollider a, XMFLOAT3 pobb, OBBCollider b);

bool AabbVsAabb(XMFLOAT3 p1, AABBCollider b1, XMFLOAT3 p2, AABBCollider b2);

static XMFLOAT3 GetForwardFromQuat(const XMFLOAT4& qf)
{
	XMVECTOR quat = XMLoadFloat4(&qf);
	XMMATRIX rotMat = XMMatrixRotationQuaternion(quat);
	XMVECTOR f = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotMat);
	f = XMVector3Normalize(f);
	XMFLOAT3 out; XMStoreFloat3(&out, f);
	return out;
}

Player::Player() : m_stateMachine(this, State::Count)
{
	// --- IDLE ---
	{
		auto* sIdle = m_stateMachine.CreateBehaviour(State::Idle);
		sIdle->AddAction(new PlayerAction_Idle());
		//-> MOVE TRANSITION
		{
			auto transition = sIdle->CreateTransition(State::Move);
			auto condition = transition->AddCondition<PlayerCondition_IsMoving>();
		}
		//-> ATTACK TRANSITION
		{
			auto transition = sIdle->CreateTransition(State::Attack);
			auto condition = transition->AddCondition<PlayerCondition_IsAttacking>();
		}
		//-> JUMP TRANSITION
		{
			auto transition = sIdle->CreateTransition(State::Jump);
			//auto condition = transition->AddCondition<PlayerCondition_IsOnGround>();
			transition->AddCondition<PlayerCondition_IsJumping>();
		}
		//-> FALL TRANSITION
		{
			auto transition = sIdle->CreateTransition(State::Fall);
			auto condition = transition->AddCondition<PlayerCondition_IsNotOnGround>();
		}
		//-> PICK UP TRANSITION
		{
			auto transition = sIdle->CreateTransition(State::PickUp);
			transition->AddCondition<PlayerCondition_IsPickingUp>();
			transition->AddCondition<PlayerCondition_IsCloseToObject>();
		}
		//-> SPECIAL ATTACK TRANSITION
		{
			auto transition = sIdle->CreateTransition(State::SpecialAttack);
			auto condition = transition->AddCondition<PlayerCondition_IsSpecialAttacking>();
		}
	}

	// --- MOVE ---
	{
		auto* sMove = m_stateMachine.CreateBehaviour(State::Move);
		sMove->AddAction(new PlayerAction_Move());
		//-> IDLE TRANSITION
		{
			auto transition = sMove->CreateTransition(State::Idle);
			auto condition = transition->AddCondition<PlayerCondition_IsNotMoving>();
		}
		//-> ATTACK TRANSITION
		{
			auto transition = sMove->CreateTransition(State::Attack);
			auto condition = transition->AddCondition<PlayerCondition_IsAttacking>();
		}
		//-> JUMP TRANSITION
		{
			auto transition = sMove->CreateTransition(State::Jump);
			auto condition = transition->AddCondition<PlayerCondition_IsOnGround>();
			transition->AddCondition<PlayerCondition_IsJumping>();
		}
		//-> FALL TRANSITION
		{
			auto transition = sMove->CreateTransition(State::Fall);
			auto condition = transition->AddCondition<PlayerCondition_IsNotOnGround>();
		}
		//-> PICK UP TRANSITION
		{
			auto transition = sMove->CreateTransition(State::PickUp);
			transition->AddCondition<PlayerCondition_IsPickingUp>();
			transition->AddCondition<PlayerCondition_IsCloseToObject>();
		}
		//-> SPECIAL ATTACK TRANSITION
		{
			auto transition = sMove->CreateTransition(State::SpecialAttack);
			auto condition = transition->AddCondition<PlayerCondition_IsSpecialAttacking>();
		}
	}

	// --- JUMP ---
	{
		auto* sJump = m_stateMachine.CreateBehaviour(State::Jump);
		sJump->AddAction(new PlayerAction_Jump());
		//-> IDLE TRANSITION
		{
			auto transition = sJump->CreateTransition(State::Idle);
			//auto condition = transition->AddCondition<PlayerCondition_IsAirBorne>(); // Saut ou chute deja commencee
			transition->AddCondition<PlayerCondition_IsOnGround>(); // Contact par le dessous
			//transition->AddCondition<PlayerCondition_IsNotMoving>();
		}
		//-> PICK UP TRANSITION
		{
			auto transition = sJump->CreateTransition(State::PickUp);
			transition->AddCondition<PlayerCondition_IsPickingUp>();
			transition->AddCondition<PlayerCondition_IsCloseToObject>();
		}
		//-> FALL TRANSITION
		{
			auto transition = sJump->CreateTransition(State::Fall);
			transition->AddCondition<PlayerCondition_JumpEnd>();
		}
		//-> FALL TRANSITION
		{
			auto transition = sJump->CreateTransition(State::Jump);
			transition->AddCondition<PlayerCondition_IsJumping>();
		}
	}

	// --- FALL ---
	{
		auto* sFall = m_stateMachine.CreateBehaviour(State::Fall);
		sFall->AddAction(new PlayerAction_Fall());
		//-> IDLE TRANSITION
		{
			auto transition = sFall->CreateTransition(State::Idle);
			auto condition = transition->AddCondition<PlayerCondition_IsOnGround>();
			//transition->AddCondition<PlayerCondition_IsNotMoving>();
		}
		//-> MOVE TRANSITION
		{
			auto transition = sFall->CreateTransition(State::Move);
			auto condition = transition->AddCondition<PlayerCondition_IsMoving>();
		}
		//-> SPECIAL ATTACK TRANSITION
		{
			auto transition = sFall->CreateTransition(State::SpecialAttack);
			auto condition = transition->AddCondition<PlayerCondition_IsSpecialAttacking>();
		}
	}

	// --- Attack ---
	{
		auto* sAttack = m_stateMachine.CreateBehaviour(State::Attack);
		sAttack->AddAction(new PlayerAction_Attack());
		//-> IDLE TRANSITION
		{
			auto transition = sAttack->CreateTransition(State::Idle);
			auto condition = transition->AddCondition<PlayerCondition_IsNotMoving>();
			transition->AddCondition<PlayerCondition_AttackFinished>();
		}
		//-> MOVE TRANSITION
		{
			auto transition = sAttack->CreateTransition(State::Move);
			auto condition = transition->AddCondition<PlayerCondition_IsMoving>();
			transition->AddCondition<PlayerCondition_AttackFinished>();
		}
		//-> FALL TRANSITION
		{
			auto transition = sAttack->CreateTransition(State::Fall);
			auto condition = transition->AddCondition<PlayerCondition_IsNotOnGround>();
			transition->AddCondition<PlayerCondition_AttackFinished>();
		}
		//-> SPECIAL ATTACK TRANSITION
		{
			auto transition = sAttack->CreateTransition(State::SpecialAttack);
			auto condition = transition->AddCondition<PlayerCondition_IsSpecialAttacking>();
			transition->AddCondition<PlayerCondition_AttackFinished>();
		}
	}
	// --- Pick Up ---
	{
		auto* sPickUp = m_stateMachine.CreateBehaviour(State::PickUp);
		sPickUp->AddAction(new PlayerAction_PickUp());
		//-> IDLE TRANSITION
		{
			auto transition = sPickUp->CreateTransition(State::Idle);
			auto condition = transition->AddCondition<PlayerCondition_IsNotMoving>();
		}
		//-> MOVE TRANSITION
		{
			auto transition = sPickUp->CreateTransition(State::Move);
			auto condition = transition->AddCondition<PlayerCondition_IsMoving>();
		}
		//-> FALL TRANSITION
		{
			auto transition = sPickUp->CreateTransition(State::Fall);
			auto condition = transition->AddCondition<PlayerCondition_IsNotOnGround>();
		}
	}
	// --- Special Attack ---
	{
		auto* sSpecialAttack = m_stateMachine.CreateBehaviour(State::SpecialAttack);
		sSpecialAttack->AddAction(new PlayerAction_SpecialAttack());
		//-> IDLE TRANSITION
		{
			auto transition = sSpecialAttack->CreateTransition(State::Idle);
			auto condition = transition->AddCondition<PlayerCondition_IsNotMoving>();
		}
		//-> MOVE TRANSITION
		{
			auto transition = sSpecialAttack->CreateTransition(State::Move);
			auto condition = transition->AddCondition<PlayerCondition_IsMoving>();
		}
		//-> FALL TRANSITION
		{
			auto transition = sSpecialAttack->CreateTransition(State::Fall);
			auto condition = transition->AddCondition<PlayerCondition_IsNotOnGround>();
		}
		//-> JUMP TRANSITION
		{
			auto transition = sSpecialAttack->CreateTransition(State::Jump);
			auto condition = transition->AddCondition<PlayerCondition_IsOnGround>();
			transition->AddCondition<PlayerCondition_IsJumping>();
		}
	}


	// Base State
	m_stateMachine.SetState(State::Idle);
}

void Player::Init(ECSManager* ecsManager, GameManager* gameManager, Scene* scene, GameObject& cameraGO)
{
	//m_playerGameObject = gameObject;

	InitPlayerGameObj(ecsManager, scene);
	//mp_scene->CreateGameObject("player");
	SetScale({ 1, 4, 1 });
	//XMFLOAT3 POSITION_CHAMPS = { 325, -2, 50 };
	//XMFLOAT3 pos(POSITION_CHAMPS.x + 0, POSITION_CHAMPS.y + 15, POSITION_CHAMPS.z + 0);
	//SetPosition(pos);
	SetPosition({ 0,60,0 });


	mp_gameManager = gameManager;
	mp_scene = scene;
	mp_cameraGO = &cameraGO;
	m_moveSpeed = m_walkSpeed;
	m_attackFinished = true;
	m_slashAttackNb = 1;
	m_deltatime = 0;
	m_hp = 6;
	AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ GetScale().x / 2, GetScale().y / 2, GetScale().z / 2 })));
	//AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ 1,1,1 })));

	AddComponent<Tag_Player>(new Tag_Player());

	m_moveSpeed = m_walkSpeed;

	// sounds
	//mp_gameManager->GetSoundManager()->CreateSound("swordSlash1", L"../LyonPlexLib/Ressources/swordSlash1.wav");
	//mp_gameManager->GetSoundManager()->CreateSound("swordSpecialSlash", L"../LyonPlexLib/Ressources/swordSpecialSlash.wav");

	// Hearts
	RECT renderZone;
	GetClientRect(mp_gameManager->GetRenderingManager().GetGraphicsDevice()->GetWindow(), &renderZone);
	UINT renderWidth = renderZone.right - renderZone.left;
	UINT renderHeight = renderZone.bottom - renderZone.top;

	mp_scene->CreateGameObject("Heart1", TYPE_2D, true);
	m_playerHeart1 = mp_scene->GetGameObjectByName("Heart1");
	m_playerHeart1.SetMesh(MESHES::LOCAL_SQUARE);
	m_playerHeart1.SetTexture(TEXTURES::heart_full);
	m_playerHeart1.SetPosition({ 120, (float)renderHeight / 6, 0 });
	m_playerHeart1.SetScale({ (float)renderWidth * 0.07f, (float)renderHeight * 0.1f, 0 });
	m_playerHeart1.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	mp_scene->CreateGameObject("Heart2", TYPE_2D, true);
	m_playerHeart2 = mp_scene->GetGameObjectByName("Heart2");
	m_playerHeart2.SetMesh(MESHES::LOCAL_SQUARE);
	m_playerHeart2.SetTexture(TEXTURES::heart_full);
	m_playerHeart2.SetPosition({ 240, (float)renderHeight / 6, 0 });
	m_playerHeart2.SetScale({ (float)renderWidth * 0.07f, (float)renderHeight * 0.1f, 0 });
	m_playerHeart2.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	mp_scene->CreateGameObject("Heart3", TYPE_2D, true);
	m_playerHeart3 = mp_scene->GetGameObjectByName("Heart3");
	m_playerHeart3.SetMesh(MESHES::LOCAL_SQUARE);
	m_playerHeart3.SetTexture(TEXTURES::heart_full);
	m_playerHeart3.SetPosition({ 360, (float)renderHeight / 6, 0 });
	m_playerHeart3.SetScale({ (float)renderWidth * 0.07f, (float)renderHeight * 0.1f, 0 });
	m_playerHeart3.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	// PlaceHolder weapon
	mp_scene->CreateGameObject("WeaponPLaceholder", TYPE_2D, true);
	m_weaponPlaceholder = mp_scene->GetGameObjectByName("WeaponPLaceholder");
	m_weaponPlaceholder.SetMesh(MESHES::LOCAL_SQUARE);
	m_weaponPlaceholder.SetTexture(TEXTURES::Weapon_placeholder);
	m_weaponPlaceholder.SetPosition({ (float)renderWidth - 100, (float)renderHeight - 80, 0 });
	m_weaponPlaceholder.SetScale({ (float)renderWidth * 0.07f, (float)renderHeight * 0.1f, 0 });
	m_weaponPlaceholder.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	// Selected Weapon
	mp_scene->CreateGameObject("WeaponSelected", TYPE_2D, true);
	m_selectedWeapon = mp_scene->GetGameObjectByName("WeaponSelected");
	m_selectedWeapon.SetMesh(MESHES::LOCAL_SQUARE);
	m_selectedWeapon.SetTexture(TEXTURES::ATTACK1_W1_1);
	m_selectedWeapon.SetPosition({ (float)renderWidth - 100, (float)renderHeight - 80, 0 });
	m_selectedWeapon.SetScale({ (float)renderWidth * 0.08f, (float)renderHeight * 0.08f, 0 });
	m_selectedWeapon.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	const uint32_t myId = GetEntity().id;
	Scene* scenePtr = mp_scene;
	Player* self = this;

	EventBus::instance().subscribe<CollisionEvent>([myId, scenePtr, self](CollisionEvent::Payload const& p)
		{
			if (p.a.id != myId && p.b.id != myId) return;
			Entity otherE = (p.a.id == myId) ? p.b : p.a;
			if (otherE.id == 0 || otherE.id == static_cast<uint32_t>(-1)) return;

			GameObject* otherGO = scenePtr->GetGameObjectByID(otherE);
			if (!otherGO) return;                 // <-- évite le crash si l'objet a déjà disparu

			auto tag = otherGO->GetTag();

			switch (tag)
			{
			case TAG_Floor:
			case TAG_Environment:
				break;
			case TAG_Projectile:
			{
				if (self && self->m_hp > 0 && !self->m_isInvincible)
				{
					self->m_hp--;
					self->HpUpdate();
					self->m_isInvincible = true;
					OutputDebugStringA("\n -1hp aie \n");
				}

				// === Knockback ===
				if (self)
				{
					self->ApplyKnockback(otherGO->GetPosition(), 8.0f, 3.0f);
				}

				scenePtr->DestroyGameObject(*otherGO);
				break;
			}
			case TAG_ProjectilePlayer:
			{
				OutputDebugStringA("\n Just me (player projectile) - ignore\n");
				break;
			}
			case TAG_HealingRock:
			{
				if (self->m_hp < 6)
				{
					OutputDebugStringA("\n  + 1hp \n");
					self->mp_gameManager->GetSoundManager()->PlaySoundPlex("heal");
					self->m_hp += 1;
					self->HpUpdate();
					scenePtr->DestroyGameObject(*otherGO);
				}
				break;
			}
			default:
				break;
			}

			if (self) self->m_hasCollided = true;
		});

	OutputDebugStringA("\nINIT PLAYER REUSSI !\n");

}

const char* Player::GetStateName(State state) const
{
	switch (state)
	{
	case Idle: return "Idle";
	case Move: return "Move";
	case Jump: return "Jump";
	case Attack: return "Attack";
	case Fall: return "Fall";
	default: return "Unknown";
	}
}

const char* Player::GetCurrentStateName() const
{
	int state = m_stateMachine.GetCurrentState();
	return GetStateName(static_cast<State>(state));
}

void Player::OnUpdate(float deltatime)
{
	m_stateMachine.Update();
	m_deltatime = deltatime;
	Movement();

	//Utils::log("\n\n -- BEFORE MOVE & COL --- \n");
	//Utils::log(" Velocity = X: " + std::to_string(m_velocity.x) + "  ; Y: " + std::to_string(m_velocity.y) + "  ; Z: " + std::to_string(m_velocity.z) + "\n");
	//Utils::log(" Position = X: " + std::to_string(GetPosition().x) + "  ; Y: " + std::to_string(GetPosition().y) + "  ; Z: " + std::to_string(GetPosition().z) + "\n");

	ApplyMovementAndCollisions(deltatime);

	/*Utils::log("\n\n -- BEFORE MOVE & COL --- \n");
	Utils::log(" Velocity = X: " + std::to_string(m_velocity.x) + "  ; Y: " + std::to_string(m_velocity.y) + "  ; Z: " + std::to_string(m_velocity.z) + "\n");
	Utils::log(" Position = X: " + std::to_string(GetPosition().x) + "  ; Y: " + std::to_string(GetPosition().y) + "  ; Z: " + std::to_string(GetPosition().z) + "\n");*/

	InvincibilityManager(deltatime);
	KnockeBackManager(deltatime);

	// weapon holder
	switch (m_currIdleMesh) 
	{
	case TEXTURES::IDLEARM_W1_1:
		m_selectedWeapon.SetTexture(TEXTURES::ATTACK1_W1_1);
		break;
	case TEXTURES::IDLEARM_W2_1:
		m_selectedWeapon.SetTexture(TEXTURES::ATTACK1_W2_1);
		break;
	}
}


XMFLOAT3 ComputeChildEntityPos(Entity childEntity, ECSManager& ecs, Scene* scene)
{
	GameObject* child = scene->GetGameObjectByID(childEntity);
	if (!child) return XMFLOAT3{ 0,0,0 };

	auto* childTr = child->GetComponent<TransformComponent>();
	if (!childTr) return XMFLOAT3{ 0,0,0 };

	XMFLOAT3 childPos = childTr->position;

	if (childTr->parent.id != UINT32_MAX)
	{
		// calcule récursivement la position du parent (évite shadowing)
		XMFLOAT3 parentPos = ComputeChildEntityPos(childTr->parent, ecs, scene);

		childPos = {
			parentPos.x + childTr->position.x,
			parentPos.y + childTr->position.y,
			parentPos.z + childTr->position.z
		};
	}

	return childPos;
}
struct WorldTransform
{
	XMFLOAT3 position;
	XMFLOAT4 rotation; // quaternion
	XMFLOAT3 scale;
};

inline bool GetWorldTransformFromMap(uint32_t entityId,
	TransformSystem& ts,
	WorldTransform& outWT)
{
	auto& map = ts.GetWorldMatrix();
	auto it = map.find(entityId);
	if (it == map.end()) return false;

	XMMATRIX wm = it->second;
	XMVECTOR s, r, t;
	if (!XMMatrixDecompose(&s, &r, &t, wm)) return false;

	XMStoreFloat3(&outWT.position, t);
	XMStoreFloat4(&outWT.rotation, r);
	XMStoreFloat3(&outWT.scale, s);
	return true;
}

void Player::ApplyMovementAndCollisions(float dt)
{
	using namespace DirectX;

	const float EPS_LEN_SQ = 1e-8f;
	const float SKIN_WIDTH = 0.01f;
	const float MAX_SLOPE_DEG = 45.0f;
	const float MAX_SLOPE_COS = cosf(XMConvertToRadians(MAX_SLOPE_DEG));
	const float FALLBACK_DIST = 0.25f;

	// Reset état
	lastPushNormal = XMVectorZero();
	float maxUpDot = -1.0f;

	// Récupération player components (identique à votre code d'avant)
	auto* pTr = GetComponent<TransformComponent>();
	auto* pCol = GetComponent<CollisionComponent>();
	if (!pTr || !pCol) return;
	auto& tP = *pTr;
	auto& cP = *pCol;
	auto playerLocalAabb = std::get<AABBCollider>(cP.shape);

	// Récupération TransformSystem (adaptation si nécessaire)
	TransformSystem* pTransformSys = nullptr;
	if (mp_scene) {
		pTransformSys = &mp_scene->GetEcsManager()->m_systemMgr.GetTransformSystem(); // <--- adaptez si votre API diffère
	}

	// helper : extraire world pos/rot/scale depuis TransformSystem->worldMatrices
	auto GetWorldFromMap = [&](uint32_t entityId, XMFLOAT3& outPos, XMFLOAT4& outRot, XMFLOAT3& outScale) -> bool {
		if (!pTransformSys) return false;
		auto& map = pTransformSys->GetWorldMatrix();
		auto it = map.find(entityId);
		if (it == map.end()) return false;
		XMVECTOR s, r, t;
		if (!XMMatrixDecompose(&s, &r, &t, it->second)) return false;
		XMStoreFloat3(&outPos, t);
		XMStoreFloat4(&outRot, r);
		XMStoreFloat3(&outScale, s);
		return true;
		};

	// --- BROADPHASE : remplir candidates (en tenant compte du scale pour bounding-sphere)
	std::vector<Entity> candidates;
	{
		float margin = m_moveSpeed * dt + 0.1f;

		// compute player world pos & scale (prefer TransformSystem but fallback to local)
		XMFLOAT3 playerWorldPos = tP.position;
		XMFLOAT3 playerWorldScale{ 1,1,1 };
		if (pTransformSys) {
			XMFLOAT4 tmpR; XMFLOAT3 tmpS;
			GetWorldFromMap(GetEntity().id, playerWorldPos, tmpR, tmpS);
			playerWorldScale = tmpS;
		}

		// player world bounding sphere radius (apply scale)
		XMVECTOR ph = XMLoadFloat3(&playerLocalAabb.halfSize);
		XMVECTOR pHalfScaled = XMVectorMultiply(ph, XMLoadFloat3(&playerWorldScale));
		float rPlayer = XMVectorGetX(XMVector3Length(pHalfScaled));

		ComponentMask mask = (1ULL << CollisionComponent::StaticTypeID) | (1ULL << TransformComponent::StaticTypeID);
		mp_scene->GetEcsManager()->ForEach(mask, [&](Entity e)
			{
				if (e.id == GetEntity().id) return;

				GameObject* otherGO = mp_scene->GetGameObjectByID(e);
				if (!otherGO) return;
				auto* otherC = otherGO->GetComponent<CollisionComponent>();
				if (!otherC) return;

				// get other world pos/scale if available
				XMFLOAT3 otherWorldPos{};
				XMFLOAT4 otherWorldRot{};
				XMFLOAT3 otherWorldScale{ 1,1,1 };
				bool haveWT = GetWorldFromMap(e.id, otherWorldPos, otherWorldRot, otherWorldScale);
				if (!haveWT) {
					otherWorldPos = ComputeChildEntityPos(e, *mp_scene->GetEcsManager(), mp_scene);
				}

				// compute bounding-sphere radius of other in world (apply scale)
				float rOther = 0.0f;
				if (otherC->shapeType == ColliderType::AABB) {
					auto b = std::get<AABBCollider>(otherC->shape);
					XMVECTOR h = XMLoadFloat3(&b.halfSize);
					XMVECTOR hScaled = XMVectorMultiply(h, XMLoadFloat3(&otherWorldScale));
					rOther = XMVectorGetX(XMVector3Length(hScaled));
				}
				else if (otherC->shapeType == ColliderType::OBB) {
					auto b = std::get<OBBCollider>(otherC->shape);
					XMVECTOR h = XMLoadFloat3(&b.halfSize);
					XMVECTOR hScaled = XMVectorMultiply(h, XMLoadFloat3(&otherWorldScale));
					rOther = XMVectorGetX(XMVector3Length(hScaled));
				}
				else { // Sphere
					auto s = std::get<SphereCollider>(otherC->shape);
					// scale radius by maximum scale component to be safe
					float maxS = (otherWorldScale.x > otherWorldScale.y)
						? (otherWorldScale.x > otherWorldScale.z ? otherWorldScale.x : otherWorldScale.z)
						: (otherWorldScale.y > otherWorldScale.z ? otherWorldScale.y : otherWorldScale.z);
					rOther = s.radius * maxS;
				}

				float dx = otherWorldPos.x - playerWorldPos.x;
				float dy = otherWorldPos.y - playerWorldPos.y;
				float dz = otherWorldPos.z - playerWorldPos.z;
				float dist2 = dx * dx + dy * dy + dz * dz;

				if (dist2 <= Utils::sqr(rPlayer + rOther + margin)) {
					candidates.push_back(e);
				}
			});
	}

	// déplacement demandé
	XMVECTOR totalDisp = XMLoadFloat3(&m_velocity) * dt;
	float remaining = 1.0f;

	// --- PASS 1 : push-out des pénétrations
	for (auto& e : candidates) {
		GameObject* otherGO = mp_scene->GetGameObjectByID(e);
		if (!otherGO) continue;
		auto* ocPtr = otherGO->GetComponent<CollisionComponent>();
		auto* otPtr = otherGO->GetComponent<TransformComponent>();
		if (!ocPtr || !otPtr) continue;
		auto& oc = *ocPtr;
		auto& otLocal = *otPtr;

		// world transform of other
		XMFLOAT3 otherWorldPos{};
		XMFLOAT4 otherWorldRot{};
		XMFLOAT3 otherWorldScale{ 1,1,1 };
		bool haveWT = GetWorldFromMap(e.id, otherWorldPos, otherWorldRot, otherWorldScale);
		if (!haveWT) {
			otherWorldPos = ComputeChildEntityPos(e, *mp_scene->GetEcsManager(), mp_scene);
			otherWorldRot = XMFLOAT4{ 0,0,0,1 };
		}

		// prepare a world-correct collider copy (do NOT modify original)
		XMFLOAT3 playerPosF = tP.position;
		XMFLOAT3 otherPosF = otherWorldPos;
		XMVECTOR mtv = XMVectorZero();

		// For consistency: convert any local AABB to OBB-in-world (so we always test ObbVsAabb)
		if (oc.shapeType == ColliderType::AABB) {
			AABBCollider otherA = std::get<AABBCollider>(oc.shape);
			// scale halfSize & offset
			//otherA.halfSize.x *= otherWorldScale.x;
			//otherA.halfSize.y *= otherWorldScale.y;
			//otherA.halfSize.z *= otherWorldScale.z;
			XMVECTOR off = XMLoadFloat3(&otherA.offset);
			off = XMVectorMultiply(off, XMLoadFloat3(&otherWorldScale));
			XMStoreFloat3(&otherA.offset, off);

			// build equivalent OBB in world orientation (AABB rotated by world rot -> OBB)
			OBBCollider obbFromA;
			obbFromA.halfSize = otherA.halfSize;
			obbFromA.offset = otherA.offset;
			obbFromA.orientation = otherWorldRot; // treat as OBB oriented by world rot

			// use ObbVsAabb (player is AABB)
			bool hit = ObbVsAabb(playerPosF, playerLocalAabb, otherPosF, obbFromA);
			if (hit) {
				mtv = Utils::ResolveAabbObbCollision(playerPosF, playerLocalAabb, otherPosF, obbFromA);
			}
		}
		else if (oc.shapeType == ColliderType::OBB) {
			OBBCollider otherO = std::get<OBBCollider>(oc.shape);
			// combine local orientation with parent/world orientation: worldRot * localOrientation
			XMVECTOR locOri = XMLoadFloat4(&otherO.orientation);
			XMVECTOR worldOri = XMLoadFloat4(&otherWorldRot);
			XMVECTOR combinedOri = XMQuaternionMultiply(worldOri, locOri); // parent * local
			XMFLOAT4 combinedOriF; XMStoreFloat4(&combinedOriF, combinedOri);

			// scale halfSize & offset
			//otherO.halfSize.x *= otherWorldScale.x;
			//otherO.halfSize.y *= otherWorldScale.y;
			//otherO.halfSize.z *= otherWorldScale.z;
			XMVECTOR off = XMLoadFloat3(&otherO.offset);
			off = XMVectorMultiply(off, XMLoadFloat3(&otherWorldScale));
			XMStoreFloat3(&otherO.offset, off);

			// set orientation to composed world orientation
			otherO.orientation = combinedOriF;

			// test
			bool hit = ObbVsAabb(playerPosF, playerLocalAabb, otherPosF, otherO);
			if (hit) {
				mtv = Utils::ResolveAabbObbCollision(playerPosF, playerLocalAabb, otherPosF, otherO);
			}
		}
		else { // Sphere vs AABB
			// if you have sphere vs aabb test, use it; else skip for now
			SphereCollider s = std::get<SphereCollider>(oc.shape);
			float maxScale = (otherWorldScale.x > otherWorldScale.y)
				? (otherWorldScale.x > otherWorldScale.z ? otherWorldScale.x : otherWorldScale.z)
				: (otherWorldScale.y > otherWorldScale.z ? otherWorldScale.y : otherWorldScale.z);
			s.radius *= maxScale;
			// approximate: if sphere collides with player AABB, you probably have helper; else skip.
			// We'll attempt broad-phase only (already did).
		}

		// If mtv is tiny -> no penetration
		if (XMVectorGetX(XMVector3LengthSq(mtv)) > EPS_LEN_SQ) {
			// ensure mtv points *away* from other (push-out). Convention: playerPos -> otherPos = dirPO
			XMVECTOR vPlayer = XMLoadFloat3(&playerPosF);
			XMVECTOR vOther = XMLoadFloat3(&otherPosF);
			XMVECTOR dirPO = XMVectorSubtract(vOther, vPlayer); // from player to other

			float dot = XMVectorGetX(XMVector3Dot(mtv, dirPO));
			if (dot > 0.0f) {
				// mtv points towards other: invert so it pushes player outwards
				mtv = XMVectorNegate(mtv);
			}

			// accumulate normals for ground-check
			XMVECTOR n = XMVector3Normalize(mtv);
			float upDot = XMVectorGetY(n);
			if (upDot > maxUpDot) {
				maxUpDot = upDot;
				lastPushNormal = n;
			}

			// apply push
			GameObject* goOther = otherGO;
			if (goOther->GetTag() == TAG_Floor || goOther->GetTag() == TAG_Environment) {
				XMVECTOR v = XMLoadFloat3(&tP.position);
				v = XMVectorAdd(v, mtv); // add mtv (mtv now points outward from other)
				XMStoreFloat3(&tP.position, v);
				tP.dirty = true;
			}
			else {
				XMVECTOR half = XMVectorScale(mtv, 0.5f);
				XMVECTOR vp = XMLoadFloat3(&tP.position) + half;
				XMVECTOR vo = XMLoadFloat3(&otLocal.position) - half; // move other oppositely
				XMStoreFloat3(&tP.position, vp);
				XMStoreFloat3(&otLocal.position, vo);
				tP.dirty = otLocal.dirty = true;
				lastPushNormal = XMVector3Normalize(half);
			}
		}
	} // end penetration pass

	// --- Prépare pour sweep & slide
	XMFLOAT3 currentPos = tP.position;
	AABBCollider mover = playerLocalAabb;
	// apply player world scale to mover.halfSize
	XMFLOAT3 playerWorldScale{ 1,1,1 };
	if (pTransformSys) {
		XMFLOAT4 tmpR; GetWorldFromMap(GetEntity().id, currentPos, tmpR, playerWorldScale); // currentPos updated with world pos
	}
	//mover.halfSize.x *= playerWorldScale.x;
	//mover.halfSize.y *= playerWorldScale.y;
	//mover.halfSize.z *= playerWorldScale.z;

	mover.halfSize.x = 0.0f > mover.halfSize.x - SKIN_WIDTH ? 0.0f : mover.halfSize.x - SKIN_WIDTH;
	mover.halfSize.y = 0.0f > mover.halfSize.y - SKIN_WIDTH ? 0.0f : mover.halfSize.y - SKIN_WIDTH;
	mover.halfSize.z = 0.0f > mover.halfSize.z - SKIN_WIDTH ? 0.0f : mover.halfSize.z - SKIN_WIDTH;

	// sweep & slide loop (uses world-correct colliders similarly)
	for (int iter = 0; iter < 3 && remaining > 1e-3f; ++iter) {
		XMVECTOR dispCurr = totalDisp * remaining;
		XMFLOAT3 dCurr; XMStoreFloat3(&dCurr, dispCurr);

		float tMin = 1.0f;
		XMVECTOR hitN = XMVectorZero();

		for (auto& e : candidates) {
			GameObject* otherGO = mp_scene->GetGameObjectByID(e);
			if (!otherGO) continue;
			auto* ocPtr = otherGO->GetComponent<CollisionComponent>();
			auto* otPtr = otherGO->GetComponent<TransformComponent>();
			if (!ocPtr || !otPtr) continue;
			auto& oc = *ocPtr;
			auto& otLocal = *otPtr;

			// world transform
			XMFLOAT3 otherWorldPos{};
			XMFLOAT4 otherWorldRot{};
			XMFLOAT3 otherWorldScale{ 1,1,1 };
			bool haveWT = GetWorldFromMap(e.id, otherWorldPos, otherWorldRot, otherWorldScale);
			if (!haveWT) otherWorldPos = ComputeChildEntityPos(e, *mp_scene->GetEcsManager(), mp_scene);

			float t = 1.0f;
			XMVECTOR n = XMVectorZero();

			if (oc.shapeType == ColliderType::AABB) {
				AABBCollider otherA = std::get<AABBCollider>(oc.shape);
				//otherA.halfSize.x *= otherWorldScale.x;
				//otherA.halfSize.y *= otherWorldScale.y;
				//otherA.halfSize.z *= otherWorldScale.z;
				XMVECTOR off = XMLoadFloat3(&otherA.offset);
				off = XMVectorMultiply(off, XMLoadFloat3(&otherWorldScale));
				XMStoreFloat3(&otherA.offset, off);

				// convert to OBB for sweep
				OBBCollider obbFromA;
				obbFromA.halfSize = otherA.halfSize;
				obbFromA.offset = otherA.offset;
				obbFromA.orientation = otherWorldRot;

				TransformComponent tmpOt = otLocal;
				tmpOt.position = otherWorldPos;
				tmpOt.rotation = otherWorldRot;

				t = Utils::SweepAabbVsObb(currentPos, dCurr, mover, tmpOt, obbFromA, n);
			}
			else if (oc.shapeType == ColliderType::OBB) {
				OBBCollider otherO = std::get<OBBCollider>(oc.shape);
				// compose world orientation
				XMVECTOR locOri = XMLoadFloat4(&otherO.orientation);
				XMVECTOR wOri = XMLoadFloat4(&otherWorldRot);
				XMVECTOR combined = XMQuaternionMultiply(wOri, locOri);
				XMFLOAT4 combinedF; XMStoreFloat4(&combinedF, combined);

				//otherO.halfSize.x *= otherWorldScale.x;
				//otherO.halfSize.y *= otherWorldScale.y;
				//otherO.halfSize.z *= otherWorldScale.z;
				XMVECTOR off = XMLoadFloat3(&otherO.offset);
				off = XMVectorMultiply(off, XMLoadFloat3(&otherWorldScale));
				XMStoreFloat3(&otherO.offset, off);
				otherO.orientation = combinedF;

				TransformComponent tmpOt = otLocal;
				tmpOt.position = otherWorldPos;
				tmpOt.rotation = combinedF;

				t = Utils::SweepAabbVsObb(currentPos, dCurr, mover, tmpOt, otherO, n);
			}
			else {
				// Sphere sweep not handled here — skip
				continue;
			}

			if (t < tMin) {
				tMin = t;
				hitN = n;
			}
		} // end candidates loop

		// advance
		XMFLOAT3 hitN_f; XMStoreFloat3(&hitN_f, hitN);
		currentPos.x += dCurr.x * tMin;
		currentPos.y += dCurr.y * tMin;
		currentPos.z += dCurr.z * tMin;

		if (tMin < 1.0f) {
			currentPos.x += hitN_f.x * SKIN_WIDTH;
			currentPos.y += hitN_f.y * SKIN_WIDTH;
			currentPos.z += hitN_f.z * SKIN_WIDTH;

			if (XMVectorGetX(XMVector3LengthSq(hitN)) > EPS_LEN_SQ) {
				XMVECTOR nn = XMVector3Normalize(hitN);
				float upDot = XMVectorGetY(nn);
				if (upDot > maxUpDot) {
					maxUpDot = upDot;
					lastPushNormal = nn;
				}
			}
		}

		if (tMin >= 1.0f) break;

		// slide
		XMVECTOR rem = totalDisp * remaining * (1.0f - tMin);
		XMVECTOR slide = rem - hitN * XMVectorGetX(XMVector3Dot(rem, hitN));
		remaining *= (1.0f - tMin);
		totalDisp = slide;
	} // end sweep&slide

	// stuck detection / nudge
	{
		XMVECTOR oldPosV = XMLoadFloat3(&tP.position);
		XMVECTOR newPosV = XMVectorSet(currentPos.x, currentPos.y, currentPos.z, 0.0f);
		bool moved = XMVectorGetX(XMVector3LengthSq(oldPosV - newPosV)) > EPS_LEN_SQ;

		if ((m_velocity.x != 0.0f || m_velocity.z != 0.0f) && !moved) stuckFrames++;
		else stuckFrames = 0;

		if (stuckFrames >= 3) {
			XMVECTOR n = lastPushNormal;
			if (XMVectorGetX(XMVector3LengthSq(n)) <= EPS_LEN_SQ) n = XMVectorSet(0, 1, 0, 0);
			XMVECTOR nudge = XMVectorScale(n, 0.05f);
			newPosV = XMVectorAdd(newPosV, nudge);
			XMStoreFloat3(&currentPos, newPosV);
			stuckFrames = 0;
		}
	}

	// apply position
	SetPosition(currentPos);


	// seuil: normale suffisamment "up" pour être considérée comme sol
	const float MIN_NORMAL_UP = cosf(XMConvertToRadians(MAX_SLOPE_DEG));
	// --- GROUND CHECK combiné et déterministe ---
	// Primary: maxUpDot (normales rencontrées)
	// Secondary: per-candidate IsStandingOnOBB / proximity (votre version qui marchait bien)
	// Tertiary: si nécessaire, vertical sweep deterministe sur ensemble élargi
	bool onGround = (maxUpDot >= MAX_SLOPE_COS);

	// 1) try primary / per-candidate fallback (votre première bonne version)
	if (!onGround) {
		XMFLOAT3 playerWorldPos = currentPos;
		XMFLOAT3 playerWorldScale{ 1,1,1 };
		if (pTransformSys) {
			XMFLOAT4 tmpR; GetWorldFromMap(GetEntity().id, playerWorldPos, tmpR, playerWorldScale);
		}

		for (auto& e : candidates) {
			GameObject* otherGO = mp_scene->GetGameObjectByID(e);
			if (!otherGO) continue;
			auto* ocPtr = otherGO->GetComponent<CollisionComponent>();
			auto* otPtr = otherGO->GetComponent<TransformComponent>();
			if (!ocPtr || !otPtr) continue;
			auto& oc = *ocPtr;
			auto& otLocal = *otPtr;

			XMFLOAT3 otherWorldPos{};
			XMFLOAT4 otherWorldRot{};
			XMFLOAT3 otherWorldScale{ 1,1,1 };
			bool haveWT = GetWorldFromMap(e.id, otherWorldPos, otherWorldRot, otherWorldScale);
			if (!haveWT) otherWorldPos = ComputeChildEntityPos(e, *mp_scene->GetEcsManager(), mp_scene);

			bool hit = false;
			if (oc.shapeType == ColliderType::AABB) {
				// quick Y slab test (as before)
				float minY = otherWorldPos.y - std::get<AABBCollider>(oc.shape).halfSize.y * otherWorldScale.y;
				float playerBottom = playerWorldPos.y - playerLocalAabb.halfSize.y * playerWorldScale.y;
				if (playerBottom >= minY && playerBottom - FALLBACK_DIST <= minY) hit = true;
			}
			else {
				// use existing IsStandingOnOBB but with temporaries set to world values
				TransformComponent tmpOther = otLocal;
				tmpOther.position = otherWorldPos;
				tmpOther.rotation = otherWorldRot;

				TransformComponent tmpPlayer = tP;
				tmpPlayer.position = playerWorldPos;

				OBBCollider obbLocal = std::get<OBBCollider>(oc.shape);
				XMVECTOR off = XMLoadFloat3(&obbLocal.offset);
				off = XMVectorMultiply(off, XMLoadFloat3(&otherWorldScale));
				XMStoreFloat3(&obbLocal.offset, off);

				// votre util existant (on suppose qu'il attend transforms en espace monde)
				hit = Utils::IsStandingOnOBB(tmpPlayer, playerLocalAabb, tmpOther, obbLocal, FALLBACK_DIST, MAX_SLOPE_DEG);
			}

			if (hit) { onGround = true; break; }
		}
	}

	// 2) If still not onGround -> deterministic vertical sweep over an enlarged, sorted candidate set
	if (!onGround) {
		// build deterministic set of ground candidates around player (wider than 'candidates')
		std::vector<Entity> groundCandidates;
		{
			const float HORIZ_SEARCH_RADIUS = 1.5f + (playerLocalAabb.halfSize.x + playerLocalAabb.halfSize.z) * 0.5f;
			ComponentMask mask = (1ULL << CollisionComponent::StaticTypeID) | (1ULL << TransformComponent::StaticTypeID);
			mp_scene->GetEcsManager()->ForEach(mask, [&](Entity e) {
				if (e.id == GetEntity().id) return;
				GameObject* otherGO = mp_scene->GetGameObjectByID(e);
				if (!otherGO) return;
				auto* otherC = otherGO->GetComponent<CollisionComponent>();
				if (!otherC) return;

				XMFLOAT3 otherWorldPos{};
				XMFLOAT4 otherWorldRot{};
				XMFLOAT3 otherWorldScale{ 1,1,1 };
				bool haveWT = GetWorldFromMap(e.id, otherWorldPos, otherWorldRot, otherWorldScale);
				if (!haveWT) otherWorldPos = ComputeChildEntityPos(e, *mp_scene->GetEcsManager(), mp_scene);

				float dx = otherWorldPos.x - currentPos.x;
				float dz = otherWorldPos.z - currentPos.z;
				float horizDist2 = dx * dx + dz * dz;

				float rOther = 0.0f;
				if (otherC->shapeType == ColliderType::AABB) {
					auto b = std::get<AABBCollider>(otherC->shape);
					XMVECTOR h = XMLoadFloat3(&b.halfSize);
					XMVECTOR hScaled = XMVectorMultiply(h, XMLoadFloat3(&otherWorldScale));
					rOther = XMVectorGetX(XMVector3Length(hScaled));
				}
				else if (otherC->shapeType == ColliderType::OBB) {
					auto b = std::get<OBBCollider>(otherC->shape);
					XMVECTOR h = XMLoadFloat3(&b.halfSize);
					XMVECTOR hScaled = XMVectorMultiply(h, XMLoadFloat3(&otherWorldScale));
					rOther = XMVectorGetX(XMVector3Length(hScaled));
				}
				else {
					auto s = std::get<SphereCollider>(otherC->shape);
					float maxS = (otherWorldScale.x > otherWorldScale.y)
						? (otherWorldScale.x > otherWorldScale.z ? otherWorldScale.x : otherWorldScale.z)
						: (otherWorldScale.y > otherWorldScale.z ? otherWorldScale.y : otherWorldScale.z);
					rOther = s.radius * maxS;
				}

				float allowed = HORIZ_SEARCH_RADIUS + rOther;
				if (horizDist2 <= allowed * allowed) groundCandidates.push_back(e);
				});
			std::sort(groundCandidates.begin(), groundCandidates.end(), [](const Entity& a, const Entity& b) { return a.id < b.id; });
		}

		// perform small vertical sweep per groundCandidate
		const float SWEEP_DOWN_DIST = 0.35f;
		AABBCollider moverDown = mover; // votre mover (already reduced by skin)
		XMFLOAT3 sweepDirF{ 0.0f, -SWEEP_DOWN_DIST, 0.0f };

		for (auto& e : groundCandidates) {
			GameObject* otherGO = mp_scene->GetGameObjectByID(e);
			if (!otherGO) continue;
			auto* ocPtr = otherGO->GetComponent<CollisionComponent>();
			auto* otPtr = otherGO->GetComponent<TransformComponent>();
			if (!ocPtr || !otPtr) continue;
			auto& oc = *ocPtr;
			auto& otLocal = *otPtr;

			XMFLOAT3 otherWorldPos{};
			XMFLOAT4 otherWorldRot{};
			XMFLOAT3 otherWorldScale{ 1,1,1 };
			bool haveWT = GetWorldFromMap(e.id, otherWorldPos, otherWorldRot, otherWorldScale);
			if (!haveWT) otherWorldPos = ComputeChildEntityPos(e, *mp_scene->GetEcsManager(), mp_scene);

			float t = 1.0f;
			XMVECTOR n = XMVectorZero();

			if (oc.shapeType == ColliderType::AABB) {
				AABBCollider otherA = std::get<AABBCollider>(oc.shape);
				//otherA.halfSize.x *= otherWorldScale.x;
				//otherA.halfSize.y *= otherWorldScale.y;
				//otherA.halfSize.z *= otherWorldScale.z;
				XMVECTOR off = XMLoadFloat3(&otherA.offset);
				off = XMVectorMultiply(off, XMLoadFloat3(&otherWorldScale));
				XMStoreFloat3(&otherA.offset, off);

				OBBCollider obbFromA;
				obbFromA.halfSize = otherA.halfSize;
				obbFromA.offset = otherA.offset;
				obbFromA.orientation = otherWorldRot;

				TransformComponent tmpOt = otLocal;
				tmpOt.position = otherWorldPos;
				tmpOt.rotation = otherWorldRot;

				t = Utils::SweepAabbVsObb(currentPos, sweepDirF, moverDown, tmpOt, obbFromA, n);
			}
			else if (oc.shapeType == ColliderType::OBB) {
				OBBCollider otherO = std::get<OBBCollider>(oc.shape);
				XMVECTOR locOri = XMLoadFloat4(&otherO.orientation);
				XMVECTOR wOri = XMLoadFloat4(&otherWorldRot);
				XMVECTOR combined = XMQuaternionMultiply(wOri, locOri);
				XMFLOAT4 combinedF; XMStoreFloat4(&combinedF, combined);

				//otherO.halfSize.x *= otherWorldScale.x;
				//otherO.halfSize.y *= otherWorldScale.y;
				//otherO.halfSize.z *= otherWorldScale.z;
				XMVECTOR off = XMLoadFloat3(&otherO.offset);
				off = XMVectorMultiply(off, XMLoadFloat3(&otherWorldScale));
				XMStoreFloat3(&otherO.offset, off);
				otherO.orientation = combinedF;

				TransformComponent tmpOt = otLocal;
				tmpOt.position = otherWorldPos;
				tmpOt.rotation = combinedF;

				t = Utils::SweepAabbVsObb(currentPos, sweepDirF, moverDown, tmpOt, otherO, n);
			}
			else if (oc.shapeType == ColliderType::Sphere) {
				SphereCollider s2 = std::get<SphereCollider>(oc.shape);
				float maxS = (otherWorldScale.x > otherWorldScale.y)
					? (otherWorldScale.x > otherWorldScale.z ? otherWorldScale.x : otherWorldScale.z)
					: (otherWorldScale.y > otherWorldScale.z ? otherWorldScale.y : otherWorldScale.z);
				float otherTopY = otherWorldPos.y + s2.radius * maxS;
				float playerBottom = currentPos.y - moverDown.halfSize.y;
				if (playerBottom >= otherTopY - 1e-3f && playerBottom <= otherTopY + SWEEP_DOWN_DIST) {
					n = XMVectorSet(0, 1, 0, 0);
					t = 0.0f;
				}
			}

			if (t < 1.0f && XMVectorGetX(XMVector3LengthSq(n)) > 1e-8f) {
				XMVECTOR nn = XMVector3Normalize(n);
				float upDot = XMVectorGetY(nn);
				if (upDot >= MIN_NORMAL_UP) {
					onGround = true;
					lastPushNormal = nn;
					break;
				}
			}
		} // end groundCandidates
	}

	// 3) coyote time counter (separate from onGround)
	if (onGround) {
		m_coyoteFrames = Player::COYOTE_MAX_FRAMES; // reset window
	}
	else if (m_coyoteFrames > 0) {
		--m_coyoteFrames;
	}

	// final assign (do not set onGround true via hysteresis here)
	m_isOnGround = onGround;

	// do not overwrite upward velocity produced by a jump this frame
	if (m_isOnGround) {
		if (m_velocity.y <= 0.0f) m_velocity.y = 0.0f;
	}


}


void Player::Movement()
{
	// Gere le sprint
	if (InputManager::GetKeyIsPressed(VK_SHIFT))
	{
		SetMoveSpeed(GetRunSpeed());
	}
	else
	{
		SetMoveSpeed(GetWalkSpeed());
	}

	// 1) Recupere la rotation de la camera
	XMFLOAT4 camQuatF = mp_cameraGO->GetRotation();
	XMVECTOR camQuat = XMLoadFloat4(&camQuatF);
	XMMATRIX rotMat = XMMatrixRotationQuaternion(camQuat);

	 //2) Construit forward & right dans le plan XZ
	XMVECTOR forward = XMVector3TransformNormal(XMVectorSet(0, 0, 1, 0), rotMat);

	// enlever la composante Y pour movement plan XZ
	forward = XMVectorSetY(forward, 0);

	// fallback: si forward quasi nul, utiliser axe Z monde
	float forwardLenSq = XMVectorGetX(XMVector3LengthSq(forward));
	if (forwardLenSq < 1e-6f) {
		forward = XMVectorSet(0, 0, 1, 0); // fallback horizontal forward
	}
	else {
		forward = XMVector3Normalize(forward);
	}

	XMVECTOR right = XMVector3Normalize(XMVector3Cross(XMVectorSet(0, 1, 0, 0), forward));

	//XMVECTOR camForward = XMVector3TransformNormal(XMVectorSet(0, 0, 1, 0), rotMat);
	//XMVECTOR forward = XMVectorSetY(camForward, 0);      // ignore Y
	//float lenSq = XMVectorGetX(XMVector3LengthSq(forward));
	//if (lenSq < 1e-6f) forward = XMVectorSet(0, 0, 1, 0); // fallback horizontal
	//else forward = XMVector3Normalize(forward);

	//XMVECTOR right = XMVector3Normalize(XMVector3Cross(XMVectorSet(0, 1, 0, 0), forward));

	// 3) Calcule la direction de deplacement horizontale selon l'input
	XMVECTOR moveDir = XMVectorZero();
	if (InputManager::GetKeyIsPressed('Z')) moveDir += forward;
	if (InputManager::GetKeyIsPressed('S')) moveDir -= forward;
	if (InputManager::GetKeyIsPressed('D')) moveDir += right;
	if (InputManager::GetKeyIsPressed('Q')) moveDir -= right;

	// 4) Normalise (pour ne pas accelerer dans les diagonales)
	if (!XMVector3Equal(moveDir, XMVectorZero())) {
		moveDir = XMVector3Normalize(moveDir);
	}

	// 5) ecrit la vitesse horizontale dans m_velocity.x/z
	XMFLOAT3 vel = m_velocity;
	float speed = GetMoveSpeed();      // sprint ou marche
	vel.x = XMVectorGetX(moveDir) * speed;
	vel.z = XMVectorGetZ(moveDir) * speed;
	m_velocity = vel;
}

bool ObbVsObb(XMFLOAT3 p1, OBBCollider b1, XMFLOAT3 p2, OBBCollider b2)
{

	// 3 axes locaux de chaque bo��e
	XMMATRIX R1 = XMMatrixRotationQuaternion(XMLoadFloat4(&b1.orientation));
	XMMATRIX R2 = XMMatrixRotationQuaternion(XMLoadFloat4(&b2.orientation));
	XMVECTOR A[3] = { R1.r[0], R1.r[1], R1.r[2] };
	XMVECTOR B[3] = { R2.r[0], R2.r[1], R2.r[2] };

	// centres en espace monde
	XMVECTOR C1 = XMLoadFloat3(&p1) +
		XMVector3Rotate(XMLoadFloat3(&b1.offset), XMLoadFloat4(&b1.orientation));
	XMVECTOR C2 = XMLoadFloat3(&p2) +
		XMVector3Rotate(XMLoadFloat3(&b2.offset), XMLoadFloat4(&b2.orientation));

	// matrice des dot products et valeurs absolues (+epsilon)
	float R_[3][3], AbsR[3][3];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			R_[i][j] = XMVectorGetX(XMVector3Dot(A[i], B[j]));
			AbsR[i][j] = std::abs(R_[i][j]) + 1e-6f;
		}
	}

	// vecteur distance projet�Esur A[]
	XMVECTOR tvec = C2 - C1;
	float t[3] = {
		XMVectorGetX(XMVector3Dot(tvec, A[0])),
		XMVectorGetX(XMVector3Dot(tvec, A[1])),
		XMVectorGetX(XMVector3Dot(tvec, A[2]))
	};

	// 1�E : axes A0, A1, A2
	for (int i = 0; i < 3; ++i) {
		float ra = (&b1.halfSize.x)[i];
		float rb = b2.halfSize.x * AbsR[i][0]
			+ b2.halfSize.y * AbsR[i][1]
			+ b2.halfSize.z * AbsR[i][2];
		if (std::abs(t[i]) > ra + rb) return false;
	}
	// 4�E : axes B0, B1, B2
	for (int j = 0; j < 3; ++j) {
		float ra = b1.halfSize.x * AbsR[0][j]
			+ b1.halfSize.y * AbsR[1][j]
			+ b1.halfSize.z * AbsR[2][j];
		float tj = std::abs(XMVectorGetX(XMVector3Dot(tvec, B[j])));
		float rb = (&b2.halfSize.x)[j];
		if (tj > ra + rb) return false;
	}
	// 7�E5 : A_i � B_j
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			float ra = (&b1.halfSize.x)[(i + 1) % 3] * AbsR[(i + 2) % 3][j]
				+ (&b1.halfSize.x)[(i + 2) % 3] * AbsR[(i + 1) % 3][j];
			float rb = (&b2.halfSize.x)[(j + 1) % 3] * AbsR[i][(j + 2) % 3]
				+ (&b2.halfSize.x)[(j + 2) % 3] * AbsR[i][(j + 1) % 3];
			float tij = std::abs(
				t[(i + 2) % 3] * R_[(i + 1) % 3][j] - t[(i + 1) % 3] * R_[(i + 2) % 3][j]
			);
			if (tij > ra + rb) return false;
		}
	}

	return true;
}

bool ObbVsAabb(XMFLOAT3 paabb, AABBCollider a, XMFLOAT3 pobb, OBBCollider b)
{
	// transformer l�AABB en OBB : orientation = identity, offset = a.offset
	OBBCollider boxA;
	boxA.halfSize = a.halfSize;
	boxA.offset = a.offset;
	boxA.orientation = { 0, 0, 0, 1 };
	// et appeler directement ObbVsObb avec centres �chang�s si besoin
	return ObbVsObb(pobb, b, paabb, boxA);
}

bool AabbVsAabb(XMFLOAT3 p1, AABBCollider b1, XMFLOAT3 p2, AABBCollider b2)
{
	return
		std::abs(p1.x + b1.offset.x - (p2.x + b2.offset.x)) <= (b1.halfSize.x + b2.halfSize.x)
		&& std::abs(p1.y + b1.offset.y - (p2.y + b2.offset.y)) <= (b1.halfSize.y + b2.halfSize.y)
		&& std::abs(p1.z + b1.offset.z - (p2.z + b2.offset.z)) <= (b1.halfSize.z + b2.halfSize.z);
}

XMFLOAT3 Player::GetWorldForwardFromGO(GameObject* go)
{
	// local forward = +Z
	XMVECTOR localForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	// recup rotation quaternion depuis le GO (XMFLOAT4)
	XMFLOAT4 qf = go->GetRotation(); // existe d'apres ton MoveForward
	XMVECTOR quat = XMLoadFloat4(&qf);

	XMVECTOR worldF = XMVector3Rotate(localForward, quat);
	worldF = XMVector3Normalize(worldF);

	XMFLOAT3 f;
	XMStoreFloat3(&f, worldF);
	return f;
}

void Player::CreateProjectile(XMFLOAT3 posStart, XMFLOAT3 posTarget, float lifeTime)
{
	if (!mp_scene) return;

	// choose source for forward: prefer camera if valid, else player
	GameObject* source = mp_cameraGO ? mp_cameraGO : this;

	XMFLOAT3 forward = GetWorldForwardFromGO(source);

	XMFLOAT3 playerPos = this->GetPosition();
	const float chestHeight = 1.3f;
	XMFLOAT3 start = { playerPos.x, playerPos.y + chestHeight, playerPos.z };

	const float muzzleOffset = 0.8f;
	start.x += forward.x * muzzleOffset;
	start.y += forward.y * muzzleOffset;
	start.z += forward.z * muzzleOffset;

	const float range = 1000.0f;
	XMFLOAT3 target = {
		start.x + forward.x * range,
		start.y + forward.y * range,
		start.z + forward.z * range
	};

	// debug (optional)
	{
		//char buf[256];
		//sprintf_s(buf, "CreateProjectile final start=(%.2f,%.2f,%.2f) target=(%.2f,%.2f,%.2f) fwd=(%.3f,%.3f,%.3f)\n",
		//	start.x, start.y, start.z, target.x, target.y, target.z, forward.x, forward.y, forward.z);
		//OutputDebugStringA(buf);
	}

	mp_scene->CreateGameObject<Projectile>(mp_scene, start, target, ProjectileType::AirSlash, lifeTime);
}

void Player::HpUpdate()
{
	switch (m_hp)
	{
	case 0:
		m_playerHeart1.SetTexture(TEXTURES::heart_empty);
		m_playerHeart2.SetTexture(TEXTURES::heart_empty);
		m_playerHeart3.SetTexture(TEXTURES::heart_empty);
		DeathManager();
		break;
	case 1:
		m_playerHeart1.SetTexture(TEXTURES::heart_demi);
		m_playerHeart2.SetTexture(TEXTURES::heart_empty);
		m_playerHeart3.SetTexture(TEXTURES::heart_empty);
		break;
	case 2:
		m_playerHeart1.SetTexture(TEXTURES::heart_full);
		m_playerHeart2.SetTexture(TEXTURES::heart_empty);
		m_playerHeart3.SetTexture(TEXTURES::heart_empty);
		break;
	case 3:
		m_playerHeart1.SetTexture(TEXTURES::heart_full);
		m_playerHeart2.SetTexture(TEXTURES::heart_demi);
		m_playerHeart3.SetTexture(TEXTURES::heart_empty);
		break;
	case 4:
		m_playerHeart1.SetTexture(TEXTURES::heart_full);
		m_playerHeart2.SetTexture(TEXTURES::heart_full);
		m_playerHeart3.SetTexture(TEXTURES::heart_empty);
		break;
	case 5:
		m_playerHeart1.SetTexture(TEXTURES::heart_full);
		m_playerHeart2.SetTexture(TEXTURES::heart_full);
		m_playerHeart3.SetTexture(TEXTURES::heart_demi);
		break;
	case 6:
		m_playerHeart1.SetTexture(TEXTURES::heart_full);
		m_playerHeart2.SetTexture(TEXTURES::heart_full);
		m_playerHeart3.SetTexture(TEXTURES::heart_full);
		break;
	default:
		break;
	}
}

void Player::DeathManager()
{
	RECT renderZone;
	GetClientRect(mp_gameManager->GetRenderingManager().GetGraphicsDevice()->GetWindow(), &renderZone);
	UINT renderWidth = renderZone.right - renderZone.left;
	UINT renderHeight = renderZone.bottom - renderZone.top;

	mp_scene->CreateGameObject("gameOver", TYPE_2D, true);
	m_gameOver = mp_scene->GetGameObjectByName("gameOver");
	m_gameOver.SetMesh(MESHES::LOCAL_SQUARE);
	m_gameOver.SetTexture(TEXTURES::LOSESCREEN);
	m_gameOver.SetPosition({ (float)renderWidth / 2, (float)renderHeight / 2, 0 });
	m_gameOver.SetScale({ (float)renderWidth * 0.4f, (float)renderHeight * 0.4f, 0 });
	m_gameOver.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);
}

void Player::InvincibilityManager(float deltatime)
{
	if (m_invicibilityCooldown > 0 && m_isInvincible)
	{
		m_invicibilityCooldown -= 1 * deltatime;
	}
	else
	{
		m_isInvincible = false;
		m_invicibilityCooldown = m_invincibilityTime;
	}
}

void Player::KnockeBackManager(float deltatime)
{
	if (!m_knockback.active) return;

	// déplacement horizontal
	XMFLOAT3 pos = GetPosition();
	pos.x += m_knockback.dir.x * m_knockback.speed * deltatime;
	pos.z += m_knockback.dir.z * m_knockback.speed * deltatime;
	SetPosition(pos);

	// réduire distance horizontale
	m_knockback.distLeft -= m_knockback.speed * deltatime;
	if (m_knockback.distLeft <= 0.0f)
		m_knockback.active = false;

}

void Player::ApplyKnockback(const XMFLOAT3& sourcePos, float strength, float upward)
{
	XMVECTOR dir = XMLoadFloat3(&GetPosition()) - XMLoadFloat3(&sourcePos);
	dir = XMVectorSetY(dir, 0);
	dir = XMVector3Normalize(dir);

	XMStoreFloat3(&m_knockback.dir, dir);
	m_knockback.speed = strength * 5.0f;   // horizontal
	m_knockback.distLeft = strength;
	m_knockback.upward = upward;           // vitesse verticale temporaire
	m_knockback.active = true;

	// Ajoute la vitesse verticale au système physique du joueur
	m_velocity.y = upward;
}
