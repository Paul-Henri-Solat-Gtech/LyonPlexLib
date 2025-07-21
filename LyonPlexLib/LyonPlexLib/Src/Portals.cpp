#include "pch.h"
#include "Portals.h"
#include "Enemy.h"
#include "Utils.h"

Portals::Portals(ECSManager* ecsManager, GameManager* gameManager, GameObject& gameObjectPlayer, Scene* scene) : m_playerGm(gameObjectPlayer)
{
	InitGameObj(ecsManager, scene);
	mp_gameManager = gameManager;
	mp_ecs = ecsManager;
}

void Portals::OnUdpdate(float deltatime)
{
	m_timer += deltatime;

	if (m_timer > 1.5 && m_capacity < 0)
	{
		auto& newEnemy = mp_scene->CreateGameObject<Enemy>(mp_ecs, mp_gameManager, m_playerGm, mp_scene);

		float x = GetPosition().x;
		float posX = x;
		while ((posX < x + 2) && (posX > x - 2))
		{
			posX = Utils::randomFloat(GetPosition().x - 3, x + 3);
		}

		float z = GetPosition().z;
		float posZ = z;
		while ((posZ < z + 2) && (posZ > z - 2))
		{
			posZ = Utils::randomFloat(z - 3, z + 3);
		}

		newEnemy.SetPosition({ posX, 1, posZ });
		newEnemy.SetTexture(TEXTURES::iceCream);
		m_timer = 0;

		m_capacity--;
	}
}
