#include "pch.h"
#include "PlayerCondition.h"

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
    return !(InputManager::GetKeyIsPressed('Z') ||InputManager::GetKeyIsPressed('Q') || InputManager::GetKeyIsPressed('S') || InputManager::GetKeyIsPressed('D'));
}

bool PlayerCondition_IsAttacking::OnTest(Player* owner)
{
    return InputManager::GetKeyIsJustPressed(VK_LBUTTON);
}

bool PlayerCondition_AttackFinished::OnTest(Player* owner)
{
    return owner->m_attackFinished;
};