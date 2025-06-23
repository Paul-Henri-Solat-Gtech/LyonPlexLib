#include "pch.h"
#include "SampleScene2.h"

void SampleScene2::Start()
{
	//OutputDebugStringA("\nHI ! I am sample scene. \n");

	auto& txtMngr = mp_sceneManager->GetGameManager()->GetTextureManager();
	auto& meshMngr = mp_sceneManager->GetGameManager()->GetMeshManager();

	txtMngr.LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");
	txtMngr.LoadTexture("../LyonPlexLib/Ressources/Test.png");
	txtMngr.LoadTexture("../LyonPlexLib/Ressources/TestBRAS.png");
	txtMngr.LoadTexture("../LyonPlexLib/Ressources/grid.png");

	Entity tree = { -1 };

	//meshMngr.LoadObjMesh("../LyonPlexLib/Ressources/ArbreTest.obj", tree.id);

	//for (int i = 0; i < 5; i++) 
	//{
	//	Entity newEntity = mp_ecsManager->CreateEntity();
	//	mp_ecsManager->AddComponent<TransformComponent>(newEntity, new TransformComponent());
	//	mp_ecsManager->GetComponent<TransformComponent>(newEntity)->position = { i * 1.5f, 0, 0 };
	//	mp_ecsManager->AddComponent<Type_3D>(newEntity, new Type_3D());
	//	mp_ecsManager->AddComponent<MeshComponent>(newEntity, new MeshComponent(2, 0));
	//}

	CreateEntity("camera");
	AddComponent<CameraComponent>("camera", new CameraComponent());
	GetComponent<TransformComponent>("camera")->position = { 0, 0.5, -1 };

	CreateEntity("cube");
	AddComponent<Type_3D>("cube", new Type_3D());
	AddComponent<MeshComponent>("cube", new MeshComponent(2, 0));
	GetComponent<TransformComponent>("cube")->position = { 0, 0, -1 };

	CreateEntity("cube2");
	//AddComponent<Type_2D5>("cube2", new Type_2D5());
	AddComponent<Type_3D>("cube2", new Type_3D());
	AddComponent<MeshComponent>("cube2", new MeshComponent(3, 0));
	GetComponent<TransformComponent>("cube2")->position = { 0, 0, 0 };
	GetComponent<TransformComponent>("cube2")->scale = { 0.5, 0.5, 0.5 };

	CreateEntity("bras");
	AddComponent<Type_2D>("bras", new Type_2D());
	AddComponent<MeshComponent>("bras", new MeshComponent(2, 2));
	GetComponent<TransformComponent>("bras")->position = { 400, 500, 0 };
	GetComponent<TransformComponent>("bras")->scale = { 800, 500, 0 };
	GetComponent<TransformComponent>("bras")->SetRotation(0, 0, 180);
	GetComponent<TransformComponent>("bras")->dirty = true;

	CreateEntity("cube2D");
	AddComponent<Type_2D>("cube2D", new Type_2D());
	AddComponent<MeshComponent>("cube2D", new MeshComponent(2, 0));
	GetComponent<TransformComponent>("cube2D")->position = { 400, 300, 0 };
	GetComponent<TransformComponent>("cube2D")->scale = { 80, 60, 0 };
	//GetComponent<TransformComponent>("cube2D")->SetRotation(0 ,0, 0);
	GetComponent<TransformComponent>("cube2D")->dirty = true;

	CreateEntity("cube4");
	AddComponent<Type_3D>("cube4", new Type_3D());
	AddComponent<MeshComponent>("cube4", new MeshComponent(2, 0));
	GetComponent<TransformComponent>("cube4")->position = { 0, 0, 0 };

	GetComponent<TransformComponent>("camera")->parent = { GetEntity("cube")->id };
}

void SampleScene2::Update(float deltatime)
{
	GetComponent<TransformComponent>("cube2D")->AddRotation(0 ,-20 * deltatime, 0);
	GetComponent<TransformComponent>("cube2")->AddRotation(0 ,15 * deltatime, 0);

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

void SampleScene2::Release()
{

}

