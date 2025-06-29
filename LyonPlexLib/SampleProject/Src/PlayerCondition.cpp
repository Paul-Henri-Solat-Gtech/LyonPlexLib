#include "pch.h"
#include "PlayerCondition.h"

bool PlayerCondition_IsInTheAir::OnTest(Player* owner)
{
    return false; // checkPosition
}

bool PlayerCondition_IsOnGround::OnTest(Player* owner)
{
    return false; // checkPosition and return true if true
}

bool PlayerCondition_IsMoving::OnTest(Player* owner)
{
    if (InputManager::GetKeyIsPressed('Z') || InputManager::GetKeyIsPressed('Q') || InputManager::GetKeyIsPressed('S') || InputManager::GetKeyIsPressed('D'))
    {
        return true;
    }
}

bool PlayerCondition_IsNotMoving::OnTest(Player* owner)
{
    return !(InputManager::GetKeyIsPressed('Z') ||InputManager::GetKeyIsPressed('Q') || InputManager::GetKeyIsPressed('S') || InputManager::GetKeyIsPressed('D'));
}
