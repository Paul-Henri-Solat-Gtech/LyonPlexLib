#include "pch.h"
#include "SampleScene2.h"

void SampleScene2::Start()
{
	//OutputDebugStringA("\nHI ! I am sample scene. \n");

	CreateEntity("camera");
	AddComponent<CameraComponent>("camera", new CameraComponent());
	GetComponent<TransformComponent>("camera")->position = { 0, 0.5, -1 };

	CreateEntity("cube");
	AddComponent<Type_3D>("cube", new Type_3D());
	AddComponent<MeshComponent>("cube", new MeshComponent(2, 0));
	GetComponent<TransformComponent>("cube")->position = { 0, 0, -1 };

	CreateEntity("cube2");
	AddComponent<Type_3D>("cube2", new Type_3D());
	AddComponent<MeshComponent>("cube2", new MeshComponent(2, 1));
	GetComponent<TransformComponent>("cube2")->position = { 1, 0, -1 };

	CreateEntity("bras");
	AddComponent<Type_2D>("bras", new Type_2D());
	AddComponent<MeshComponent>("bras", new MeshComponent(2, 2));
	GetComponent<TransformComponent>("bras")->position = { 400, 400, 0 };
	GetComponent<TransformComponent>("bras")->scale = { 1600, 1000, 0 };
	GetComponent<TransformComponent>("bras")->SetRotation(0, 0, 180);
	GetComponent<TransformComponent>("bras")->dirty = true;

	//CreateEntity("cube2D");
	//AddComponent<Type_2D>("cube2D", new Type_2D());
	//AddComponent<MeshComponent>("cube2D", new MeshComponent(2, 0));
	//GetComponent<TransformComponent>("cube2D")->position = { 400, 300, 0 };
	//GetComponent<TransformComponent>("cube2D")->scale = { 600, 600, 0 };
	////GetComponent<TransformComponent>("cube2D")->SetRotation(0 ,0, 0);
	//GetComponent<TransformComponent>("cube2D")->dirty = true;

	CreateEntity("cube4");
	AddComponent<Type_3D>("cube4", new Type_3D());
	AddComponent<MeshComponent>("cube4", new MeshComponent(2, 0));
	GetComponent<TransformComponent>("cube4")->position = { 1, 0, 3 };

	//GetComponent<TransformComponent>("camera")->parent = { GetEntity("cube")->id };
}

void SampleScene2::Update(float deltatime)
{
	//GetComponent<TransformComponent>("cube2D")->AddRotation(0 ,1, 0);

	//Input
	if (InputManager::GetKeyIsPressed('Z'))
	{
		//OutputDebugStringA("\nZ is pressed ! \n");
		GetComponent<TransformComponent>("cube")->position.z += 1.f * deltatime;
		GetComponent<TransformComponent>("cube")->dirty = true;
		GetComponent<TransformComponent>("camera")->position.z += 1.f * deltatime;
		GetComponent<TransformComponent>("camera")->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('S'))
	{
		GetComponent<TransformComponent>("cube")->position.z -= 1.f * deltatime;
		GetComponent<TransformComponent>("cube")->dirty = true;
		GetComponent<TransformComponent>("camera")->position.z -= 1.f * deltatime;
		GetComponent<TransformComponent>("camera")->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('Q'))
	{
		GetComponent<TransformComponent>("cube")->position.x -= 1.f * deltatime;
		GetComponent<TransformComponent>("cube")->dirty = true;
		GetComponent<TransformComponent>("camera")->position.x -= 1.f * deltatime;
		GetComponent<TransformComponent>("camera")->dirty = true;
	}
	if (InputManager::GetKeyIsPressed('D'))
	{
		GetComponent<TransformComponent>("cube")->position.x += 1.f * deltatime;
		GetComponent<TransformComponent>("cube")->dirty = true;
		GetComponent<TransformComponent>("camera")->position.x += 1.f * deltatime;
		GetComponent<TransformComponent>("camera")->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_SPACE))
	{
		GetComponent<TransformComponent>("cube")->position.y += 1.f * deltatime;
		GetComponent<TransformComponent>("cube")->dirty = true;
		GetComponent<TransformComponent>("camera")->position.y += 1.f * deltatime;
		GetComponent<TransformComponent>("camera")->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_CONTROL))
	{
		GetComponent<TransformComponent>("cube")->position.y -= 1.f * deltatime;
		GetComponent<TransformComponent>("cube")->dirty = true;
		GetComponent<TransformComponent>("camera")->position.y -= 1.f * deltatime;
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

