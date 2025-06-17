#include "pch.h"
#include "GameScene.h"

void GameScene::Start()
{
    CreateEntity("camera");
    AddComponent<CameraComponent>("camera", new CameraComponent());
    GetComponent<TransformComponent>("camera")->position = { 0, 0, -1 };

    CreateEntity("cube");
    AddComponent<MeshComponent>("cube", new MeshComponent(2, 0));
    GetComponent<TransformComponent>("cube")->position = { 0, 0, -1 };

    CreateEntity("cube4");
    AddComponent<Type_3D>("cube4", new Type_3D());
    AddComponent<MeshComponent>("cube4", new MeshComponent(2, 0));
    GetComponent<TransformComponent>("cube4")->position = { 1, 0, 3 };

    //CreateGameObject("testGm");
    //GetGameObjectByName("testGm").GetComponent<TransformComponent>()->position = { 1, 1, 4 };

    CreateGameObject("testGm");
    GetGameObjectByName("testGm").SetPosition({ 2, 1, 3 });

    GetComponent<TransformComponent>("camera")->parent = { GetEntity("cube")->id };
}

void GameScene::Update(float deltatime)
{
    if (InputManager::GetKeyIsReleased('A'))
    {
        ChangeScene("SampleScene2");
    }
}

void GameScene::Release()
{
}
