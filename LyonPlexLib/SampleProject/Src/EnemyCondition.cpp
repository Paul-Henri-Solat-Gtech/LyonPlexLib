#include "pch.h"
#include "EnemyCondition.h"
#include "Utils.h"

bool EnnemyCondition_PlayerIsNear::OnTest(Enemy* owner)
{
	Utils::Vector3 newVec;
	newVec.x = owner->m_playerGm.GetPosition().x - owner->GetPosition().x;
	newVec.y = owner->m_playerGm.GetPosition().y - owner->GetPosition().y;
	newVec.z = owner->m_playerGm.GetPosition().z - owner->GetPosition().z;

	if (newVec.length() < 20 && newVec.length() > 10)
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
	Utils::Vector3 newVec;
	newVec.x = owner->m_playerGm.GetPosition().x - owner->GetPosition().x;
	newVec.y = owner->m_playerGm.GetPosition().y - owner->GetPosition().y;
	newVec.z = owner->m_playerGm.GetPosition().z - owner->GetPosition().z;

	if (newVec.length() < 10)
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
	Utils::Vector3 newVec;
	newVec.x = owner->m_playerGm.GetPosition().x - owner->GetPosition().x;
	newVec.y = owner->m_playerGm.GetPosition().y - owner->GetPosition().y;
	newVec.z = owner->m_playerGm.GetPosition().z - owner->GetPosition().z;

	if (newVec.length() > 20)
	{
		return true;
	}
	else
	{
		return false;
	}
}
