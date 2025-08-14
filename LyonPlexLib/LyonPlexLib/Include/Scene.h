#pragma once

#include "GameObject.h"
#include "Button.h"
#include "FreeCamera.h"
//#include "Enemy.h"

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

	void SceneUpdate(float deltatime);

	void ChangeScene(std::string sceneName);

	void SetEcsManager(ECSManager* ecsManager) { mp_ecsManager = ecsManager; };

	ECSManager* GetEcsManager() { return mp_ecsManager; };

	SceneManager* GetSceneManager() { return mp_sceneManager; };

	void AddEntityToScene(Entity entity, const std::string& entityName); //(a enlever)
	
	SceneEntity CreateEntity(const std::string& entityName);//(a enlever)

	Entity* GetEntity(const std::string& entityName);//(a enlever)

	GameObject& CreateGameObject(const std::string& gameObjectName);
	GameObject& CreateGameObject(const std::string& gameObjectName, uint32_t meshId, uint32_t textureId);
	GameObject& CreateWaterGameObject();
	GameObject& CreateWaterGameObject(const std::string& gameObjectName);
	GameObject& CreateGameObject(const std::string& gameObjectName, /*std::vector<std::unique_ptr<GameObject>>& sceneGameObjects,*/ DimensionalType type, bool useMesh = true);
	GameObject& CreateBoulder(const std::string& gameObjectName, DimensionalType type, bool useMesh);
	GameObject& CreateGameHitbox(const std::string& gameObjectName = "");

	GameObject& GetGameObjectByName(const std::string& gameObjectName);
	GameObject* FindGameObjectByName(const std::string& name);
	GameObject& GetGameObjectByTag(Tag gameObjectTag);
	GameObject& GetGameObjectByID(Entity entityID);

	void DestroyGameObject(GameObject& gameObject);
	void EndUpdate();

	std::vector<std::unique_ptr<GameObject>>& GetSceneGameObjects() { return m_sceneGameObjects; };

	void SetParent(const std::string& gameObjectNameChild, const std::string& gameObjectNameParent);
	void SetParent(GameObject& gameObjectChild, GameObject& gameObjectParent);

	void EnableLockCursor();
	void DisableLockCursor();
	void CenterLockCursor();

	void EnableMouseRotationFor(GameObject& target, float sensitivity);

	// Audio
	void CreateSoundPlex(const std::string& soundName, const std::wstring& soundPath);
	void PlaySoundPlex(const std::string& soundName);
	void PlayMusicPlex(const std::string& musicName);
	void StopMusicPlex();

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

	template<typename T, typename... Args>
	T& CreateGameObject(Args&&... ctorArgs) 
	{
		static_assert(std::is_base_of<GameObject, T>::value,
			"T doit hériter de GameObject");
		// 1) On construit un unique_ptr<T> avec les bons arguments
		auto ptr = std::make_unique<T>(std::forward<Args>(ctorArgs)...);
		// 2) On récupère la référence sur l'objet
		T& ref = *ptr;
		// 4) On l'insère dans le container (upcast automatique)
		m_sceneGameObjects.emplace_back(std::move(ptr));
		return ref;
	}

	/*std::vector<Enemy*> m_enemies;
	int m_enemyCount = 0;*/

protected:

	ECSManager* mp_ecsManager;
	SceneManager* mp_sceneManager;

	std::vector<SceneEntity> m_sceneEntities; // old
	//std::vector<GameObject> m_sceneGameObjects; // new
	std::vector<std::unique_ptr<GameObject>> m_sceneGameObjects; // new
	//std::vector<GameObject*> m_sceneGameObjectsToDelete;

	// Mouse
	bool m_mouseRotating;
	POINT m_lastMousePos;

	int m_waveCount = 0;
};

