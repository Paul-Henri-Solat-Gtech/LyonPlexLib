#include "pch.h"
#include "PlayerAction.h"

// IDLE (dont need to be implemented normaly)

// MOVE
void PlayerAction_Move::Start(Player* player)
{
}
void PlayerAction_Move::Update(Player* player)
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
void PlayerAction_Move::End(Player* player)
{
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
}
void PlayerAction_Attack::Update(Player* player)
{
}
void PlayerAction_Attack::End(Player* player)
{
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
}
