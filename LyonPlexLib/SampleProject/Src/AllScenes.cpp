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

    // Create all textures
    CreateAllTextures();

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

void AllScenes::CreateAllTextures()
{
    auto& txtMngr = mp_gameManager->GetTextureManager();
    auto& meshMngr = mp_gameManager->GetMeshManager();

    txtMngr.LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");//0
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/Test.png");//1
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/TestBRAS.png");//2
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/grid.png");//3
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/NoTexture.png");//4
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/bois.jpg");//5
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/eau.jpg");//6
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/champ.jpg");//7
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/parcelle1.jpg");//8
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/parcelle2.jpg");//9
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/parcelle3.jpg");//10
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/parcelle4.jpg");//11
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/chemin_terre.jpg");//12
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/pierre.jpg");//13
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/herbe.jpg");//14
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/pont.jpg");//15
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/maison.png");//16
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/temple.jpg");//17
}
