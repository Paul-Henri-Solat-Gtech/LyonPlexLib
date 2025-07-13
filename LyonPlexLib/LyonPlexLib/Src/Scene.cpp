#include "pch.h"
#include "Scene.h"

void Scene::Init(SceneManager* sceneManager)
{
	mp_sceneManager = sceneManager;
	m_mouseRotating = false;
	m_lastMousePos = { 0,0 };
	ShowCursor(TRUE);
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
GameObject& Scene::CreateGameObject(const std::string& gameObjectName, uint32_t meshId, uint32_t textureId)
{
	GameObject newGameObject;
	newGameObject.Init(gameObjectName, mp_ecsManager, meshId, textureId);

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

GameObject& Scene::GetGameObjectByID(Entity entityID)
{
	for (auto& gO : m_sceneGameObjects)
	{
		if (gO.GetEntity().id == entityID.id)
			return gO;
	}
}

void Scene::DestroyGameObject(GameObject& gameObject)
{

	// 2) Remove Gameobject
	const std::string& gmName = gameObject.GetName();
	m_sceneGameObjects.erase
	(
		std::remove_if(
			m_sceneGameObjects.begin(),
			m_sceneGameObjects.end(),
			[&](GameObject& gm) { return gm.GetName() == gmName; }),
		m_sceneGameObjects.end()
	);
	// 1) DestroyEntity
	mp_ecsManager->DestroyEntity(gameObject.GetEntity());
}

void Scene::SetParent(const std::string& gameObjectNameChild, const std::string& gameObjectNameParent)
{
	GameObject& objChild = GetGameObjectByName(gameObjectNameChild);
	GameObject& objParent = GetGameObjectByName(gameObjectNameParent);

	//objChild.GetComponent<TransformComponent>()->parent = { objParent.GetEntity()->id };
	GetGameObjectByName(gameObjectNameChild).GetComponent<TransformComponent>()->parent = { GetGameObjectByName(gameObjectNameParent).GetEntity().id };

}

void Scene::SetParent(GameObject& gameObjectChild, GameObject& gameObjectParent)
{
	gameObjectChild.GetComponent<TransformComponent>()->parent = { gameObjectParent.GetEntity().id };
}

void Scene::EnableLockCursor()
{
	InputManager::EnableFPSMouseLock(mp_sceneManager->GetWindow());
}

void Scene::DisableLockCursor()
{
	InputManager::DisableFPSMouseLock();
}

void Scene::CenterLockCursor()
{
	InputManager::CenterLockCursor(mp_sceneManager->GetWindow());
}

void Scene::EnableMouseRotationFor(GameObject& target, float sensitivity)
{
	if (!mp_sceneManager->GetWindow()) return;

	// Détecter état du clic droit
	SHORT state = GetAsyncKeyState(VK_MBUTTON);
	bool pressed = (state & 0x8000) != 0;

	// Démarrage de la rotation (front montant)
	if (pressed && !m_mouseRotating) {
		m_mouseRotating = true;
		SetCapture(mp_sceneManager->GetWindow());
		ShowCursor(FALSE);
		GetCursorPos(&m_lastMousePos);
	}
	// Fin de la rotation (front descendant)
	else if (!pressed && m_mouseRotating) {
		m_mouseRotating = false;
		ReleaseCapture();
		ShowCursor(TRUE);
		return;
	}

	// Si en rotation active, appliquer sur 'target'
	if (m_mouseRotating) {
		POINT cur;
		GetCursorPos(&cur);
		int dx = cur.x - m_lastMousePos.x;
		int dy = cur.y - m_lastMousePos.y;

		// Conversion pixel→angle (sans deltaTime en général)
		float deltaYaw = dx * sensitivity;
		float deltaPitch = -dy * sensitivity;

		// Si vous vouliez malgré tout moduler par deltaTime (souvent inutile pour la souris) :
		// deltaYaw   *= deltaTime;
		// deltaPitch *= deltaTime;

		if (auto t = target.GetComponent<TransformComponent>()) {
			t->AddRotation(deltaPitch, deltaYaw, 0.0f);
			t->dirty = true;
		}

		// Recentrer pour éviter bords d’écran
		SetCursorPos(m_lastMousePos.x, m_lastMousePos.y);
	}
}

void Scene::CreateSoundPlex(const std::string& soundName, const std::wstring& soundPath)
{
	mp_sceneManager->GetGameManager()->GetSoundManager()->CreateSound(soundName, soundPath);
}
void Scene::PlaySoundPlex(const std::string& soundName)
{
	mp_sceneManager->GetGameManager()->GetSoundManager()->PlaySoundPlex(soundName);
}
void Scene::PlayMusicPlex(const std::string& musicName) 
{
	mp_sceneManager->GetGameManager()->GetSoundManager()->PlayMusicPlex(musicName);
}
void Scene::StopMusicPlex()
{
	mp_sceneManager->GetGameManager()->GetSoundManager()->StopMusic();
}