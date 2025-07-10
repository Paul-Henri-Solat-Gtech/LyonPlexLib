#include "pch.h"
#include "PlayerAction.h"

// IDLE (dont need to be implemented normaly with override{})
void PlayerAction_Idle::Start(Player* player)
{
	OutputDebugStringA("StartIdle-");
	m_idleAnim.Init(0.05f, &player->GetPlayerArm());
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

}
void PlayerAction_Idle::Update(Player* player)
{
	m_idleAnim.Loop(player->GetDeltatime());
}

void PlayerAction_Idle::End(Player* player)
{
	player->GetPlayerArm().SetTexture(TEXTURES::ARMS);
}


// MOVE
void PlayerAction_Move::Start(Player* player)
{
	m_canMoveArm = true;
	m_cooldownArmMovement = 0.5f;
	m_cooldownArmMovementActual = m_cooldownArmMovement;
}
void PlayerAction_Move::Update(Player* player)
{
	// movements
	{
		if (InputManager::GetKeyIsPressed('Z'))
		{
			player->GetGameObject().GetComponent<TransformComponent>()->position.z += player->GetMoveSpeed() * player->GetDeltatime();
			player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed('S'))
		{
			player->GetGameObject().GetComponent<TransformComponent>()->position.z -= player->GetMoveSpeed() * player->GetDeltatime();
			player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed('Q'))
		{
			player->GetGameObject().GetComponent<TransformComponent>()->position.x -= player->GetMoveSpeed() * player->GetDeltatime();
			player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed('D'))
		{
			player->GetGameObject().GetComponent<TransformComponent>()->position.x += player->GetMoveSpeed() * player->GetDeltatime();
			player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed(VK_SPACE))
		{
			player->GetGameObject().GetComponent<TransformComponent>()->position.y += 10 * player->GetDeltatime();
			player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed(VK_CONTROL))
		{
			player->GetGameObject().GetComponent<TransformComponent>()->position.y -= player->GetMoveSpeed() * player->GetDeltatime();
			player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed(VK_SHIFT))
		{
			player->SetMoveSpeed(player->GetRunSpeed());
			m_cooldownArmMovement = 0.1f;
		}
		else
		{
			player->SetMoveSpeed(player->GetWalkSpeed());
			m_cooldownArmMovement = 0.5f;
		}
	}
	
	// Arm anim
	if (m_canMoveArm && !m_armIsUp) 
	{
		//OutputDebugStringA("UP");
		player->GetPlayerArm().GetComponent<TransformComponent>()->SetRotation(0, 0, 180 + 5);
		m_armIsUp = true;
		m_canMoveArm = false;
	}
	if(m_canMoveArm && m_armIsUp)
	{
		//OutputDebugStringA("DOWN");
		player->GetPlayerArm().GetComponent<TransformComponent>()->SetRotation(0, 0, 180 -5);
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
	player->GetPlayerArm().GetComponent<TransformComponent>()->SetRotation(0, 0, 180);
	player->GetPlayerArm().SetTexture(TEXTURES::ARMS);
}

// JUMP (not needded ?)
void PlayerAction_Jump::Start(Player* player)
{
}
void PlayerAction_Jump::Update(Player* player)
{
}
void PlayerAction_Jump::End(Player* player)
{
}

// ATTACK
void PlayerAction_Attack::Start(Player* player)
{
	//anim
	OutputDebugStringA("StartSlash-");
	player->m_attackFinished = false;

	

	switch (player->m_slashAttackNb)
	{
	case 1:
		m_attackAnim.Init(0.05f, &player->GetPlayerArm());
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_1);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_2);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_3);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_4);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_5);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_6);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_7);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_8);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_9);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_10);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_11);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_12);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_13);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_14);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_15);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_16);
		break;
	case 2:
		m_attackAnim.Init(0.03f, &player->GetPlayerArm());
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_1);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_2);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_3);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_4);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_5);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_6);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_7);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_8);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_9);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_10);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_11);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_12);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_13);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_14);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_15);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_16);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_17);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_18);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_19);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_20);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_21);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_22);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_23);
		m_attackAnim.AddFrame(TEXTURES::ATTACK2_24);
		break;
	case 3:
		m_attackAnim.Init(0.05f, &player->GetPlayerArm());
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_1);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_2);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_3);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_4);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_5);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_6);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_7);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_8);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_9);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_10);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_11);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_12);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_13);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_14);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_15);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_16);
		m_attackAnim.AddFrame(TEXTURES::ATTACK3_17);
		break;
	default:
		break;
	}

	player->m_slashAttackNb++;
	if (player->m_slashAttackNb > 3)
	{
		player->m_slashAttackNb = 1;
	}

	// Attack1 frames
	/*{
		m_attackAnim.Init(0.05f, &player->GetPlayerArm());
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_1);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_2);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_3);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_4);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_5);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_6);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_7);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_8);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_9);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_10);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_11);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_12);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_13);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_14);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_15);
		m_attackAnim.AddFrame(TEXTURES::ATTACK1_16);
	}*/


	//sound

	player->mp_gameManager->GetSoundManager()->PlaySoundPlex("swordSlash1"); // need to adapt sound to frame (like adding pause)
}
void PlayerAction_Attack::Update(Player* player)
{
	m_attackAnim.AnimationSequence(player->GetDeltatime());
	if (m_attackAnim.GetAnimationHisFinished())
	{
		player->m_attackFinished = true;
	}
	//Move
	{
		if (InputManager::GetKeyIsPressed('Z'))
		{
			player->GetGameObject().GetComponent<TransformComponent>()->position.z += player->GetMoveSpeed() * player->GetDeltatime();
			player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed('S'))
		{
			player->GetGameObject().GetComponent<TransformComponent>()->position.z -= player->GetMoveSpeed() * player->GetDeltatime();
			player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed('Q'))
		{
			player->GetGameObject().GetComponent<TransformComponent>()->position.x -= player->GetMoveSpeed() * player->GetDeltatime();
			player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed('D'))
		{
			player->GetGameObject().GetComponent<TransformComponent>()->position.x += player->GetMoveSpeed() * player->GetDeltatime();
			player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed(VK_SPACE))
		{
			player->GetGameObject().GetComponent<TransformComponent>()->position.y += 10 * player->GetDeltatime();
			player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed(VK_CONTROL))
		{
			player->GetGameObject().GetComponent<TransformComponent>()->position.y -= player->GetMoveSpeed() * player->GetDeltatime();
			player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed(VK_SHIFT))
		{
			player->SetMoveSpeed(player->GetRunSpeed());
		}
		else
		{
			player->SetMoveSpeed(player->GetWalkSpeed());
		}
	}
}
void PlayerAction_Attack::End(Player* player)
{
	player->GetPlayerArm().SetTexture(TEXTURES::ARMS);
	OutputDebugStringA("-EndSlash");
}

// FALL
void PlayerAction_Fall::Start(Player* player)
{
}
void PlayerAction_Fall::Update(Player* player)
{
	player->GetGameObject().GetComponent<TransformComponent>()->position.y -= 9.81f * player->m_deltatime;
	player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
}
void PlayerAction_Fall::End(Player* player)
{
	player->GetPlayerArm().SetTexture(TEXTURES::ARMS);
}

void PlayerAction_PickUp::Start(Player* player)
{
	OutputDebugStringA("\n-Start Pick Up\n");
	player->m_isPickingUp = true;
}

void PlayerAction_PickUp::Update(Player* player)
{
	player->m_isPickingUp = false;
}

void PlayerAction_PickUp::End(Player* player)
{
	OutputDebugStringA("\nEnd Pick Up-\n");
}
