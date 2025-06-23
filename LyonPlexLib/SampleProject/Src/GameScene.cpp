#include "pch.h"
#include "GameScene.h"

void GameScene::Start()
{
    CreateGameObject("camera2");
    GetGameObjectByName("camera2").AddComponent<CameraComponent>(new CameraComponent());
    GetGameObjectByName("camera2").SetPosition({ 0, 0.5, -1 });
    
    CreateGameObject("cube2");
    GetGameObjectByName("cube2").SetPosition({ 0, 0, -1 });

    CreateGameObject("testGm");
    GetGameObjectByName("testGm").SetPosition({ 2, 1, 3 });

    SetParent("camera2", "cube2");
}

void GameScene::Update(float deltatime)
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
        ChangeScene("DevScene");
    }
}

void GameScene::Release()
{
}
