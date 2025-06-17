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

    CreateEntity("cube3");
    AddComponent<Type_2D>("cube3", new Type_2D());
    AddComponent<MeshComponent>("cube3", new MeshComponent(2, 2));
    GetComponent<TransformComponent>("cube3")->position = { 300, 300, 0 };
    GetComponent<TransformComponent>("cube3")->scale = { 300, 300, 0 };
    GetComponent<TransformComponent>("cube3")->dirty = true;

    CreateEntity("cube4");
    AddComponent<Type_3D>("cube4", new Type_3D());
    AddComponent<MeshComponent>("cube4", new MeshComponent(2, 0));
    GetComponent<TransformComponent>("cube4")->position = { 1, 0, 3 };

    GetComponent<TransformComponent>("camera")->parent = { GetEntity("cube")->id };
}

void SampleScene2::Update(float deltatime)
{
    //Input
    if (InputManager::GetKeyIsPressed('Z'))
    {
        //OutputDebugStringA("\nZ is pressed ! \n");
        GetComponent<TransformComponent>("cube")->position.z += 1.f * deltatime;
        GetComponent<TransformComponent>("cube")->dirty = true;
    }
    if (InputManager::GetKeyIsPressed('S'))
    {
        GetComponent<TransformComponent>("cube")->position.z -= 1.f * deltatime;
        GetComponent<TransformComponent>("cube")->dirty = true;
    }
    if (InputManager::GetKeyIsPressed('Q'))
    {
        GetComponent<TransformComponent>("cube")->position.x -= 1.f * deltatime;
        GetComponent<TransformComponent>("cube")->dirty = true;
    }
    if (InputManager::GetKeyIsPressed('D'))
    {
        GetComponent<TransformComponent>("cube")->position.x += 1.f * deltatime;
        GetComponent<TransformComponent>("cube")->dirty = true;
    }
    if (InputManager::GetKeyIsPressed(VK_SPACE))
    {
        GetComponent<TransformComponent>("cube")->position.y += 1.f * deltatime;
        GetComponent<TransformComponent>("cube")->dirty = true;
    }
    if (InputManager::GetKeyIsPressed(VK_CONTROL))
    {
        GetComponent<TransformComponent>("cube")->position.y -= 1.f * deltatime;
        GetComponent<TransformComponent>("cube")->dirty = true;
        
    }
    if (InputManager::GetKeyIsReleased('A'))
    {
        ChangeScene("GameScene");
    }
}

void SampleScene2::Release()
{

}

