#include "pch.h"
#include "PlayerCondition.h"
#include "Utils.h"

bool PlayerCondition_IsInTheAir::OnTest(Player* owner)
{
	return owner->GetGameObject().GetPosition().y > 1;
}
//BOTH NEED CHANGES ONLY WORK ON FLAT MAP
bool PlayerCondition_IsOnGround::OnTest(Player* owner)
{
	return owner->GetGameObject().GetPosition().y <= 1;
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
};

bool PlayerCondition_IsPickingUp::OnTest(Player* owner)
{
	int x = 02;
	x = 2;
	return InputManager::GetKeyIsPressed('F');
	//return InputManager::GetKeyIsJustPressed('F');
}

bool PlayerCondition_IsCloseToObject::OnTest(Player* owner)
{

	bool closeToObject = false;

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

			if (newVec.length() < 3)
			{
				closeToObject = true;
			}
		});


	return closeToObject;
}

bool PlayerCondition_IsNotPickingUp::OnTest(Player* owner)
{
	return !owner->m_isPickingUp;
}
