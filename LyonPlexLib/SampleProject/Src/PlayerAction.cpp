#include "pch.h"
#include "PlayerAction.h"

// IDLE (dont need to be implemented normaly with override{})
void PlayerAction_Idle::Start(Player* player)
{
	OutputDebugStringA("StartIdle-");
	m_idleAnim.Init(0.05f, &player->GetPlayerArm());
	// idle frames
	{
		m_idleAnim.AddFrame(TEXTURES::idleArm1);
		m_idleAnim.AddFrame(TEXTURES::idleArm2);
		m_idleAnim.AddFrame(TEXTURES::idleArm3);
		m_idleAnim.AddFrame(TEXTURES::idleArm4);
		m_idleAnim.AddFrame(TEXTURES::idleArm5);
		m_idleAnim.AddFrame(TEXTURES::idleArm6);
		m_idleAnim.AddFrame(TEXTURES::idleArm7);
		m_idleAnim.AddFrame(TEXTURES::idleArm8);
		m_idleAnim.AddFrame(TEXTURES::idleArm9);
		m_idleAnim.AddFrame(TEXTURES::idleArm10);
		m_idleAnim.AddFrame(TEXTURES::idleArm11);
		m_idleAnim.AddFrame(TEXTURES::idleArm12);
		m_idleAnim.AddFrame(TEXTURES::idleArm13);
		m_idleAnim.AddFrame(TEXTURES::idleArm14);
		m_idleAnim.AddFrame(TEXTURES::idleArm15);
		m_idleAnim.AddFrame(TEXTURES::idleArm16);
		m_idleAnim.AddFrame(TEXTURES::idleArm17);
		m_idleAnim.AddFrame(TEXTURES::idleArm18);
		m_idleAnim.AddFrame(TEXTURES::idleArm19);
		m_idleAnim.AddFrame(TEXTURES::idleArm20);
		m_idleAnim.AddFrame(TEXTURES::idleArm21);
		m_idleAnim.AddFrame(TEXTURES::idleArm22);
		m_idleAnim.AddFrame(TEXTURES::idleArm23);
		m_idleAnim.AddFrame(TEXTURES::idleArm24);
	}

}
void PlayerAction_Idle::Update(Player* player)
{
	m_idleAnim.Loop(player->GetDeltatime());
}

void PlayerAction_Idle::End(Player* player)
{
	player->GetPlayerArm().SetTexture(TEXTURES::bras);
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
	player->GetPlayerArm().SetTexture(TEXTURES::bras);
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
	m_attackAnim.Init(1.f, &player->GetPlayerArm());
	m_attackAnim.AddFrame(TEXTURES::bras);
	m_attackAnim.AddFrame(TEXTURES::test);
	m_attackAnim.AddFrame(TEXTURES::tex0);
	m_attackAnim.AddFrame(TEXTURES::bras);

	//sound
	player->mp_gameManager->GetSoundManager()->CreateSound("swordSlash1", L"../LyonPlexLib/Ressources/swordSlash1.wav");
	player->mp_gameManager->GetSoundManager()->PlaySoundPlex("swordSlash1");
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
	player->GetPlayerArm().SetTexture(TEXTURES::bras);
	OutputDebugStringA("-EndSlash");
}

// FALL
void PlayerAction_Fall::Start(Player* player)
{
}
void PlayerAction_Fall::Update(Player* player)
{
	player->GetGameObject().GetComponent<TransformComponent>()->position.y -= 9.81f * player->GetDeltatime();
	player->GetGameObject().GetComponent<TransformComponent>()->dirty = true;
}
void PlayerAction_Fall::End(Player* player)
{
	player->GetPlayerArm().SetTexture(TEXTURES::bras);
}
