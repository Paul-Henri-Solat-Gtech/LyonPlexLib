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











	CreateGameObject("chemin1", 2, 4);
	GetGameObjectByName("chemin1").SetPosition({ -8.714675,-1.933910,-61.310471 });
	GetGameObjectByName("chemin1").SetRotation({ 1.000000,0.000000,0.000000,0.000000 });
	GetGameObjectByName("chemin1").SetScale({ 75.578575,1.258187,17.168396 });


	CreateGameObject("chemin2", 2, 4);
	GetGameObjectByName("chemin2").SetPosition({ -106.625977,-1.933910,-61.581860 });
	GetGameObjectByName("chemin2").SetRotation({ 1.000000,0.000000,0.000000,0.000000 });
	GetGameObjectByName("chemin2").SetScale({ 75.578575,1.258187,17.168396 });




	CreateGameObject("pont", 2, 4);
	GetGameObjectByName("pont").SetPosition({ -57.737553,-0.460670,-61.557228 });
	GetGameObjectByName("pont").SetRotation({ 1.000000,0.000000,0.000000,0.000000 });
	GetGameObjectByName("pont").SetScale({ 22.520617,4.305717,17.147631 });




	CreateGameObject("chemin3", 2, 4);
	GetGameObjectByName("chemin3").SetPosition({ -147.938324,-1.791484,-60.287571 });
	GetGameObjectByName("chemin3").SetRotation({ 0.991285,0.000000,0.131738,0.000000 });
	GetGameObjectByName("chemin3").SetScale({ 13.040899,1.000000,16.946362 });
	CreateGameObject("chemin4", 2, 4);
	GetGameObjectByName("chemin4").SetPosition({ -155.854523,-1.791484,-56.247593 });
	GetGameObjectByName("chemin4").SetRotation({ 0.939115,0.000000,0.343603,0.000000 });
	GetGameObjectByName("chemin4").SetScale({ 13.040899,1.000000,16.946362 });
	CreateGameObject("chemin5", 2, 4);
	GetGameObjectByName("chemin5").SetPosition({ -162.549118,-1.791484,-48.833179 });
	GetGameObjectByName("chemin5").SetRotation({ 0.885591,0.000000,0.464467,0.000000 });
	GetGameObjectByName("chemin5").SetScale({ 13.040899,1.000000,16.946362 });
	CreateGameObject("chemin6", 2, 4);
	GetGameObjectByName("chemin6").SetPosition({ -166.592896,-1.791484,-40.391773 });
	GetGameObjectByName("chemin6").SetRotation({ 0.792439,0.000000,0.609951,0.000000 });
	GetGameObjectByName("chemin6").SetScale({ 13.040899,1.000000,16.946362 });
	CreateGameObject("chemin7", 2, 4);
	GetGameObjectByName("chemin7").SetPosition({ -165.851974,-1.791484,-13.364552 });
	GetGameObjectByName("chemin7").SetRotation({ 0.680958,0.000000,0.732322,0.000000 });
	GetGameObjectByName("chemin7").SetScale({ 46.794952,1.000000,16.946362 });




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
