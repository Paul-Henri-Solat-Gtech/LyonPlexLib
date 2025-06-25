#include "pch.h"
#include "BlockTutoScene.h"

void BlockTutoScene::Start()
{
	CreateEntity("camera");
	AddComponent<CameraComponent>("camera", new CameraComponent());
	GetComponent<TransformComponent>("camera")->position = { 0, 0.5, -1 };




	CreateGameObject("parcelle1");
	GetGameObjectByName("parcelle1").SetPosition({ 51.792843, -1.916459, -76.895660 });
	GetGameObjectByName("parcelle1").SetScale({ 10, 1, 5 });

	CreateGameObject("parcelle2");
	GetGameObjectByName("parcelle2").SetPosition({ 51.792843, -1.916459, -68.895660 });
	GetGameObjectByName("parcelle2").SetScale({ 10, 1, 5 });

	CreateGameObject("parcelle3");
	GetGameObjectByName("parcelle3").SetPosition({ 51.792843, -1.916459, -60.895660 });
	GetGameObjectByName("parcelle3").SetScale({ 10, 1, 5 });

	CreateGameObject("parcelle4");
	GetGameObjectByName("parcelle4").SetPosition({ 51.792843, -1.916459, -54.895660 });
	GetGameObjectByName("parcelle4").SetScale({ 10, 1, 5 });

	CreateGameObject("parcelle5");
	GetGameObjectByName("parcelle5").SetPosition({ 51.792843, -1.916459, -46.895660 });
	GetGameObjectByName("parcelle5").SetScale({ 10, 1, 5 });



	CreateGameObject("parcelle6");
	GetGameObjectByName("parcelle6").SetPosition({ 36.792843, -1.916459, -60.895660 });
	GetGameObjectByName("parcelle6").SetScale({ 10, 1, 5 });

	CreateGameObject("parcelle7");
	GetGameObjectByName("parcelle7").SetPosition({ 36.792843, -1.916459, -54.895660 });
	GetGameObjectByName("parcelle7").SetScale({ 10, 1, 5 });

	CreateGameObject("parcelle8");
	GetGameObjectByName("parcelle8").SetPosition({ 36.792843, -1.916459, -46.895660 });
	GetGameObjectByName("parcelle8").SetScale({ 10, 1, 5 });





	CreateGameObject("maison");
	GetGameObjectByName("maison").SetPosition({ 36.792843, 1.916459, -71.895660 });
	GetGameObjectByName("maison").SetScale({ 10, 10, 10 });






	CreateGameObject("champ");
	GetGameObjectByName("champ").SetPosition({ 44.292843, -1.952915, -60.895660 });
	GetGameObjectByName("champ").SetScale({ 30, 1, 43 });
}

void BlockTutoScene::Update(float deltatime)
{
	//Input
	if (InputManager::GetKeyIsPressed('Z'))
	{
		//OutputDebugStringA("\nZ is pressed ! \n");
		//GetComponent<TransformComponent>("cube")->position.z += 10.f * deltatime;
		//GetComponent<TransformComponent>("cube")->dirty = true;
		GetComponent<TransformComponent>("camera")->position.z += 10.f * deltatime;
		GetComponent<TransformComponent>("camera")->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('S'))
	{
		//GetComponent<TransformComponent>("cube")->position.z -= 10.f * deltatime;
		//GetComponent<TransformComponent>("cube")->dirty = true;
		GetComponent<TransformComponent>("camera")->position.z -= 10.f * deltatime;
		GetComponent<TransformComponent>("camera")->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('Q'))
	{
		//GetComponent<TransformComponent>("cube")->position.x -= 10.f * deltatime;
		//GetComponent<TransformComponent>("cube")->dirty = true;
		GetComponent<TransformComponent>("camera")->position.x -= 10.f * deltatime;
		GetComponent<TransformComponent>("camera")->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('D'))
	{
		//GetComponent<TransformComponent>("cube")->position.x += 10.f * deltatime;
		//GetComponent<TransformComponent>("cube")->dirty = true;
		GetComponent<TransformComponent>("camera")->position.x += 10.f * deltatime;
		GetComponent<TransformComponent>("camera")->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_SPACE))
	{
		//GetComponent<TransformComponent>("cube")->position.y += 10.f * deltatime;
		//GetComponent<TransformComponent>("cube")->dirty = true;
		GetComponent<TransformComponent>("camera")->position.y += 10.f * deltatime;
		GetComponent<TransformComponent>("camera")->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_CONTROL))
	{
		//GetComponent<TransformComponent>("cube")->position.y -= 10.f * deltatime;
		//GetComponent<TransformComponent>("cube")->dirty = true;
		GetComponent<TransformComponent>("camera")->position.y -= 10.f * deltatime;
		GetComponent<TransformComponent>("camera")->dirty = true;

	}
	if (InputManager::GetKeyIsReleased('A'))
	{
		ChangeScene("GameScene");
	}
}

void BlockTutoScene::Release()
{
}
