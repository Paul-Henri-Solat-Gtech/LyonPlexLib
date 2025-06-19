#include "pch.h"
#include "Scene.h"

void Scene::Init(SceneManager* sceneManager)
{
	mp_sceneManager = sceneManager;
	Start();
}

void Scene::Start()
{
	OutputDebugStringA("\nScene has started ! \n");
}

void Scene::Update(float deltatime)
{

}

void Scene::Release()
{
	m_sceneEntities.clear();
	m_sceneGameObjects.clear();
	mp_ecsManager->ClearAllEntities();
}

void Scene::ChangeScene(std::string sceneName)
{
	mp_sceneManager->SetScene(sceneName);
}

void Scene::AddEntityToScene(Entity entity, const std::string& entityName)
{
	SceneEntity newEntity;
	newEntity.entity = entity;
	newEntity.name = entityName;

	m_sceneEntities.push_back(newEntity);
}

SceneEntity Scene::CreateEntity(const std::string& entityName)
{
	Entity newEntity = mp_ecsManager->CreateEntity();

	AddEntityToScene(newEntity, entityName);

	//	Adding basics component(s) for any entity in scene & default parameters :
	//	TRANSFORM
	AddComponent<TransformComponent>(entityName, new TransformComponent());
	GetComponent<TransformComponent>(entityName)->position = { 0, 0, 0 };
	//GetComponent<TransformComponent>(entityName)->dirty = true;
	//	... Add other component here if needed

	return SceneEntity();
}

Entity* Scene::GetEntity(const std::string& entityName)
{
	for (auto& entity : m_sceneEntities)
	{
		if (entity.name == entityName)
		{
			return &entity.entity;
		}
	}
	return nullptr;
}

GameObject& Scene::CreateGameObject(const std::string& gameObjectName)
{
	GameObject newGameObject;
	newGameObject.Init(gameObjectName, mp_ecsManager);

	m_sceneGameObjects.push_back(newGameObject);

	return newGameObject;
}
GameObject& Scene::CreateGameObject(const std::string& gameObjectName, DimensionalType type, bool useMesh)
{
	GameObject newGameObject;
	newGameObject.Init(gameObjectName, mp_ecsManager, type, useMesh);
	
	m_sceneGameObjects.push_back(newGameObject);

	return newGameObject;
}

GameObject& Scene::GetGameObjectByName(const std::string& gameObjectName)
{
	for (auto& gameObject : m_sceneGameObjects) 
	{
		if (gameObject.GetName() == gameObjectName) 
		{
			return gameObject;
		}
	}
}

GameObject& Scene::GetGameObjectByTag(Tag gameObjectTag)
{
	for (auto& gameObject : m_sceneGameObjects)
	{
		if (gameObject.GetTag() == gameObjectTag)
		{
			return gameObject;
		}
	}
}

void Scene::SetParent(const std::string& gameObjectNameChild, const std::string& gameObjectNameParent)
{
	GameObject& objChild = GetGameObjectByName(gameObjectNameChild);
	GameObject& objParent = GetGameObjectByName(gameObjectNameParent);

	//objChild.GetComponent<TransformComponent>()->parent = { objParent.GetEntity()->id };
	GetGameObjectByName(gameObjectNameChild).GetComponent<TransformComponent>()->parent = { GetGameObjectByName(gameObjectNameParent).GetEntity()->id };

}
