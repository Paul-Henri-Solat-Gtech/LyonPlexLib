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
	GetGameObjectByName("chemin3").SetPosition({ -147.232193,-1.791602,-60.108562 });
	GetGameObjectByName("chemin3").SetRotation({ 0.000000,0.159008,0.000000,0.987277 });
	GetGameObjectByName("chemin3").SetScale({ 12.261778,1.000000,17.289970 });
	CreateGameObject("chemin4", 2, 4);
	GetGameObjectByName("chemin4").SetPosition({ -154.086472,-1.791602,-56.157413 });
	GetGameObjectByName("chemin4").SetRotation({ 0.000000,0.369589,0.000000,0.929195 });
	GetGameObjectByName("chemin4").SetScale({ 12.261778,1.000000,17.289970 });
	CreateGameObject("chemin5", 2, 4);
	GetGameObjectByName("chemin5").SetPosition({ -159.983658,-1.791602,-48.708969 });
	GetGameObjectByName("chemin5").SetRotation({ 0.000000,0.491170,0.000000,0.871064 });
	GetGameObjectByName("chemin5").SetScale({ 12.261778,1.000000,17.289970 });
	CreateGameObject("chemin6", 2, 4);
	GetGameObjectByName("chemin6").SetPosition({ -163.272125,-1.791602,-40.477226 });
	GetGameObjectByName("chemin6").SetRotation({ 0.000000,0.621024,0.000000,0.783792 });
	GetGameObjectByName("chemin6").SetScale({ 12.261778,1.000000,17.289970 });
	CreateGameObject("chemin7", 2, 4);
	GetGameObjectByName("chemin7").SetPosition({ -163.920303,-1.791602,-11.829290 });
	GetGameObjectByName("chemin7").SetRotation({ 0.000000,0.714181,0.000000,0.699961 });
	GetGameObjectByName("chemin7").SetScale({ 48.603138,1.000000,17.289970 });
	CreateGameObject("temple", 2, 4);
	GetGameObjectByName("temple").SetPosition({ -163.533112,12.042871,30.696255 });
	GetGameObjectByName("temple").SetRotation({ 0.000000,0.714181,0.000000,0.699961 });
	GetGameObjectByName("temple").SetScale({ 43.701939,28.993061,46.056992 });
	CreateGameObject("sol_falaise1", 2, 4);
	GetGameObjectByName("sol_falaise1").SetPosition({ -154.179062,-1.289247,85.766991 });
	GetGameObjectByName("sol_falaise1").SetRotation({ 0.000000,0.714181,0.000000,0.699961 });
	GetGameObjectByName("sol_falaise1").SetScale({ 65.552933,2.552095,82.173508 });
	CreateGameObject("sol_falaise2", 2, 4);
	GetGameObjectByName("sol_falaise2").SetPosition({ -95.213821,0.792710,84.350952 });
	GetGameObjectByName("sol_falaise2").SetRotation({ -0.038456,0.713102,0.039237,0.698904 });
	GetGameObjectByName("sol_falaise2").SetScale({ 65.667862,2.552095,44.344215 });
	CreateGameObject("sol_falaise3", 2, 4);
	GetGameObjectByName("sol_falaise3").SetPosition({ -68.140533,5.718371,83.420593 });
	GetGameObjectByName("sol_falaise3").SetRotation({ -0.104059,0.706245,0.106173,0.692183 });
	GetGameObjectByName("sol_falaise3").SetScale({ 65.667862,2.552095,44.344215 });
	CreateGameObject("sol_falaise4", 2, 4);
	GetGameObjectByName("sol_falaise4").SetPosition({ -29.228916,14.561965,82.698311 });
	GetGameObjectByName("sol_falaise4").SetRotation({ -0.063842,0.711203,0.065139,0.697044 });
	GetGameObjectByName("sol_falaise4").SetScale({ 65.667862,2.552095,44.344215 });





	CreateGameObject("falaise_arriere1", 2, 4);
	GetGameObjectByName("falaise_arriere1").SetPosition({ -64.860374,6.561852,56.778175 });
	GetGameObjectByName("falaise_arriere1").SetRotation({ -0.177998,0.000000,0.000000,0.984031 });
	GetGameObjectByName("falaise_arriere1").SetScale({ 110.436554,-31.579859,-3.461195 });
	CreateGameObject("falaise_arriere2", 2, 4);
	GetGameObjectByName("falaise_arriere2").SetPosition({ -129.324753,4.646706,52.411228 });
	GetGameObjectByName("falaise_arriere2").SetRotation({ -0.202433,-0.220042,0.033374,0.953671 });
	GetGameObjectByName("falaise_arriere2").SetScale({ 24.185171,-31.579859,-3.461195 });








	CreateGameObject("falaise1", 2, 4);
	GetGameObjectByName("falaise1").SetPosition({ -94.317947,6.153999,21.011206 });
	GetGameObjectByName("falaise1").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("falaise1").SetScale({ 51.725380,32.509892,62.962383 });
	CreateGameObject("falaise2", 2, 4);
	GetGameObjectByName("falaise2").SetPosition({ -13.134092,5.834605,14.712330 });
	GetGameObjectByName("falaise2").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("falaise2").SetScale({ 62.403419,32.509892,44.804203 });





	CreateGameObject("bordure_falaise1", 2, 4);
	GetGameObjectByName("bordure_falaise1").SetPosition({ -13.350974,6.254149,-10.135196 });
	GetGameObjectByName("bordure_falaise1").SetRotation({ 0.089634,0.000000,0.000000,0.995975 });
	GetGameObjectByName("bordure_falaise1").SetScale({ 61.619911,31.739275,1.324951 });
	CreateGameObject("bordure_falaise2", 2, 4);
	GetGameObjectByName("bordure_falaise2").SetPosition({ -94.131599,6.254149,-12.966456 });
	GetGameObjectByName("bordure_falaise2").SetRotation({ 0.089634,0.000000,0.000000,0.995975 });
	GetGameObjectByName("bordure_falaise2").SetScale({ 52.049381,31.739275,1.324951 });
	CreateGameObject("bordure_falaise3", 2, 4);
	GetGameObjectByName("bordure_falaise3").SetPosition({ -122.394119,5.190633,19.562407 });
	GetGameObjectByName("bordure_falaise3").SetRotation({ -0.073755,-0.697653,-0.084566,0.707593 });
	GetGameObjectByName("bordure_falaise3").SetScale({ 59.848358,31.739275,1.324951 });




	CreateGameObject("riviere1", 2, 4);
	GetGameObjectByName("riviere1").SetPosition({ -56.037834,4.738580,14.733049 });
	GetGameObjectByName("riviere1").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("riviere1").SetScale({ 24.563875,32.157726,55.548630 });
	CreateGameObject("riviere2", 2, 4);
	GetGameObjectByName("riviere2").SetPosition({ -57.772491,-16.518198,-63.350914 });
	GetGameObjectByName("riviere2").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("riviere2").SetScale({ 15.549196,32.157726,55.548630 });
	CreateGameObject("riviere3", 2, 4);
	GetGameObjectByName("riviere3").SetPosition({ -54.636024,-16.518198,-25.446779 });
	GetGameObjectByName("riviere3").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("riviere3").SetScale({ 49.277706,32.157726,23.708309 });
	CreateGameObject("riviere4", 2, 4);
	GetGameObjectByName("riviere4").SetPosition({ 0.674132,4.739717,42.908764 });
	GetGameObjectByName("riviere4").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("riviere4").SetScale({ 135.462677,32.157726,14.368229 });





	CreateGameObject("arriere_falaise_bloc", 2, 4);
	GetGameObjectByName("arriere_falaise_bloc").SetPosition({ 30.165237,4.227498,83.066872 });
	GetGameObjectByName("arriere_falaise_bloc").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("arriere_falaise_bloc").SetScale({ 74.294655,35.368317,68.698074 });









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
