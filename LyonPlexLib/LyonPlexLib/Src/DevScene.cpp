#include "pch.h"
#include "DevScene.h"

void DevScene::Start()
{
    CreateGameObject("camera", TYPE_3D, false);
    GetGameObjectByName("camera").AddComponent<CameraComponent>(new CameraComponent());
    GetGameObjectByName("camera").SetPosition({ 0, 0.5, -2 });

    CreateGameObject("placingModule");
	m_placingModule = GetGameObjectByName("placingModule");
    m_placingModule.SetPosition({ 0, 0, 1 });

    SetParent("camera", "placingModule");

	CreateGameObject("ground",2,3);
	GetGameObjectByName("ground").SetPosition({ 0, -2, 0 });
	GetGameObjectByName("ground").SetScale({ 50, 1, 50 });

	m_newIdGM = 0;
	m_camWalkSpeed = 1.f;
	m_camRunSpeed = 5.f;
	m_camSpeed = m_camWalkSpeed;
	// Test
	//player = m_placingModule;

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
		m_placingModule.GetComponent<TransformComponent>()->position.z += m_camSpeed * deltatime;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('S'))
	{
		m_placingModule.GetComponent<TransformComponent>()->position.z -= m_camSpeed * deltatime;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('Q'))
	{
		m_placingModule.GetComponent<TransformComponent>()->position.x -= m_camSpeed * deltatime;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('D'))
	{
		m_placingModule.GetComponent<TransformComponent>()->position.x += m_camSpeed * deltatime;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_SPACE))
	{
		m_placingModule.GetComponent<TransformComponent>()->position.y += m_camSpeed * deltatime;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_CONTROL))
	{
		m_placingModule.GetComponent<TransformComponent>()->position.y -= m_camSpeed * deltatime;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}

	// Rotate
	if (InputManager::GetKeyIsPressed(VK_RIGHT))
	{
		m_placingModule.GetComponent<TransformComponent>()->AddRotation(0.f,-100.f * deltatime,0.f);
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_LEFT))
	{
		m_placingModule.GetComponent<TransformComponent>()->AddRotation(0.f, 100.f * deltatime, 0.f);
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_UP))
	{
		m_placingModule.GetComponent<TransformComponent>()->AddRotation(100.f * deltatime, 0.f, 0.f);
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_DOWN))
	{
		m_placingModule.GetComponent<TransformComponent>()->AddRotation(-100.f * deltatime, 0.f , 0.f);
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}

	// Scale
	if (InputManager::GetKeyIsPressed(VK_ADD))
	{
		m_placingModule.GetComponent<TransformComponent>()->scale.x += m_camSpeed * deltatime;
		m_placingModule.GetComponent<TransformComponent>()->scale.y += m_camSpeed * deltatime;
		m_placingModule.GetComponent<TransformComponent>()->scale.z += m_camSpeed * deltatime;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_SUBTRACT))
	{
		m_placingModule.GetComponent<TransformComponent>()->scale.x -= m_camSpeed * deltatime;
		m_placingModule.GetComponent<TransformComponent>()->scale.y -= m_camSpeed * deltatime;
		m_placingModule.GetComponent<TransformComponent>()->scale.z -= m_camSpeed * deltatime;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}

	// ChangeScene
    if (InputManager::GetKeyIsReleased('A'))
    {
        ChangeScene("SampleScene2");
    }

	// Adding blocks (make a function in this scene)
	if (InputManager::GetKeyIsReleased(VK_LBUTTON))
	{
		XMFLOAT3 posCamera = m_placingModule.GetPosition();
		XMFLOAT4 rotCamera = m_placingModule.GetRotation();
		XMFLOAT3 scaleCamera = m_placingModule.GetScale();
		uint32_t meshID = m_placingModule.GetMesh();
		uint32_t textureID = m_placingModule.GetTexture();

		std::string gmName = "GM" + std::to_string(m_newIdGM);

		CreateGameObject(gmName, meshID, textureID);
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
		m_placingModule.SetScale({ 1.f, 1.f, 1.f });
		m_placingModule.SetRotation({ 0.f, 0.f, 0.f,0.f });
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
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
				//std::string cm_create = std::string("\nCreateGameObject(\"") + gm.GetName() + "\");";
				std::string cm_create = std::string("\nCreateGameObject(\"") + gm.GetName() + "\"" + "," + std::to_string(gm.GetMesh()) + "," + std::to_string(gm.GetTexture()) + ");";
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

	// Change type of gameobject (prototype)
	if (InputManager::GetKeyIsReleased('1'))
	{
		m_placingModule.SetTexture(4);
	}
	if (InputManager::GetKeyIsReleased('2'))
	{
		m_placingModule.SetTexture(1);
	}
	if (InputManager::GetKeyIsReleased('3'))
	{
		m_placingModule.SetTexture(3);
	}
}

void DevScene::Release()
{

}
