#include "pch.h"
#include "EnemyCondition.h"
#include "Utils.h"

bool EnnemyCondition_PlayerIsNear::OnTest(Enemy* owner)
{
	if (owner->m_distanceBetweenEnnemyPlayer.length() < 50 && owner->m_distanceBetweenEnnemyPlayer.length() > 20)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EnnemyCondition_PlayerIsVeryNear::OnTest(Enemy* owner)
{
	if (owner->m_distanceBetweenEnnemyPlayer.length() < 20)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EnnemyCondition_PlayerIsNotNear::OnTest(Enemy* owner)
{
	if (owner->m_distanceBetweenEnnemyPlayer.length() > 50)
	{
		return true;
	}
	else
	{
		return false;
	}
}
