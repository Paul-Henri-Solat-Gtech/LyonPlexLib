#include "pch.h"
#include "EnemyCondition.h"
#include "Utils.h"

bool EnnemyCondition_PlayerIsNear::OnTest(Enemy* owner)
{
	if (owner->m_distanceBetweenEnnemyPlayer.length() < 70 && owner->m_distanceBetweenEnnemyPlayer.length() > 15)
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
	if (owner->m_distanceBetweenEnnemyPlayer.length() < 15)
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
	if (owner->m_distanceBetweenEnnemyPlayer.length() > 70)
	{
		return true;
	}
	else
	{
		return false;
	}
}
