#include "pch.h"
#include "Portals.h"
#include "Enemy.h"
#include "Utils.h"

Portals::Portals(GameObject& gameObjectPlayer, Scene* scene, int ennemyNb) : m_playerGm(gameObjectPlayer)
{
	mp_gameManager = scene->GetSceneManager()->GetGameManager();
	mp_ecs = scene->GetEcsManager();
	m_capacity = ennemyNb;

	InitGameObj(mp_ecs, scene);

	GetComponent<MeshComponent>()->ColorPatchUp();
}

void Portals::OnUdpdate(float deltatime)
{
	m_timer += deltatime;

	GetComponent<TransformComponent>()->AddRotation(0.f,0.f,0.1f);
	LookAt(m_playerGm);
	auto rotZ = GetRotation().z;
	rotZ += 5;
	AddRotation({0,0,rotZ});

	if (m_timer > 1.5 && m_capacity > 0)
	{
		m_timer = 0;

		//rand pos
		float x = GetPosition().x;
		float posX = x;
		posX = Utils::randomFloat(x - 4, x + 4);

		float z = GetPosition().z;
		float posZ = z;
		posZ = Utils::randomFloat(z - 4, z + 4);

		//float y = GetPosition().y;
		//float posY = y + 1;
		//posY = Utils::randomFloat(y - 1, y + 1);

		//rand enemy
		int randEnemy = (std::rand() % 3) + 1;

		switch (randEnemy)
		{
		case 1: 
		{
			auto& newEnemy = mp_scene->CreateGameObject<Enemy>(mp_ecs, mp_gameManager, m_playerGm, mp_scene, EnemyType::Crabe);
			newEnemy.SetPosition({ posX, newEnemy.GetPosition().y, posZ});
			break;
		}
		case 2: 
		{
			auto& newEnemy = mp_scene->CreateGameObject<Enemy>(mp_ecs, mp_gameManager, m_playerGm, mp_scene, EnemyType::Crabe);
			newEnemy.SetPosition({ posX, newEnemy.GetPosition().y, posZ });
			break;
		}
		case 3: 
		{
			auto& newEnemy = mp_scene->CreateGameObject<Enemy>(mp_ecs, mp_gameManager, m_playerGm, mp_scene, EnemyType::Golem);
			newEnemy.SetPosition({ posX, newEnemy.GetPosition().y, posZ });
			break;
		}
		}

		XMFLOAT3 test = { GetScale().x - 0.1f, GetScale().y -0.1f, GetScale().z - 0.1f};
		SetScale(test);
		m_capacity--;
	}

	if (m_capacity <= 0)
	{
		mp_scene->DestroyGameObject(*this);
	}
}
