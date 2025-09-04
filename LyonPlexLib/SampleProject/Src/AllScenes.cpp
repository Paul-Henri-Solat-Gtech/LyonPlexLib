#include "pch.h"
#include "AllScenes.h"

// Includes scenes here :
#include "SampleScene2.h"
#include "GameScene.h"
#include "BlockTutoScene.h"
#include "MainMenuScene.h"
#include "IntroScene.h"
#include "ArenaScene.h"
// ..

void AllScenes::Init(GameManager* gameManager)
{
    mp_gameManager = gameManager;

    // Create all sounds
    InitAllSounds();

    // Create all scenes
    CreateAllScenes();

    // START SCENE
    //StartScene("SampleScene2");
    StartScene("IntroScene");
}

void AllScenes::CreateAllScenes()
{
    // Create new scenes
    //mp_gameManager->GetSceneManager()->RegisterScene("SampleScene2", []() { return new SampleScene2(); });
    mp_gameManager->GetSceneManager()->RegisterScene("BlockTutoScene", []() { return new BlockTutoScene(); });
    mp_gameManager->GetSceneManager()->RegisterScene("GameScene", []() { return new GameScene(); });
    mp_gameManager->GetSceneManager()->RegisterScene("MainMenuScene", []() { return new MainMenuScene(); });
    mp_gameManager->GetSceneManager()->RegisterScene("IntroScene", []() { return new IntroScene(); });
    mp_gameManager->GetSceneManager()->RegisterScene("ArenaScene", []() { return new ArenaScene(); });

}

void AllScenes::StartScene(std::string sceneName)
{
    // Set & Start scene
    mp_gameManager->GetSceneManager()->SetScene(sceneName);
}

void AllScenes::InitAllSounds() 
{
    mp_gameManager->GetSoundManager()->CreateSound("roar", L"../LyonPlexLib/Ressources/Roar.wav");
    mp_gameManager->GetSoundManager()->CreateSound("swordSlash1", L"../LyonPlexLib/Ressources/swordSlash1.wav");
    mp_gameManager->GetSoundManager()->CreateSound("swordSpecialSlash", L"../LyonPlexLib/Ressources/swordSpecialSlash.wav");
    mp_gameManager->GetSoundManager()->CreateSound("deathScream", L"../SampleProject/Ressources/Sounds/deathScreamBBB3.wav");
    mp_gameManager->GetSoundManager()->CreateSound("HUGH", L"../SampleProject/Ressources/Sounds/HUGH.wav");
    mp_gameManager->GetSoundManager()->CreateSound("BEAM", L"../SampleProject/Ressources/Sounds/beam.wav");
    mp_gameManager->GetSoundManager()->CreateSound("BIP", L"../SampleProject/Ressources/Sounds/bip.wav");
    mp_gameManager->GetSoundManager()->CreateSound("heal", L"../SampleProject/Ressources/Sounds/heal.wav");
}

