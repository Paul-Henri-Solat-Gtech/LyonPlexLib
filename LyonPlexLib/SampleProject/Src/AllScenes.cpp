#include "pch.h"
#include "AllScenes.h"

// Includes scenes here :
#include "SampleScene2.h"
#include "GameScene.h"
#include "BlockTutoScene.h"

// ..

void AllScenes::Init(GameManager* gameManager)
{
    mp_gameManager = gameManager;

    // Create all scenes
    CreateAllScenes();

    // START SCENE
    StartScene("SampleScene2");
    //StartScene("GameScene");
}

void AllScenes::CreateAllScenes()
{
    // Create new scenes
    //SampleScene2* newSampleScene2 = new SampleScene2();
    //mp_gameManager->GetSceneManager()->CreateScene(newSampleScene2, "SampleScene2");
    //GameScene* newGameScene = new GameScene();
    //mp_gameManager->GetSceneManager()->CreateScene(newGameScene, "GameScene");

    mp_gameManager->GetSceneManager()->RegisterScene("SampleScene2", []() { return new SampleScene2(); });
    mp_gameManager->GetSceneManager()->RegisterScene("BlockTutoScene", []() { return new BlockTutoScene(); });
    mp_gameManager->GetSceneManager()->RegisterScene("GameScene", []() { return new GameScene(); });

    // Demarrer la scene de depart
    mp_gameManager->GetSceneManager()->SetScene("GameScene");
}

void AllScenes::StartScene(std::string sceneName)
{
    // Set & Start scene
    mp_gameManager->GetSceneManager()->SetScene(sceneName);
}


