#include "pch.h"
#include "PlayerAction.h"
#include "Utils.h"

float FPS_24 = 1 / 24;

void PlayerMovement(Player* player)
{
	// Gère le sprint
	if (InputManager::GetKeyIsPressed(VK_SHIFT))
	{
		player->SetMoveSpeed(player->GetRunSpeed());
	}
	else
	{
		player->SetMoveSpeed(player->GetWalkSpeed());
	}

	//move
	// 1) Récupère le quaternion de la caméra
	GameObject& camGO = *player->mp_cameraGO;
	XMFLOAT4 camQuatF = camGO.GetRotation();
	XMVECTOR camQuat = XMLoadFloat4(&camQuatF);
	XMMATRIX rotMat = XMMatrixRotationQuaternion(camQuat);

	// 2) Calcule forward et right dans le plan XZ
	XMVECTOR forward = XMVector3Normalize(
		XMVector3TransformNormal(
			XMVectorSet(0, 0, 1, 0),  // vecteur avant local +Z
			rotMat
		)
	);
	forward = XMVectorSetY(forward, 0); // on zappe Y pour marcher au sol
	forward = XMVector3Normalize(forward);

	XMVECTOR right = XMVector3Normalize(
		XMVector3Cross(
			XMVectorSet(0, 1, 0, 0), // Y up
			forward
		)
	);

	// 3) Compose le déplacement
	XMVECTOR move = XMVectorZero();
	if (InputManager::GetKeyIsPressed('Z')) move += forward;
	if (InputManager::GetKeyIsPressed('S')) move -= forward;
	if (InputManager::GetKeyIsPressed('D')) move += right;
	if (InputManager::GetKeyIsPressed('Q')) move -= right;

	// vertical
	//if (InputManager::GetKeyIsPressed(VK_SPACE))   move += XMVectorSet(0, 1, 0, 0);
	//if (InputManager::GetKeyIsPressed(VK_CONTROL)) move -= XMVectorSet(0, 1, 0, 0);

	// 4) Applique la vitesse et deltaTime
	if (!XMVector3Equal(move, XMVectorZero()))
	{
		move = XMVector3Normalize(move)
			* (player->GetMoveSpeed() * player->GetDeltatime());

		XMFLOAT3 pos = player->GetGameObject().GetPosition();
		XMVECTOR  p = XMLoadFloat3(&pos) + move;
		XMStoreFloat3(&pos, p);

		player->GetGameObject().SetPosition(pos);
		player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
	}

}



// IDLE (dont need to be implemented normaly with override{})
void PlayerAction_Idle::Start(Player* player)
{
	OutputDebugStringA("\n- StartIdle\n");

	// Reset des variables dynamiques (sauts, chute,...)
	player->m_jumpProgress = 0.0f;
	player->m_fallProgress = 0.0f;

	switch (player->m_currIdleMesh)
	{
	case TEXTURES::ARMS:

		m_idleAnim.Init(FPS_24, &player->GetPlayerArm());
		// idle frames
		{
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_1);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_2);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_3);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_4);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_5);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_6);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_7);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_8);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_9);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_10);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_11);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_12);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_13);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_14);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_15);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_16);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_17);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_18);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_19);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_20);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_21);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_22);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_23);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_24);
		}
		break;

	case TEXTURES::IDLEARM_W1_1:

		m_idleAnim.Init(FPS_24, &player->GetPlayerArm());
		// idle frames
		{
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_1);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_2);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_3);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_4);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_5);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_6);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_7);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_8);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_9);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_10);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_11);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_12);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_13);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_14);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_15);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_16);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_17);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_18);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W1_19);
		}
		break;

	case TEXTURES::IDLEARM_W2_1:

		m_idleAnim.Init(FPS_24, &player->GetPlayerArm());
		// idle frames
		{
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W2_1);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W2_2);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W2_3);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W2_4);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W2_5);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W2_6);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W2_7);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W2_8);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W2_9);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W2_10);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W2_11);
			m_idleAnim.AddFrame(TEXTURES::IDLEARM_W2_12);
		}
		break;

	default:
		break;
	}

}
void PlayerAction_Idle::Update(Player* player)
{
	m_idleAnim.Loop(player->GetDeltatime());
}

void PlayerAction_Idle::End(Player* player)
{
	OutputDebugStringA("\nEndIdle -\n");
	player->GetPlayerArm().SetTexture(player->m_currIdleMesh);
}


// MOVE
void PlayerAction_Move::Start(Player* player)
{
	OutputDebugStringA("\nMoving\n");
	m_canMoveArm = true;
	m_cooldownArmMovement = 0.5f;
	m_cooldownArmMovementActual = m_cooldownArmMovement;
}
void PlayerAction_Move::Update(Player* player)
{
	PlayerMovement(player);

	// Arm anim
	if (m_canMoveArm && !m_armIsUp)
	{
		//OutputDebugStringA("UP");
		player->GetPlayerArm().GetComponent<TransformComponent>()->SetRotation(0, 0, 180 + 5);
		m_armIsUp = true;
		m_canMoveArm = false;
	}
	if (m_canMoveArm && m_armIsUp)
	{
		//OutputDebugStringA("DOWN");
		player->GetPlayerArm().GetComponent<TransformComponent>()->SetRotation(0, 0, 180 - 5);
		m_armIsUp = false;
		m_canMoveArm = false;
	}
	if (!m_canMoveArm)
	{
		if (m_cooldownArmMovementActual > 0)
		{
			m_cooldownArmMovementActual -= 1 * player->GetDeltatime();
		}
		if (m_cooldownArmMovementActual <= 0)
		{
			m_canMoveArm = true;
			m_cooldownArmMovementActual = m_cooldownArmMovement;
		}
	}
}
void PlayerAction_Move::End(Player* player)
{
	OutputDebugStringA("\nEnd Moving State\n");
	player->GetPlayerArm().GetComponent<TransformComponent>()->SetRotation(0, 0, 180);
	player->GetPlayerArm().SetTexture(player->m_currIdleMesh);
}


// ATTACK
void PlayerAction_Attack::Start(Player* player)
{
	//anim
	OutputDebugStringA("StartSlash-");
	player->m_attackFinished = false;


	switch (player->m_currIdleMesh)
	{
	case TEXTURES::ARMS:
		OutputDebugStringA("\n Attaque NO Weapon \n");

		break;

	case TEXTURES::IDLEARM_W1_1:
		OutputDebugStringA("\n Attaque Weapon 1\n");
		switch (player->m_slashAttackNb)
		{
		case 1:
			m_attackAnim.Init(FPS_24, &player->GetPlayerArm());
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_1);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_2);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_3);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_4);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_5);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_6);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_7);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_8);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_9);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_10);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_11);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_12);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_13);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_14);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_15);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_16);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_17);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_18);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_19);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_20);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_21);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_22);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_23);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_24);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_25);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_26);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_27);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_28);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_29);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_30);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_31);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_32);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_33);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_34);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_35);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_36);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_37);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_38);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_39);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_40);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_41);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_42);
			m_attackAnim.AddFrame(TEXTURES::ATTACK1_W1_43);
			break;
		case 2:
			m_attackAnim.Init(FPS_24, &player->GetPlayerArm());
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_1);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_2);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_3);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_4);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_5);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_6);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_7);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_8);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_9);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_10);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_11);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_12);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_13);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_14);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_15);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_16);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_17);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_18);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_19);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_20);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_21);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_22);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_23);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_24);
			m_attackAnim.AddFrame(TEXTURES::ATTACK2_W1_25);
			break;
		case 3:
			m_attackAnim.Init(FPS_24, &player->GetPlayerArm());
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_1);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_2);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_3);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_4);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_5);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_6);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_7);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_8);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_9);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_10);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_11);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_12);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_13);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_14);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_15);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_16);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_17);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_18);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_19);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_20);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_21);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_22);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_23);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_24);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_25);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_26);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_27);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_28);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_29);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_30);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_31);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_32);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_33);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_34);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_35);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_36);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_37);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_38);
			m_attackAnim.AddFrame(TEXTURES::ATTACK3_W1_39);
			break;
		default:
			break;
		}

		break;

	case TEXTURES::IDLEARM_W2_1:
		OutputDebugStringA("\n Attaque Weapon 2\n");
		switch (player->m_slashAttackNb)
		{
		case 1:
			m_heavyAttackAnim.Init(FPS_24, &player->GetPlayerArm());
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_1);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_2);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_3);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_4);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_5);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_6);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_7);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_8);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_9);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_10);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_11);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_12);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_13);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_14);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_15);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_16);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_17);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_18);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_19);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_20);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_21);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_22);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_23);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_24);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_25);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_26);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_27);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_28);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_29);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_30);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_31);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_32);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_33);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_34);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_35);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_36);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_37);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_38);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_39);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_40);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_41);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_42);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK1_W2_43);
			break;
		case 2:
			m_heavyAttackAnim.Init(FPS_24, &player->GetPlayerArm());
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_1);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_2);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_3);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_4);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_5);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_6);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_7);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_8);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_9);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_10);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_11);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_12);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_13);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_14);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_15);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_16);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_17);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_18);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_19);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_20);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_21);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_22);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_23);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_24);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_25);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_26);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_27);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_28);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_29);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_30);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_31);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_32);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_33);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_34);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_35);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_36);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_37);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_38);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_39);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_40);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_41);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_42);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_43);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_44);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_45);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK2_W2_46);
			break;
		case 3:
			m_heavyAttackAnim.Init(FPS_24, &player->GetPlayerArm());
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_1);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_2);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_3);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_4);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_5);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_6);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_7);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_8);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_9);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_10);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_11);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_12);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_13);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_14);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_15);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_16);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_17);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_18);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_19);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_20);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_21);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_22);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_23);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_24);
			m_heavyAttackAnim.AddFrame(TEXTURES::ATTACK3_W2_25);
			break;
		default:
			break;
		}


		break;

	default:
		break;
	}


	ComponentMask mask = (1ULL << Tag_Enemy::StaticTypeID);
	auto& ecs = player->mp_gameManager->GetECSManager();
	float closest = 100;
	ecs.ForEach(mask, [&](Entity e)
		{
			Utils::Vector3 newVec;
			auto& playerPos = player->m_playerGameObject.GetPosition();
			auto* tc = ecs.GetComponent<TransformComponent>(e);

			newVec.x = playerPos.x - tc->position.x;
			newVec.y = playerPos.y - tc->position.y;
			newVec.z = playerPos.z - tc->position.z;

			float length = newVec.length();

			if (length < 3.0f)
			{
				if (length < closest)
				{
					closest = length;
					player->m_closestEnemy = &player->mp_scene->GetGameObjectByID(e);
				}
			}
		});


	player->m_slashAttackNb++;
	if (player->m_slashAttackNb > 3)
	{
		player->m_slashAttackNb = 1;
	}


	//sound

	player->mp_gameManager->GetSoundManager()->PlaySoundPlex("swordSlash1"); // need to adapt sound to frame (like adding pause)
}
void PlayerAction_Attack::Update(Player* player)
{
	switch (player->m_currIdleMesh)
	{
	case TEXTURES::ARMS:
		OutputDebugStringA("\n Attaque NO Weapon \n");

		break;

	case TEXTURES::IDLEARM_W1_1:
		m_attackAnim.AnimationSequence(player->GetDeltatime());
		if (m_attackAnim.GetAnimationHisFinished())
		{
			player->m_attackFinished = true;
		}
		break;
	case TEXTURES::IDLEARM_W2_1:
		m_heavyAttackAnim.AnimationSequence(player->GetDeltatime());
		if (m_heavyAttackAnim.GetAnimationHisFinished())
		{
			player->m_attackFinished = true;
		}
		break;
	}

	//atack


	PlayerMovement(player);
}
void PlayerAction_Attack::End(Player* player)
{

	switch (player->m_currIdleMesh)
	{
	case TEXTURES::ARMS:
		OutputDebugStringA("\n Attaque NO Weapon \n");
		break;

	case TEXTURES::IDLEARM_W1_1:
		player->m_closestEnemy ? player->mp_scene->DestroyGameObject(*player->m_closestEnemy) : OutputDebugStringA("\n No Enemy close enough to get hit \n");
		break;
	case TEXTURES::IDLEARM_W2_1:
		//player->m_closestEnemy ? player->mp_scene->DestroyGameObject(*player->m_closestEnemy) : OutputDebugStringA("\n No Enemy close enough to get hit \n");
		if (player->m_closestEnemy)
		{
			player->m_closestEnemy->alive = false;
			player->mp_scene->DestroyGameObject(*player->m_closestEnemy);
			player->m_closestEnemy = nullptr;
		}
		break;
	}

	player->GetPlayerArm().SetTexture(player->m_currIdleMesh);
	OutputDebugStringA("-EndSlash");
}


// JUMP 
void PlayerAction_Jump::Start(Player* player)
{
	OutputDebugStringA("\n- StartJump\n");
	if (player->m_jumpProgress == 0)
	{
		player->m_jumpPosY = player->GetGameObject().GetComponent<TransformComponent>()->position.y;
	}
}
void PlayerAction_Jump::Update(Player* player)
{


	float gForce = 9.18 * 10; // 70 a modifier

	float y = player->m_jumpPosY + (player->m_jumpPower * player->m_jumpProgress) - (0.5f * gForce * (player->m_jumpProgress * player->m_jumpProgress));
	player->GetGameObject().GetComponent<TransformComponent>()->position.y = y;
	player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
	player->m_jumpProgress += player->m_deltatime * 1;


	PlayerMovement(player);
}
void PlayerAction_Jump::End(Player* player)
{
	OutputDebugStringA("\nEndJump -\n");

}


// FALL
void PlayerAction_Fall::Start(Player* player)
{
	if (player->m_fallProgress == 0)
	{
		player->m_jumpPosY = player->GetGameObject().GetComponent<TransformComponent>()->position.y;
	}
}
void PlayerAction_Fall::Update(Player* player)
{
	//float gForce = gravity->m_gravityForce * gravity->m_weight;
	float gForce = 9.18 * 10;

	float y = player->m_jumpPosY - (0.5f * gForce * (player->m_fallProgress * player->m_fallProgress));
	player->GetGameObject().GetComponent<TransformComponent>()->position.y = y;
	player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
	player->m_fallProgress += player->m_deltatime * 1;


	PlayerMovement(player);
}
void PlayerAction_Fall::End(Player* player)
{
	player->GetPlayerArm().SetTexture(player->m_currIdleMesh);
}



// PICK UP OBJECT
void PlayerAction_PickUp::Start(Player* player)
{
	OutputDebugStringA("\n-Start Pick Up\n");

}

void PlayerAction_PickUp::Update(Player* player)
{
	switch (player->m_closestObject->GetTag())
	{
	case TAG_Stick:
		player->GetPlayerArm().SetTexture(TEXTURES::IDLEARM_W1_1);
		player->m_currIdleMesh = TEXTURES::IDLEARM_W1_1;
		player->mp_scene->DestroyGameObject(*player->m_closestObject);
		player->m_slashAttackNb = 1;
		break;
	case TAG_Rock:
		player->GetPlayerArm().SetTexture(TEXTURES::IDLEARM_W2_1);
		player->m_currIdleMesh = TEXTURES::IDLEARM_W2_1;
		player->mp_scene->DestroyGameObject(*player->m_closestObject);
		player->m_slashAttackNb = 1;
		break;
	default:
		break;
	}


}

void PlayerAction_PickUp::End(Player* player)
{
	OutputDebugStringA("\nEnd Pick Up-\n");
}
