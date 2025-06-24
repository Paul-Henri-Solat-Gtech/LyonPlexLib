#include "pch.h"
#include "DevScene.h"

void DevScene::Start()
{
    CreateGameObject("camera", TYPE_3D, false);
    GetGameObjectByName("camera").AddComponent<CameraComponent>(new CameraComponent());
    GetGameObjectByName("camera").SetPosition({ 0, 0.5, -2 });

    CreateGameObject("cube2");
    GetGameObjectByName("cube2").SetPosition({ 0, 0, -1 });

    SetParent("camera", "cube2");

	newIdGM = 0;
	
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
		auto* a = GetGameObjectByName("placingModule").GetComponent<TransformComponent>();
		a->scale.x += 1.f * deltatime;
		a->scale.y += 1.f * deltatime;
		a->scale.z += 1.f * deltatime;
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

	// Adding blocks
	if (InputManager::GetKeyIsReleased(VK_LBUTTON))
	{
		XMFLOAT3 posCamera = GetGameObjectByName("cube2").GetPosition();
		std::string gmName = "GM" + std::to_string(newIdGM);

		CreateGameObject(gmName);
		GetGameObjectByName(gmName).SetPosition({ posCamera });
		GetGameObjectByName(gmName).SetTag(TAG_Object);

		std::string msg = "\nAdded " + gmName + " At[ X: " + std::to_string(GetGameObjectByName(gmName).GetPosition().x) + " Y: " + std::to_string(GetGameObjectByName(gmName).GetPosition().y) + " Z: " + std::to_string(GetGameObjectByName(gmName).GetPosition().z);
		OutputDebugStringA(msg.c_str());


		newIdGM++;
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
				auto& gameObj = GetSceneGameObjects().back();
				m_lastPlacedGmName = gameObj.GetName();
				m_lastPlacedGmPos = gameObj.GetPosition();

				std::string msg = "\nRemoved " + m_lastPlacedGmName + " At[ X: " + std::to_string(m_lastPlacedGmPos.x) + " Y: " + std::to_string(m_lastPlacedGmPos.y) + " Z: " + std::to_string(m_lastPlacedGmPos.z);
				OutputDebugStringA(msg.c_str());

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
>>>>>>> Stashed changes
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
}

void DevScene::Release()
{

}
