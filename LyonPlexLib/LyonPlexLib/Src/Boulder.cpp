#include "pch.h"
#include "Boulder.h"

Boulder::Boulder(ECSManager* ecsManager, GameManager* gameManager, GameObject& gameObjectPlayer, Scene* scene) : m_playerGm(gameObjectPlayer)
{
	InitGameObj(ecsManager, scene);
	mp_gameManager = gameManager;
	mp_ecs = ecsManager;

	SetMesh(MESHES::CAILLOUX3);
	SetTexture(TEXTURES::PIERRE);
	AddComponent<Tag_Boulder>(new Tag_Boulder());
}

void Boulder::OnUdpdate(float deltatime)
{

	if(m_slideDistLeft > 0.2)
	{
	float dist = Utils::lerp(0, m_slideDistLeft, 0.05);
		MoveInDirection({ m_dir.x, m_dir.y, m_dir.z }, dist);

		m_slideDistLeft -= dist;
	}


}

void Boulder::GetPushed(Utils::Vector3 dir)
{
	m_dir = dir;
	m_slideDistLeft = m_slideDistance;
}

