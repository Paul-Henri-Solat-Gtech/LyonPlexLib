#include "pch.h"
#include "DevScene.h"

void DevScene::Start()
{
    CreateGameObject("camera", TYPE_3D, false);
    GetGameObjectByName("camera").AddComponent<CameraComponent>(new CameraComponent());
    GetGameObjectByName("camera").SetPosition({ 0, 0.5, -2 });

    CreateGameObject("placingModule");
    GetGameObjectByName("placingModule").SetPosition({ 0, 0, 1 });

    SetParent("camera", "placingModule");

	m_newIdGM = 0;
	m_camWalkSpeed = 1.f;
	m_camRunSpeed = 5.f;
	m_camSpeed = m_camWalkSpeed;
	// Test
	//player = GetGameObjectByName("placingModule");


}

void DevScene::Update(float deltatime)
{
	//Input

	//Movements
	if (InputManager::GetKeyIsPressed(VK_SHIFT)) 
	{
		m_camSpeed = m_camRunSpeed;
	}
	else
	{
		m_camSpeed = m_camWalkSpeed;
	}

	//Move
	if (InputManager::GetKeyIsPressed('Z'))
	{
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->position.z += m_camSpeed * deltatime;
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('S'))
	{
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->position.z -= m_camSpeed * deltatime;
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('Q'))
	{
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->position.x -= m_camSpeed * deltatime;
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('D'))
	{
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->position.x += m_camSpeed * deltatime;
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_SPACE))
	{
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->position.y += m_camSpeed * deltatime;
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_CONTROL))
	{
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->position.y -= m_camSpeed * deltatime;
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->dirty = true;
	}

	// Rotate
	if (InputManager::GetKeyIsPressed(VK_RIGHT))
	{
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->AddRotation(0.f,-100.f * deltatime,0.f);
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_LEFT))
	{
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->AddRotation(0.f, 100.f * deltatime, 0.f);
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_UP))
	{
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->AddRotation(100.f * deltatime, 0.f, 0.f);
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_DOWN))
	{
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->AddRotation(-100.f * deltatime, 0.f , 0.f);
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->dirty = true;
	}

	// Scale
	if (InputManager::GetKeyIsPressed(VK_ADD))
	{
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->scale.x += 1.f * deltatime;
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->scale.y += 1.f * deltatime;
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->scale.z += 1.f * deltatime;
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_SUBTRACT))
	{
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->scale.x -= 1.f * deltatime;
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->scale.y -= 1.f * deltatime;
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->scale.z -= 1.f * deltatime;
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->dirty = true;
	}

	// ChangeScene
    if (InputManager::GetKeyIsReleased('A'))
    {
        ChangeScene("SampleScene2");
    }

	// Adding blocks (make a function in this scene)
	if (InputManager::GetKeyIsReleased(VK_LBUTTON))
	{
		XMFLOAT3 posCamera = GetGameObjectByName("placingModule").GetPosition();
		XMFLOAT4 rotCamera = GetGameObjectByName("placingModule").GetRotation();
		XMFLOAT3 scaleCamera = GetGameObjectByName("placingModule").GetScale();

		std::string gmName = "GM" + std::to_string(m_newIdGM);

		CreateGameObject(gmName);
		GetGameObjectByName(gmName).SetPosition({ posCamera });
		GetGameObjectByName(gmName).SetRotation({ rotCamera });
		GetGameObjectByName(gmName).SetScale({ scaleCamera });

		GetGameObjectByName(gmName).SetTag(TAG_Object);

		std::string msg = "\nAdded " + gmName + " At[ X: " + std::to_string(GetGameObjectByName(gmName).GetPosition().x) + " Y: " + std::to_string(GetGameObjectByName(gmName).GetPosition().y) + " Z: " + std::to_string(GetGameObjectByName(gmName).GetPosition().z);
		OutputDebugStringA(msg.c_str());

		m_newIdGM++;
	}


	// Reset placing Module
	if (InputManager::GetKeyIsReleased(VK_F1))
	{
		GetGameObjectByName("placingModule").SetScale({ 1.f, 1.f, 1.f });
		GetGameObjectByName("placingModule").SetRotation({ 0.f, 0.f, 0.f,0.f });
		GetGameObjectByName("placingModule").GetComponent<TransformComponent>()->dirty = true;
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
				std::string cm_rotation = std::string("\nGetGameObjectByName(\"") + gm.GetName() + "\").SetRotation({ " + std::to_string(gm.GetRotation().w) + "," + std::to_string(gm.GetRotation().x) + "," + std::to_string(gm.GetRotation().y) + "," + std::to_string(gm.GetRotation().z) + " });";
				std::string cm_scale = std::string("\nGetGameObjectByName(\"") + gm.GetName() + "\").SetScale({ " + std::to_string(gm.GetScale().x) + "," + std::to_string(gm.GetScale().y) + "," + std::to_string(gm.GetScale().z) + " });";

				OutputDebugStringA(cm_create.c_str());
				OutputDebugStringA(cm_position.c_str());
				OutputDebugStringA(cm_rotation.c_str());
				OutputDebugStringA(cm_scale.c_str());
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

	if (InputManager::IsMouseLocked()) 
	{
		CenterLockCursor();
	}
}

void DevScene::Release()
{

}
