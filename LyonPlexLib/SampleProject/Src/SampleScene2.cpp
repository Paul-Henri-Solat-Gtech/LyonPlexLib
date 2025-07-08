#include "pch.h"
#include "SampleScene2.h"

void SampleScene2::Start()
{
	//OutputDebugStringA("\nHI ! I am sample scene. \n");



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


	CreateEntity("temple");
	AddComponent<Type_3D_Transparent>("temple", new Type_3D_Transparent());
	AddComponent<MeshComponent>("temple", new MeshComponent(MESHES::TEMPLE, TEXTURES::NOTEXTURE));
	//GetComponent<MeshComponent>("temple")->alpha = 0.5;
	GetComponent<TransformComponent>("temple")->position = { 0, 0, 0 };
	GetComponent<TransformComponent>("temple")->scale = { 1, 1, 1 };/*
	CreateEntity("temple");
	AddComponent<Type_3D>("temple", new Type_3D());
	AddComponent<MeshComponent>("temple", new MeshComponent(MESHES::TEMPLE, TEXTURES::NOTEXTURE));
	GetComponent<TransformComponent>("temple")->position = { 0, 0, 0 };
	GetComponent<TransformComponent>("temple")->scale = { 1, 1, 1 };*/

	CreateEntity("cephaTree");
	AddComponent<Type_3D>("cephaTree", new Type_3D());
	AddComponent<MeshComponent>("cephaTree", new MeshComponent(MESHES::CEPHA1, 19));
	GetComponent<TransformComponent>("cephaTree")->position = { -2, 0, 0 };
	GetComponent<TransformComponent>("cephaTree")->scale = { 0.5, 0.5, 0.5 };

	CreateEntity("TEST");
	AddComponent<Type_3D>("TEST", new Type_3D());
	AddComponent<MeshComponent>("TEST", new MeshComponent(MESHES::LOCAL_SQUARE, TEXTURES::NOTEXTURE));
	GetComponent<TransformComponent>("TEST")->position = { -1, 3, -3 };
	GetComponent<TransformComponent>("TEST")->scale = { 1, 1, 1 };

	CreateEntity("cubeEXT");
	AddComponent<Type_3D>("cubeEXT", new Type_3D());
	AddComponent<MeshComponent>("cubeEXT", new MeshComponent(5, TEXTURES::ARMS));
	GetComponent<TransformComponent>("cubeEXT")->position = { 2, 0, 0 };
	GetComponent<TransformComponent>("cubeEXT")->scale = { 1, 1, 0 };

	CreateEntity("bras");
	AddComponent<Type_2D>("bras", new Type_2D());
	AddComponent<MeshComponent>("bras", new MeshComponent(2, TEXTURES::ARMS));
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
	AddComponent<MeshComponent>("cube4", new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::BOIS));
	GetComponent<TransformComponent>("cube4")->position = { 0, 3, 0 };
	GetComponent<TransformComponent>("cube4")->scale = { 1, 1, 1 };
	/*AddComponent<LightComponent>("cube4", new LightComponent(0));
	GetComponent<LightComponent>("cube4")->color = { 1,1,1 };
	GetComponent<LightComponent>("cube4")->intensity = 1.0f;
	GetComponent<LightComponent>("cube4")->direction = { 0, -1, 0 };*/
}

void SampleScene2::Update(float deltatime)
{
	//GetComponent<TransformComponent>("cube2D")->AddRotation(0 ,-20 * deltatime, 0);
	//GetComponent<TransformComponent>("temple")->AddRotation(0 ,15 * deltatime, 0);
	GetComponent<TransformComponent>("cephaTree")->AddRotation(0 ,50 * deltatime, 0);
	GetComponent<TransformComponent>("cubeEXT")->AddRotation(0 ,25 * deltatime, 0);
	GetComponent<TransformComponent>("cube4")->AddRotation(0 ,25 * deltatime, 0);

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
	if (InputManager::GetKeyIsReleased('B'))
	{
		ChangeScene("BlockTutoScene");
	}
}

void SampleScene2::Release()
{

}

