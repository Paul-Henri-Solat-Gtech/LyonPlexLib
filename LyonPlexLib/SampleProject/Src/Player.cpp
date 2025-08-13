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
	}


	// Base State
	m_stateMachine.SetState(State::Idle);
}

void Player::Init(ECSManager* ecsManager, GameManager* gameManager, Scene* scene, GameObject& cameraGO)
{
	//m_playerGameObject = gameObject;

	InitGameObj(ecsManager, scene);
	//mp_scene->CreateGameObject("player");
	SetScale({ 1, 3, 1 });
	XMFLOAT3 POSITION_CHAMPS = { 325, -2, 50 };
	XMFLOAT3 pos(POSITION_CHAMPS.x + 0, POSITION_CHAMPS.y + 15, POSITION_CHAMPS.z + 0);
	SetPosition(pos);

	mp_gameManager = gameManager;
	mp_scene = scene;
	mp_cameraGO = &cameraGO;
	m_moveSpeed = m_walkSpeed;
	m_attackFinished = true;
	m_slashAttackNb = 1;
	m_deltatime = 0;
	m_hp = 6;
	AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ GetScale().x / 2, GetScale().y / 2, GetScale().z / 2 })));

	AddComponent<Tag_Player>(new Tag_Player());

	m_moveSpeed = m_walkSpeed;

	// sounds
	mp_gameManager->GetSoundManager()->CreateSound("swordSlash1", L"../LyonPlexLib/Ressources/swordSlash1.wav");

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


	EventBus::instance().subscribe<CollisionEvent>(
		[&](CollisionEvent::Payload const& p) {
			Entity playerE = p.a, otherE = p.b;
			// permute pour que playerE soit vraiment le joueur
			if (otherE.id == GetEntity().id) {
				playerE = p.b; otherE = p.a;
			}
			// si aucun des deux nest le joueur, on sort
			if (playerE.id != GetEntity().id) return;
			
			auto tag = mp_scene->GetGameObjectByID(otherE).GetTag();
			GameObject& otherGO = mp_scene->GetGameObjectByID(otherE);

			

		switch (tag)
		{
		case TAG_Floor:
		case TAG_Environment:
		{
		}
		case TAG_Projectile: 
		{
			if (m_hp > 0)
			{
				m_hp--;
				HpUpdate();
				OutputDebugStringA("\n -1hp aie \n");
				mp_scene->DestroyGameObject(otherGO);
			}
			else
			{
			}
			case TAG_Projectile:
			{
				//COLLISION Proj and player

				if (m_hp > 0)
				{
					m_hp--;
					OutputDebugStringA("\n -1hp \n");
				}
				else
				{
					OutputDebugStringA("\n Player is already dead ! \n");
				}

			}
			default:
			{
				break;
			}
			}

			//m_objectsCollidingWithPlayer.push_back(otherE);
			m_hasCollided = true;
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

void Player::OnUdpdate(float deltatime)
{
	m_stateMachine.Update();
	m_deltatime = deltatime;
	Movement();
	ApplyMovementAndCollisions(deltatime);
}

void Player::ApplyMovementAndCollisions(float dt)
{
	auto& tP = *GetComponent<TransformComponent>();
	auto& cP = *GetComponent<CollisionComponent>();
	auto& aabb = std::get<AABBCollider>(cP.shape);

	//m_isOnGround ? OutputDebugStringA("\n PLAYER ON GROUND\n") : OutputDebugStringA("\n -- GROUND ON NOT PLAYER -- \n");

	// A) BROAD PHASE COLLISION DETECTION
	std::vector<Entity> candidates;
	{
		float margin = m_moveSpeed * dt + 0.1f;

		// 1) r�cup�re center et radius du joueur
		XMFLOAT3 center = tP.position; float rPlayer = cP.BoundingSphereRadius();

		// 2) pour chaque entit�E
		ComponentMask mask = (1ULL << CollisionComponent::StaticTypeID) | (1ULL << TransformComponent::StaticTypeID);
		mp_scene->GetEcsManager()->ForEach(mask, [&](Entity e)
			{
				if (e.id == GetEntity().id) return;

				auto& otherT = *mp_scene->GetGameObjectByID(e).GetComponent<TransformComponent>();
				auto& otherC = *mp_scene->GetGameObjectByID(e).GetComponent<CollisionComponent>();

				//float rOther = otherC.GetBoundingSphereRadius();
				float rOther = otherC.BoundingSphereRadius();

				float dist2 = Utils::sqr(otherT.position.x - center.x)
					+ Utils::sqr(otherT.position.y - center.y)
					+ Utils::sqr(otherT.position.z - center.z);

				if (dist2 <= Utils::sqr(rPlayer + rOther + margin))
				{
					candidates.push_back(e);
				}
			});
	}

	// D�placement total voulu sur ce frame
	XMVECTOR totalDisp = XMLoadFloat3(&m_velocity) * dt;

	// fraction restante de movement [0..1]
	float remaining = 1.0f;

	// 4) Pour chaque candidate :
	for (auto& e : candidates) {
		auto& oc = *mp_scene->GetGameObjectByID(e).GetComponent<CollisionComponent>();
		auto& ot = *mp_scene->GetGameObjectByID(e).GetComponent<TransformComponent>();
		XMVECTOR mtv = XMVectorZero();

		bool hit = false;
		XMFLOAT3 pa{ tP.position.x, tP.position.y, tP.position.z };
		XMFLOAT3 pb{ ot.position.x, ot.position.y, ot.position.z };


		if (oc.shapeType == ColliderType::AABB) {
			/*mtv = Utils::ResolveAABBCollision(
				tP,
				ot);*/
			hit = AabbVsAabb(pa, std::get<AABBCollider>(cP.shape), pb, std::get<AABBCollider>(oc.shape));
			if (hit)
			{
				mtv = Utils::ResolveAabbAabbCollider(
					tP.position, aabb,
					ot.position, std::get<AABBCollider>(oc.shape));
			}
		}
		else { // OBB vs AABB
			std::get<OBBCollider>(oc.shape).orientation = ot.rotation;
			hit = ObbVsAabb(pa, std::get<AABBCollider>(cP.shape), pb, std::get<OBBCollider>(oc.shape));
			if (hit)
			{
				mtv = Utils::ResolveAabbObbCollision(
					tP.position, aabb,
					ot.position, std::get<OBBCollider>(oc.shape));
			}
		}

		if (!XMVector3Equal(mtv, XMVectorZero())) {
			// pour le sol et environnement on ne bouge que le joueur
			if (mp_scene->GetGameObjectByID(e).GetTag() == TAG_Floor || mp_scene->GetGameObjectByID(e).GetTag() == TAG_Environment) {
				XMVECTOR v = XMLoadFloat3(&tP.position);
				v = XMVectorSubtract(v, mtv);
				XMStoreFloat3(&tP.position, v);
				tP.dirty = true;
				lastPushNormal = XMVector3Normalize(mtv);
			}
			else {
				// deux objets se repoussent �Emoiti�E
				XMVECTOR half = XMVectorScale(mtv, 0.5f);
				XMVECTOR vp = XMLoadFloat3(&tP.position) - half;
				XMVECTOR vo = XMLoadFloat3(&ot.position) + half;
				XMStoreFloat3(&tP.position, vp);
				XMStoreFloat3(&ot.position, vo);
				tP.dirty = ot.dirty = true;
				lastPushNormal = XMVector3Normalize(half);
			}
		}
	}

	XMFLOAT3 currentPos = tP.position;

	const float skinWidth = 0.01f;
	AABBCollider mover = aabb;
	mover.halfSize.x = (((0.0f) > (mover.halfSize.x - skinWidth)) ? (0.0f) : (mover.halfSize.x - skinWidth));
	mover.halfSize.y = (((0.0f) > (mover.halfSize.y - skinWidth)) ? (0.0f) : (mover.halfSize.y - skinWidth));
	mover.halfSize.z = (((0.0f) > (mover.halfSize.z - skinWidth)) ? (0.0f) : (mover.halfSize.z - skinWidth));

	// 3) Sweep & slide en 3 it�rations max
	for (int iter = 0; iter < 3 && remaining > 1e-3f; ++iter) {
		// portion courante du d�placement
		XMVECTOR dispCurr = totalDisp * remaining;
		XMFLOAT3 dCurr; XMStoreFloat3(&dCurr, dispCurr);

		// recherche du premier impact
		float tMin = 1.0f;
		XMVECTOR hitN = XMVectorZero();
		for (auto& e : candidates) {
			auto& oc = *mp_scene->GetGameObjectByID(e).GetComponent<CollisionComponent>();
			auto& ot = *mp_scene->GetGameObjectByID(e).GetComponent<TransformComponent>();
			float t;
			XMVECTOR n;
			if (oc.shapeType == ColliderType::AABB) {
				t = Utils::SweepAabbVsAabb(currentPos, dCurr, mover,
					ot, std::get<AABBCollider>(oc.shape), n);
			}
			else {
				t = Utils::SweepAabbVsObb(currentPos, dCurr, mover,
					ot, std::get<OBBCollider>(oc.shape), n);
			}
			if (t < tMin) {
				tMin = t;
				hitN = n;
			}
		}

		XMFLOAT3 debugVar; XMStoreFloat3(&debugVar, hitN);
		//std::string a = std::to_string(tMin);
		//std::string b = std::to_string(debugVar.x);
		//std::string c = std::to_string(debugVar.y);
		//std::string d = std::to_string(debugVar.z);
		//Utils::log("\n tMin = " + a + "\n hitN : x = " + b + ", y = " + c + ", z = " + d + "\n");


		// avancer jusqu'au contact (ou tout le chemin si tMin == 1)
		currentPos.x += dCurr.x * tMin;
		currentPos.y += dCurr.y * tMin;
		currentPos.z += dCurr.z * tMin;

		if (tMin < 1.0f) {
			currentPos.x += debugVar.x * skinWidth;
			currentPos.y += debugVar.y * skinWidth;
			currentPos.z += debugVar.z * skinWidth;
		}

		// pas d�impact ? on a fini
		if (tMin >= 1.0f) break;

		// calcule la glisse sur la face touch�e
		XMVECTOR rem = totalDisp * remaining * (1.0f - tMin);
		XMVECTOR slide = rem - hitN * XMVectorGetX(XMVector3Dot(rem, hitN));

		// met �Ejour la fraction restante et totalDisp pour la prochaine it�ration
		remaining *= (1.0f - tMin);
		totalDisp = slide;
	}

	// Si le mouvement bloque
	{
		bool moved = !XMVector3Equal(XMLoadFloat3(&tP.position), XMLoadFloat3(&currentPos));

		//  if (player tried to move but stayed in place) ? incr�mente stuckFrames
		if ((m_velocity.x != 0 || m_velocity.z != 0) && !moved) {
			stuckFrames++;
		}
		else {
			stuckFrames = 0;
		}

		// si bloqu�Etrop longtemps ? nudge
		if (stuckFrames >= 3) {
			// pousse d�un petit epsilon le long de lastPushNormal
			XMVECTOR n = lastPushNormal;
			XMVECTOR nudge = XMVectorScale(n, 0.05f);  // 5 cm
			XMStoreFloat3(&currentPos, XMLoadFloat3(&currentPos) + nudge);
			stuckFrames = 0;
		}
	}


	// 4) Applique la nouvelle position
	SetPosition(currentPos);


	// 5) Ground check
	// Origine du rayon = center.xz + (pos.y - halfHeight - ?)
	//XMVECTOR origin = XMVectorSet(
	//	tP.position.x,
	//	tP.position.y - aabb.halfSize.y + 1e-3f,
	//	tP.position.z,
	//	0);
	XMVECTOR dir = XMVectorSet(0, -1, 0, 0);
	float maxDist = 0.3;  // tol�rance de peau
	//float maxDist = 0.2f;  // tol�rance de peau

	bool onGround = false;
	for (auto& e : candidates) {
		auto& oc = *mp_scene->GetGameObjectByID(e).GetComponent<CollisionComponent>();
		auto& ot = *mp_scene->GetGameObjectByID(e).GetComponent<TransformComponent>();

		bool hit = false;
		if (oc.shapeType == ColliderType::AABB) {
			// slab?test Y only
			float minY = ot.position.y - std::get<AABBCollider>(oc.shape).halfSize.y;
			if (tP.position.y - aabb.halfSize.y >= minY &&
				tP.position.y - aabb.halfSize.y - maxDist <= minY) {
				hit = true;
			}
		}
		else {
			// IsStandingOnOBB (ray in local space)
			hit = Utils::IsStandingOnOBB(
				tP, aabb,
				ot, std::get<OBBCollider>(oc.shape),
				maxDist, 45.0f);
		}
		if (hit) {
			onGround = true;
			break;
		}
	}
	m_isOnGround = onGround;
	if (m_isOnGround) m_velocity.y = 0;


}

void Player::Movement()
{
	// G�re le sprint
	if (InputManager::GetKeyIsPressed(VK_SHIFT))
	{
		SetMoveSpeed(GetRunSpeed());
	}
	else
	{
		SetMoveSpeed(GetWalkSpeed());
	}
	// 1) R�cup�re la rotation de la cam�ra
	XMFLOAT4 camQuatF = mp_cameraGO->GetRotation();
	XMVECTOR camQuat = XMLoadFloat4(&camQuatF);
	XMMATRIX rotMat = XMMatrixRotationQuaternion(camQuat);

	// 2) Construit forward & right **dans le plan XZ**
	XMVECTOR forward = XMVector3TransformNormal(XMVectorSet(0, 0, 1, 0), rotMat);
	forward = XMVectorSetY(forward, 0);
	forward = XMVector3Normalize(forward);

	XMVECTOR right = XMVector3Normalize(XMVector3Cross(XMVectorSet(0, 1, 0, 0), forward));

	// 3) Calcule la direction de d�placement horizontale selon l�input
	XMVECTOR moveDir = XMVectorZero();
	if (InputManager::GetKeyIsPressed('Z')) moveDir += forward;
	if (InputManager::GetKeyIsPressed('S')) moveDir -= forward;
	if (InputManager::GetKeyIsPressed('D')) moveDir += right;
	if (InputManager::GetKeyIsPressed('Q')) moveDir -= right;

	// 4) Normalise (pour ne pas acc�l�rer dans les diagonales)
	if (!XMVector3Equal(moveDir, XMVectorZero())) {
		moveDir = XMVector3Normalize(moveDir);
	}

	// 5) �crit la vitesse horizontale dans m_velocity.x/z
	//    (on garde m_velocity.y intact pour la gravit�Ejump)
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

bool ObbVsAabb(XMFLOAT3 paabb, AABBCollider a,XMFLOAT3 pobb, OBBCollider b)
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

XMFLOAT3 GetWorldForwardFromGO(GameObject* go)
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
	// source camera si dispo sinon fallback player
	GameObject* cam = mp_cameraGO ? mp_cameraGO : &m_playerGameObject;

	// forward monde issu de la camera (utilise ton helper existant GetWorldForwardFromGO)
	XMFLOAT3 camFwd = GetWorldForwardFromGO(cam);

	// position joueur (world) - spawn depuis la poitrine du joueur plutôt que la cam
	XMFLOAT3 playerPos = m_playerGameObject.GetPosition();

	// ajuster la hauteur du spawn (à régler selon ton player)
	const float chestHeight = 1.3f; // essayer 1.0..1.6
	XMFLOAT3 start = { playerPos.x, playerPos.y + chestHeight, playerPos.z };

	// avance le start d'une distance devant le joueur selon la direction de la caméra
	const float muzzleOffset = 0.6f; // augmente si le projectile spawn dans le joueur
	start.x += camFwd.x * muzzleOffset;
	start.y += camFwd.y * muzzleOffset;
	start.z += camFwd.z * muzzleOffset;

	// target lointain sur la même direction
	const float range = 1000.0f;
	XMFLOAT3 target = {
		start.x + camFwd.x * range,
		start.y + camFwd.y * range,
		start.z + camFwd.z * range
	};

	// debug rapide : affiche start/target & forward
	{
		char buf[256];
		sprintf_s(buf, "CreateProjectile start=(%.2f,%.2f,%.2f) target=(%.2f,%.2f,%.2f) fwd=(%.3f,%.3f,%.3f)\n",
			start.x, start.y, start.z, target.x, target.y, target.z, camFwd.x, camFwd.y, camFwd.z);
		OutputDebugStringA(buf);
	}

	// crée le projectile (tu utilises déjà cette signature)
	mp_scene->CreateGameObject<Projectile>(mp_scene, start, target);

	// --- Optionnel debugging : si invisible, override temporairement le mesh/texture ---
	// si ton CreateGameObject renvoie une référence/pointer, tu peux faire :
	// auto* p = mp_scene->CreateGameObject<Projectile>(mp_scene, start, target);
	// if (p) { p->SetMesh(MESHES::LOCAL_SPHERE); p->SetTexture(TEXTURES::LASER); p->SetOwnerEntity(m_playerGameObject.GetEntity()); }
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
	m_gameOver.SetTexture(TEXTURES::gameOver);
	m_gameOver.SetPosition({ (float)renderWidth / 2, (float)renderHeight / 2, 0 });
	m_gameOver.SetScale({ (float)renderWidth * 0.4f, (float)renderHeight * 0.2f, 0 });
	m_gameOver.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);
}

