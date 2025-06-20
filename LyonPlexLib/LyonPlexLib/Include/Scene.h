#pragma once

#include "GameObject.h"

class SceneManager;

struct SceneEntity 
{
	Entity entity;
	std::string name;
};

class Scene
{
public:
	void Init(SceneManager* sceneManager);

	virtual void Start();
	virtual void Update(float deltatime);
	virtual void Release();

	void ChangeScene(std::string sceneName);

	void SetEcsManager(ECSManager* ecsManager) { mp_ecsManager = ecsManager; };

	void AddEntityToScene(Entity entity, const std::string& entityName); //(a enlever)
	
	SceneEntity CreateEntity(const std::string& entityName);//(a enlever)

	Entity* GetEntity(const std::string& entityName);//(a enlever)

	GameObject& CreateGameObject(const std::string& gameObjectName);
	GameObject& CreateGameObject(const std::string& gameObjectName, DimensionalType type, bool useMesh);

	GameObject& GetGameObjectByName(const std::string& gameObjectName);
	GameObject& GetGameObjectByTag(Tag gameObjectTag);

	void DestroyGameObject(GameObject& gameObject);

	std::vector<GameObject>& GetSceneGameObjects() { return m_sceneGameObjects; };

	void SetParent(const std::string& gameObjectNameChild, const std::string& gameObjectNameParent);

	void EnableLockCursor();
	void DisableLockCursor();

	// Component Entity (a enelver)
	template<typename T>
	void AddComponent(const std::string& entityName, T* comp)
	{
		for (auto& entity : m_sceneEntities)
		{
			if (entity.name == entityName)
			{
				mp_ecsManager->AddComponent<T>(entity.entity, comp);
			}
		}
	}
	template<typename T>
	T* GetComponent(const std::string& entityName) const
	{
		for (auto& entity : m_sceneEntities)
		{
			if (entity.name == entityName)
			{
				return mp_ecsManager->GetComponent<T>(entity.entity);
			}
		}
	}

protected:

	ECSManager* mp_ecsManager;
	SceneManager* mp_sceneManager;

	std::vector<SceneEntity> m_sceneEntities; // old
	std::vector<GameObject> m_sceneGameObjects; // new

};

