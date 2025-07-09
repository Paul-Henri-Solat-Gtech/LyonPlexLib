#include "pch.h"
#include "SampleScene2.h"

void SampleScene2::Start()
{
	Entity tree = { -1 };

	//CreateEntity("camera");
	//AddComponent<CameraComponent>("camera", new CameraComponent());
	//GetComponent<TransformComponent>("camera")->position = { 0, 0.5, -1 };

	m_freeCam.Init(mp_ecsManager, mp_sceneManager->GetWindow());

	CreateEntity("tree1");
	AddComponent<Type_3D_Transparent>("tree1", new Type_3D_Transparent());
	AddComponent<MeshComponent>("tree1", new MeshComponent(MESHES::TEMPLE, TEXTURES::NOTEXTURE));
	GetComponent<MeshComponent>("tree1")->alpha = 0.5;
	GetComponent<TransformComponent>("tree1")->position = { 0, 0, 0 };
	GetComponent<TransformComponent>("tree1")->scale = { 1, 1, 1 };/*
	CreateEntity("tree1");
	AddComponent<Type_3D>("tree1", new Type_3D());
	AddComponent<MeshComponent>("tree1", new MeshComponent(MESHES::TEMPLE, TEXTURES::NOTEXTURE));
	GetComponent<TransformComponent>("tree1")->position = { 0, 0, 0 };
	GetComponent<TransformComponent>("tree1")->scale = { 1, 1, 1 };*/

	CreateEntity("tree2");
	AddComponent<Type_3D>("tree2", new Type_3D());
	AddComponent<MeshComponent>("tree2", new MeshComponent(MESHES::CEPHA1, TEXTURES::NOTEXTURE));
	GetComponent<TransformComponent>("tree2")->position = { -2, 0, 0 };
	GetComponent<TransformComponent>("tree2")->scale = { 0.5, 0.5, 0.5 };

	CreateEntity("TEST");
	AddComponent<Type_3D>("TEST", new Type_3D());
	AddComponent<MeshComponent>("TEST", new MeshComponent(MESHES::LOCAL_SQUARE, TEXTURES::NOTEXTURE));
	GetComponent<TransformComponent>("TEST")->position = { -1, 3, -3 };
	GetComponent<TransformComponent>("TEST")->scale = { 1, 1, 1 };

	CreateEntity("cubeEXT");
	AddComponent<Type_3D>("cubeEXT", new Type_3D());
	AddComponent<MeshComponent>("cubeEXT", new MeshComponent(5, 5));
	GetComponent<TransformComponent>("cubeEXT")->position = { 2, 0, 0 };
	GetComponent<TransformComponent>("cubeEXT")->scale = { 0.5, 0.5, 0 };

	CreateEntity("bras");
	AddComponent<Type_2D>("bras", new Type_2D());
	AddComponent<MeshComponent>("bras", new MeshComponent(2, 2));
	GetComponent<TransformComponent>("bras")->position = { 400, 500, 0 };
	GetComponent<TransformComponent>("bras")->scale = { 800, 500, 0 };
	GetComponent<TransformComponent>("bras")->SetRotation(0, 0, 180);
	GetComponent<TransformComponent>("bras")->dirty = true;

	//CreateEntity("cube2D");
	//AddComponent<Type_2D>("cube2D", new Type_2D());
	//AddComponent<MeshComponent>("cube2D", new MeshComponent(MESHES::LOCAL_SQUARE, 0));
	//GetComponent<TransformComponent>("cube2D")->position = { 400, 300, 0 };
	//GetComponent<TransformComponent>("cube2D")->scale = { 80, 60, 0 };
	////GetComponent<TransformComponent>("cube2D")->SetRotation(0 ,0, 0);
	//GetComponent<TransformComponent>("cube2D")->dirty = true;

	CreateEntity("cube4");
	AddComponent<Type_3D>("cube4", new Type_3D());
	AddComponent<MeshComponent>("cube4", new MeshComponent(2, 0));
	GetComponent<TransformComponent>("cube4")->position = { 0, 0, 0 };
}

void SampleScene2::Update(float deltatime)
{
	//GetComponent<TransformComponent>("cube2D")->AddRotation(0 ,-20 * deltatime, 0);
	//GetComponent<TransformComponent>("tree1")->AddRotation(0 ,15 * deltatime, 0);
	GetComponent<TransformComponent>("tree2")->AddRotation(0 ,50 * deltatime, 0);
	GetComponent<TransformComponent>("cubeEXT")->AddRotation(0 ,25 * deltatime, 0);

	//Input
	m_freeCam.Update(deltatime);
	//if (InputManager::GetKeyIsPressed('Z'))
	//{
	//	//OutputDebugStringA("\nZ is pressed ! \n");
	//	//GetComponent<TransformComponent>("cube")->position.z += 10.f * deltatime;
	//	//GetComponent<TransformComponent>("cube")->dirty = true;
	//	GetComponent<TransformComponent>("camera")->position.z += 10.f * deltatime;
	//	GetComponent<TransformComponent>("camera")->dirty = true;
	//}
	//if (InputManager::GetKeyIsPressed('S'))
	//{
	//	//GetComponent<TransformComponent>("cube")->position.z -= 10.f * deltatime;
	//	//GetComponent<TransformComponent>("cube")->dirty = true;
	//	GetComponent<TransformComponent>("camera")->position.z -= 10.f * deltatime;
	//	GetComponent<TransformComponent>("camera")->dirty = true;
	//}
	//if (InputManager::GetKeyIsPressed('Q'))
	//{
	//	//GetComponent<TransformComponent>("cube")->position.x -= 10.f * deltatime;
	//	//GetComponent<TransformComponent>("cube")->dirty = true;
	//	GetComponent<TransformComponent>("camera")->position.x -= 10.f * deltatime;
	//	GetComponent<TransformComponent>("camera")->dirty = true;
	//}
	//if (InputManager::GetKeyIsPressed('D'))
	//{
	//	//GetComponent<TransformComponent>("cube")->position.x += 10.f * deltatime;
	//	//GetComponent<TransformComponent>("cube")->dirty = true;
	//	GetComponent<TransformComponent>("camera")->position.x += 10.f * deltatime;
	//	GetComponent<TransformComponent>("camera")->dirty = true;
	//}
	//if (InputManager::GetKeyIsPressed(VK_SPACE))
	//{
	//	//GetComponent<TransformComponent>("cube")->position.y += 10.f * deltatime;
	//	//GetComponent<TransformComponent>("cube")->dirty = true;
	//	GetComponent<TransformComponent>("camera")->position.y += 10.f * deltatime;
	//	GetComponent<TransformComponent>("camera")->dirty = true;
	//}
	//if (InputManager::GetKeyIsPressed(VK_CONTROL))
	//{
	//	//GetComponent<TransformComponent>("cube")->position.y -= 10.f * deltatime;
	//	//GetComponent<TransformComponent>("cube")->dirty = true;
	//	GetComponent<TransformComponent>("camera")->position.y -= 10.f * deltatime;
	//	GetComponent<TransformComponent>("camera")->dirty = true;

	//}
	if (InputManager::GetKeyIsReleased('A'))
	{
		ChangeScene("GameScene");
	}
	if (InputManager::GetKeyIsReleased('B'))
	{
		ChangeScene("BlockTutoScene");
	}
}

void SampleScene2::Release()
{

}

