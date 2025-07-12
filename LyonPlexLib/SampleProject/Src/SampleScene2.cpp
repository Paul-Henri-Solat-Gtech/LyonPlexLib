#include "pch.h"
#include "SampleScene2.h"

void SampleScene2::Start()
{
	//CreateEntity("camera");
	//AddComponent<CameraComponent>("camera", new CameraComponent());
	//GetComponent<TransformComponent>("camera")->position = { 0, 0.5, -1 };

	m_freeCam.Init(mp_ecsManager, mp_sceneManager->GetWindow());

	//CreateEntity("temple");
	//AddComponent<Type_3D_Transparent>("temple", new Type_3D_Transparent());
	//AddComponent<MeshComponent>("temple", new MeshComponent(MESHES::TEMPLE, TEXTURES::NOTEXTURE));
	////GetComponent<MeshComponent>("temple")->alpha = 0.5;
	//GetComponent<TransformComponent>("temple")->position = { 0, 0, 0 };
	//GetComponent<TransformComponent>("temple")->scale = { 1, 1, 1 };

	CreateEntity("cephaTree");
	AddComponent<Type_3D>("cephaTree", new Type_3D());
	AddComponent<MeshComponent>("cephaTree", new MeshComponent(MESHES::CEPHA1));
	GetComponent<TransformComponent>("cephaTree")->position = { -2, 0, 0 };
	GetComponent<TransformComponent>("cephaTree")->scale = { 0.5, 0.5, 0.5 };

	CreateEntity("stick");
	AddComponent<Type_3D>("stick", new Type_3D());
	AddComponent<MeshComponent>("stick", new MeshComponent(MESHES::STICK, TEXTURES::HERBE));
	GetComponent<TransformComponent>("stick")->position = { 0, 0, 0 };
	GetComponent<TransformComponent>("stick")->scale = { 1, 1, 1 };

	CreateEntity("TEST");
	AddComponent<Type_3D>("TEST", new Type_3D());
	AddComponent<MeshComponent>("TEST", new MeshComponent(MESHES::LOCAL_SQUARE, TEXTURES::NOTEXTURE));
	GetComponent<TransformComponent>("TEST")->position = { -1, 3, -3 };
	GetComponent<TransformComponent>("TEST")->scale = { 1, 1, 1 };

	CreateEntity("cubeEXT");
	AddComponent<Type_3D>("cubeEXT", new Type_3D());
	AddComponent<MeshComponent>("cubeEXT", new MeshComponent(5, TEXTURES::ARMS));
	GetComponent<TransformComponent>("cubeEXT")->position = { 0, 0, 0 };
	GetComponent<TransformComponent>("cubeEXT")->scale = { 1, 1, 0 };

	CreateEntity("bras");
	AddComponent<Type_2D>("bras", new Type_2D());
	AddComponent<MeshComponent>("bras", new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::ARMS));
	GetComponent<TransformComponent>("bras")->position = { 400, 500, 0 };
	GetComponent<TransformComponent>("bras")->scale = { 800, 500, 0 };
	GetComponent<TransformComponent>("bras")->SetRotation(0, 0, 180);
	GetComponent<TransformComponent>("bras")->dirty = true;


	CreateEntity("Light1");
	AddComponent<Type_3D>("Light1", new Type_3D());
	AddComponent<MeshComponent>("Light1", new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::BOIS));
	GetComponent<TransformComponent>("Light1")->position = { 0, 3, 0 };
	GetComponent<TransformComponent>("Light1")->scale = { 1, 1, 1 };
	AddComponent<LightComponent>("Light1", new LightComponent(1));
	GetComponent<LightComponent>("Light1")->color = { 1,1,1 };
	GetComponent<LightComponent>("Light1")->intensity = 1.0f;
	GetComponent<LightComponent>("Light1")->direction = { -1, -1, -1 };
	GetComponent<LightComponent>("Light1")->range = 500;

}

void SampleScene2::Update(float deltatime)
{
	//GetComponent<TransformComponent>("cube2D")->AddRotation(0 ,-20 * deltatime, 0);
	//GetComponent<TransformComponent>("temple")->AddRotation(0 ,15 * deltatime, 0);
	GetComponent<TransformComponent>("cephaTree")->AddRotation(0 ,50 * deltatime, 0);
	GetComponent<TransformComponent>("cubeEXT")->AddRotation(0 ,25 * deltatime, 0);
	GetComponent<TransformComponent>("Light1")->AddRotation(0 ,25 * deltatime, 0);

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

