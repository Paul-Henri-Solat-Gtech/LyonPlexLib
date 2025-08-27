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

	GetComponent<TransformComponent>()->AddRotation(0.f,0.f,0.1f);
	LookAt(m_playerGm);

	if (m_timer > 1.5 && m_capacity > 0)
	{
		m_timer = 0;

		auto& newEnemy = mp_scene->CreateGameObject<Enemy>(mp_ecs, mp_gameManager, m_playerGm, mp_scene, EnemyType::Crabe);

		float x = GetPosition().x;
		float posX = x;
		while ((posX < x + 1) && (posX > x - 1))
		{
			posX = Utils::randomFloat(x - 4, x + 4);
		}

		float z = GetPosition().z;
		float posZ = z;
		while ((posZ < z + 1) && (posZ > z - 1))
		{
			posZ = Utils::randomFloat(z - 4, z + 4);
		}

		float y = GetPosition().y;
		float posY = y;
		while ((posY < y + 1) && (posY > y - 1))
		{
			posY = Utils::randomFloat(y - 1, y + 1);
		}

		newEnemy.SetPosition({ posX, posY, posZ });
		newEnemy.SetMesh(MESHES::LOCAL_SQUARE);
		newEnemy.SetTexture(TEXTURES::iceCream);

		XMFLOAT3 test = { GetScale().x - 0.1f, GetScale().y -0.1f, GetScale().z - 0.1f};
		SetScale(test);
		m_capacity--;
	}

	if (m_capacity <= 0)
	{
		mp_scene->DestroyGameObject(*this);
	}
}
