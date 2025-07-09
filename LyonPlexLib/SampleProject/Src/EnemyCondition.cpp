#include "pch.h"
#include "EnemyCondition.h"
#include "Utils.h"

bool EnnemyCondition_PlayerIsNear::OnTest(Ennemy* owner)
{
	Utils::Vector3 newVec;
	newVec.x = owner->m_playerGm.GetPosition().x - owner->m_ennemyGm.GetPosition().x;
	newVec.y = owner->m_playerGm.GetPosition().y - owner->m_ennemyGm.GetPosition().y;
	newVec.z = owner->m_playerGm.GetPosition().z - owner->m_ennemyGm.GetPosition().z;

	if (newVec.length() < 3) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EnnemyCondition_PlayerIsNotNear::OnTest(Ennemy* owner)
{
	Utils::Vector3 newVec;
	newVec.x = owner->m_playerGm.GetPosition().x - owner->m_ennemyGm.GetPosition().x;
	newVec.y = owner->m_playerGm.GetPosition().y - owner->m_ennemyGm.GetPosition().y;
	newVec.z = owner->m_playerGm.GetPosition().z - owner->m_ennemyGm.GetPosition().z;

	if (newVec.length() > 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}
