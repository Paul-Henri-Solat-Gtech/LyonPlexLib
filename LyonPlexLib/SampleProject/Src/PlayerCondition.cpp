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
