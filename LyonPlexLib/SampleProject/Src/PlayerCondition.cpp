#include "pch.h"
#include "PlayerCondition.h"

bool PlayerCondition_IsInTheAir::OnTest(Player* owner)
{
    if (owner->GetGameObject().GetPosition().y > 1) 
    {
        return true;
    }
}
//BOTH NEED CHANGES ONLY WORK ON FLAT MAP
bool PlayerCondition_IsOnGround::OnTest(Player* owner)
{
    if (owner->GetGameObject().GetPosition().y <= 1)
    {
        return true;
    }
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

bool PlayerCondition_IsAttacking::OnTest(Player* owner)
{
    if (InputManager::GetKeyIsReleased(VK_LBUTTON))
    {
        return true;
    }
}