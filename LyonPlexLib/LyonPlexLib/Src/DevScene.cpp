#include "pch.h"
#include "DevScene.h"

void DevScene::Start()
{
    CreateGameObject("camera", TYPE_3D, false);
    GetGameObjectByName("camera").AddComponent<CameraComponent>(new CameraComponent());
    GetGameObjectByName("camera").SetPosition({ 0, 0.5, -1 });

    CreateGameObject("cube2");
    GetGameObjectByName("cube2").SetPosition({ 0, 0, -1 });

    SetParent("camera", "cube2");

	CreateGameObject("placementCube");
	GetGameObjectByName("placementCube").SetPosition({ 0, 1, 0 });

	SetParent("placementCube", "camera");

	m_newIdGM = 0;
	
	// Test

}

void DevScene::Update(float deltatime)
{
	//Input
	if (InputManager::GetKeyIsPressed('Z'))
	{
		GetGameObjectByName("cube2").GetComponent<TransformComponent>()->position.z += 1.f * deltatime;
		GetGameObjectByName("cube2").GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('S'))
	{
		GetGameObjectByName("cube2").GetComponent<TransformComponent>()->position.z -= 1.f * deltatime;
		GetGameObjectByName("cube2").GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('Q'))
	{
		GetGameObjectByName("cube2").GetComponent<TransformComponent>()->position.x -= 1.f * deltatime;
		GetGameObjectByName("cube2").GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('D'))
	{
		GetGameObjectByName("cube2").GetComponent<TransformComponent>()->position.x += 1.f * deltatime;
		GetGameObjectByName("cube2").GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_SPACE))
	{
		GetGameObjectByName("cube2").GetComponent<TransformComponent>()->position.y += 1.f * deltatime;
		GetGameObjectByName("cube2").GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_CONTROL))
	{
		GetGameObjectByName("cube2").GetComponent<TransformComponent>()->position.y -= 1.f * deltatime;
		GetGameObjectByName("cube2").GetComponent<TransformComponent>()->dirty = true;
	}

    if (InputManager::GetKeyIsReleased('A'))
    {
        ChangeScene("SampleScene2");
    }

	// Adding blocks (make a function in this scene)
	if (InputManager::GetKeyIsReleased(VK_LBUTTON))
	{
		XMFLOAT3 posCamera = GetGameObjectByName("cube2").GetPosition();
		std::string gmName = "GM" + std::to_string(m_newIdGM);

		CreateGameObject(gmName);
		GetGameObjectByName(gmName).SetPosition({ posCamera });
		GetGameObjectByName(gmName).SetTag(TAG_Object);

		std::string msg = "\nAdded " + gmName + " At[ X: " + std::to_string(GetGameObjectByName(gmName).GetPosition().x) + " Y: " + std::to_string(GetGameObjectByName(gmName).GetPosition().y) + " Z: " + std::to_string(GetGameObjectByName(gmName).GetPosition().z);
		OutputDebugStringA(msg.c_str());

		m_newIdGM++;
	}

	// Undo
	if (InputManager::GetKeyIsReleased(VK_F2))
	{
		if (!GetSceneGameObjects().empty())
		{
			if (GetSceneGameObjects().back().GetTag() == TAG_Object)
			{
				m_lastPlacedGmName = GetSceneGameObjects().back().GetName();
				m_lastPlacedGmPos = GetSceneGameObjects().back().GetPosition();

				DestroyGameObject(GetSceneGameObjects().back());
			}
		}
	}
	// Redo (Prototype)
	if (InputManager::GetKeyIsReleased(VK_F3))
	{
		if (m_lastPlacedGmName != "")
		{
			CreateGameObject(m_lastPlacedGmName);
			GetGameObjectByName(m_lastPlacedGmName).SetPosition(m_lastPlacedGmPos);
			GetGameObjectByName(m_lastPlacedGmName).SetTag(TAG_Object);

			m_lastPlacedGmName = "";
		}
	}

	// Generating scene outpout
	if (InputManager::GetKeyIsReleased(VK_RETURN)) 
	{
		OutputDebugStringA("\n\n----------- GENERATING SCENE CM's -----------");
		for (auto gm : GetSceneGameObjects()) 
		{
			if (gm.GetTag() == TAG_Object) 
			{
				std::string cm_create = std::string("\nCreateGameObject(\"") + gm.GetName() + "\");";
				std::string cm_position = std::string("\nGetGameObjectByName(\"") + gm.GetName() + "\").SetPosition({ " + std::to_string(gm.GetPosition().x) + "," + std::to_string(gm.GetPosition().y) + "," + std::to_string(gm.GetPosition().z) + " });";

				OutputDebugStringA(cm_create.c_str());
				OutputDebugStringA(cm_position.c_str());
			}
		}
		OutputDebugStringA("\n----------- --------------------- -----------\n");
	}

	// LockMouse
	if (InputManager::GetKeyIsReleased(VK_F5))
	{
		OutputDebugStringA("\LockMouse\n");
		if (InputManager::IsMouseLocked()) 
		{
			DisableLockCursor();
		}
		else
		{
			EnableLockCursor();
		}
	}
}

void DevScene::Release()
{

}
