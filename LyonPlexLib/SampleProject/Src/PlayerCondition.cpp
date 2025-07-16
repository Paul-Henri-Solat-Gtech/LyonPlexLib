#include "pch.h"
#include "PlayerCondition.h"
#include "Utils.h"

bool PlayerCondition_IsAirBorne::OnTest(Player* owner)
{
	/*bool playerOnObject = false;
	for (auto& object : owner->m_objectsCollidingWithPlayer)
	{
		auto& playerTransform = *owner->mp_gameManager->GetECSManager().GetComponent<TransformComponent>(owner->GetGameObject().GetEntity());
		auto& objectTransform = *owner->mp_gameManager->GetECSManager().GetComponent<TransformComponent>(object);
		if (Utils::IsAbove(playerTransform, objectTransform))
			playerOnObject = true;
	}
	return !playerOnObject;*/
	return (owner->m_fallProgress > 0.2 || owner->m_jumpProgress > 0.2);
}

bool PlayerCondition_IsOnGround::OnTest(Player* owner)
{
	bool playerOnObject = false;
	for (auto& object : owner->m_objectsCollidingWithPlayer)
	{
		auto& playerTransform = *owner->mp_gameManager->GetECSManager().GetComponent<TransformComponent>(owner->GetGameObject().GetEntity());
		auto& objectTransform = *owner->mp_gameManager->GetECSManager().GetComponent<TransformComponent>(object);
		if (Utils::IsAbove(playerTransform, objectTransform))
		{
			playerOnObject = true;
			break;
		}
	}
	return playerOnObject;
}
bool PlayerCondition_IsNotOnGround::OnTest(Player* owner)
{
	bool playerOnObject = false;
	for (auto& object : owner->m_objectsCollidingWithPlayer)
	{
		auto& playerTransform = *owner->mp_gameManager->GetECSManager().GetComponent<TransformComponent>(owner->GetGameObject().GetEntity());
		auto& objectTransform = *owner->mp_gameManager->GetECSManager().GetComponent<TransformComponent>(object);
		if (Utils::IsAbove(playerTransform, objectTransform))
		{
			playerOnObject = true;
			break;
		}
	}
	return !playerOnObject;
}

bool PlayerCondition_IsJumping::OnTest(Player* owner)
{
	return InputManager::GetKeyIsPressed(VK_SPACE);
}

bool PlayerCondition_IsMoving::OnTest(Player* owner)
{
	return InputManager::GetKeyIsPressed('Z') || InputManager::GetKeyIsPressed('Q') || InputManager::GetKeyIsPressed('S') || InputManager::GetKeyIsPressed('D');
}

bool PlayerCondition_IsNotMoving::OnTest(Player* owner)
{
	return !(InputManager::GetKeyIsPressed('Z') || InputManager::GetKeyIsPressed('Q') || InputManager::GetKeyIsPressed('S') || InputManager::GetKeyIsPressed('D'));
}

bool PlayerCondition_IsAttacking::OnTest(Player* owner)
{
	return InputManager::GetKeyIsJustPressed(VK_LBUTTON);
}

bool PlayerCondition_AttackFinished::OnTest(Player* owner)
{
	return owner->m_attackFinished;
}

bool PlayerCondition_IsPickingUp::OnTest(Player* owner)
{
	//return InputManager::GetKeyIsPressed('F');
	return InputManager::GetKeyIsJustPressed('F');
}

bool PlayerCondition_IsCloseToObject::OnTest(Player* owner)
{

	bool closeToObject = false;

	float closest = 100;
	ComponentMask mask = (1ULL << Tag_Object::StaticTypeID);
	auto& ecs = owner->mp_gameManager->GetECSManager();
	ecs.ForEach(mask, [&](Entity e)
		{
			Utils::Vector3 newVec;
			auto& playerPos = owner->m_playerGameObject.GetPosition();
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
					owner->m_closestObject = &owner->mp_scene->GetGameObjectByID(e);
					closeToObject = true;
				}
			}
		});


	return closeToObject;
}

bool PlayerCondition_IsNotPickingUp::OnTest(Player* owner)
{
	return !owner->m_isPickingUp;
}

bool PlayerCondition_IsCloseToEnemy::OnTest(Player* owner)
{

	bool closeToEnemy = false;

	ComponentMask mask = (1ULL << Tag_Enemy::StaticTypeID);
	auto& ecs = owner->mp_gameManager->GetECSManager();
	float closest = 100;
	ecs.ForEach(mask, [&](Entity e)
		{
			Utils::Vector3 newVec;
			auto& playerPos = owner->m_playerGameObject.GetPosition();
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
					owner->m_closestEnemy = &owner->mp_scene->GetGameObjectByID(e);
					closeToEnemy = true;
				}
			}
		});


	return closeToEnemy;
}
