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
    StartScene("IntroScene");
    //StartScene("MainMenuScene");
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
    //Sounds
    mp_gameManager->GetSoundManager()->CreateSound("roar", L"../LyonPlexLib/Ressources/Roar.wav");
    mp_gameManager->GetSoundManager()->CreateSound("swordSlash1", L"../LyonPlexLib/Ressources/swordSlash1.wav");
    mp_gameManager->GetSoundManager()->CreateSound("swordSpecialSlash", L"../LyonPlexLib/Ressources/swordSpecialSlash.wav");
    mp_gameManager->GetSoundManager()->CreateSound("deathScream", L"../SampleProject/Ressources/Sounds/deathScreamBBB3.wav");
    mp_gameManager->GetSoundManager()->CreateSound("HUGH", L"../SampleProject/Ressources/Sounds/HUGH.wav");
    mp_gameManager->GetSoundManager()->CreateSound("BEAM", L"../SampleProject/Ressources/Sounds/beam.wav");
    mp_gameManager->GetSoundManager()->CreateSound("BIP", L"../SampleProject/Ressources/Sounds/bip.wav");
    mp_gameManager->GetSoundManager()->CreateSound("heal", L"../SampleProject/Ressources/Sounds/heal.wav");

    // Ennemis
    mp_gameManager->GetSoundManager()->CreateSound("Crabe_Degats", L"../SampleProject/Ressources/Sounds/Ennemis/Crabe_Degats.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Crabe_Degats_Lourds", L"../SampleProject/Ressources/Sounds/Ennemis/Crabe_Degats_Lourds.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Crabe_Mvmt", L"../SampleProject/Ressources/Sounds/Ennemis/Crabe_Mvmt.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Golem_Degats", L"../SampleProject/Ressources/Sounds/Ennemis/Golem_Degats.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Golem_Degats_Lourds", L"../SampleProject/Ressources/Sounds/Ennemis/Golem_Degats_Lourds.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Golem_Mvmt", L"../SampleProject/Ressources/Sounds/Ennemis/Golem_Mvmt.wav");

    // Enviro
    mp_gameManager->GetSoundManager()->CreateSound("Boulder", L"../SampleProject/Ressources/Sounds/Environment/Boulder.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Environment", L"../SampleProject/Ressources/Sounds/Environment/Environment_sound.wav");
    mp_gameManager->GetSoundManager()->CreateSound("River", L"../SampleProject/Ressources/Sounds/Environment/River_Sound.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Tree_cut", L"../SampleProject/Ressources/Sounds/Environment/Tree_cut.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Tree_fall", L"../SampleProject/Ressources/Sounds/Environment/Tree_fallSound.wav");

    // Weapons
    mp_gameManager->GetSoundManager()->CreateSound("WoodenSword", L"../SampleProject/Ressources/Sounds/Slash/Sound_Slash.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Hammer", L"../SampleProject/Ressources/Sounds/Slash/Sound_Weapon2.wav");
    
    //Musics
    mp_gameManager->GetSoundManager()->CreateSound("Corrosion", L"../LyonPlexLib/Ressources/Corrosion.wav");
    mp_gameManager->GetSoundManager()->CreateSound("ArmonizerTheme", L"../SampleProject/Ressources/Sounds/ArmonizerTheme.wav");
    mp_gameManager->GetSoundManager()->CreateSound("TheCrimsonTideClashArena", L"../SampleProject/Ressources/Sounds/TheCrimsonTideClashArena.wav");
    mp_gameManager->GetSoundManager()->CreateSound("TheCrimsonTideClashfight", L"../SampleProject/Ressources/Sounds/TheCrimsonTideClashfight.wav");
    mp_gameManager->GetSoundManager()->CreateSound("TheAlphaGolem", L"../SampleProject/Ressources/Sounds/TheAlphaGolem.wav");
}

