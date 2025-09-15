#include "pch.h"
#include "Portals.h"
#include "Utils.h"

Portals::Portals(GameObject& gameObjectPlayer, Scene* scene, int ennemyNb, float groundY) : m_playerGm(gameObjectPlayer)
{
	mp_gameManager = scene->GetSceneManager()->GetGameManager();
	mp_ecs = scene->GetEcsManager();
	m_capacity = ennemyNb;
	m_groundY = groundY;
	m_chooseEnemy = false;

	InitGameObj(mp_ecs, scene);
	SetMesh(MESHES::LOCAL_SQUARE);
	SetTexture(TEXTURES::PORTAL);
	GetComponent<MeshComponent>()->ColorPatchUp();
	GetComponent<MeshComponent>()->alpha = 0.95f;
	SetScale({3,3,1});
}

Portals::Portals(GameObject& gameObjectPlayer, Scene* scene, int ennemyNb, float groundY, EnemyType enemyType) : m_playerGm(gameObjectPlayer)
{
	mp_gameManager = scene->GetSceneManager()->GetGameManager();
	mp_ecs = scene->GetEcsManager();
	m_capacity = ennemyNb;
	m_groundY = groundY;
	m_chooseEnemy = true;
	m_choosedEnemy = enemyType;

	InitGameObj(mp_ecs, scene);
	SetMesh(MESHES::LOCAL_SQUARE);
	SetTexture(TEXTURES::PORTAL);
	GetComponent<MeshComponent>()->ColorPatchUp();
	GetComponent<MeshComponent>()->alpha = 0.95f;
	SetScale({ 3,3,1 });
}

void Portals::OnUpdate(float deltatime)
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

		if (!m_chooseEnemy) 
		{
			//rand enemy
			int randEnemy = (std::rand() % 3) + 1;

			switch (randEnemy)
			{
			case 1:
			{
				auto& newEnemy = mp_scene->CreateGameObject<Enemy>(mp_ecs, mp_gameManager, m_playerGm, mp_scene, EnemyType::Crabe);
				newEnemy.SetPosition({ posX, m_groundY, posZ });
				break;
			}
			case 2:
			{
				auto& newEnemy = mp_scene->CreateGameObject<Enemy>(mp_ecs, mp_gameManager, m_playerGm, mp_scene, EnemyType::Crabe);
				newEnemy.SetPosition({ posX, m_groundY, posZ });
				break;
			}
			case 3:
			{
				auto& newEnemy = mp_scene->CreateGameObject<Enemy>(mp_ecs, mp_gameManager, m_playerGm, mp_scene, EnemyType::Golem);
				newEnemy.SetPosition({ posX, m_groundY + newEnemy.GetScale().y / 2, posZ });
				break;
			}
			}
		}
		else
		{
			//choosed enemy
			auto& newEnemy = mp_scene->CreateGameObject<Enemy>(mp_ecs, mp_gameManager, m_playerGm, mp_scene, m_choosedEnemy);
			newEnemy.SetPosition({ posX, m_groundY, posZ });
		}


		XMFLOAT3 test = { GetScale().x - 0.25f, GetScale().y -0.25f, 1};
		SetScale(test);
		m_capacity--;
	}

	if (m_capacity <= 0)
	{
		m_finishedSpawning = true;
		mp_scene->DestroyGameObject(*this);
	}
}
