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

    std::string path;
#ifdef _DEBUG
    path = debugPath;
#else
    path = releasePath;
#endif

    //Sounds
    mp_gameManager->GetSoundManager()->CreateSound("roar", path + "Sounds/Roar.wav");
    mp_gameManager->GetSoundManager()->CreateSound("swordSlash1", path + "Sounds/swordSlash1.wav");
    mp_gameManager->GetSoundManager()->CreateSound("swordSpecialSlash", path + "Sounds/swordSpecialSlash.wav");
    mp_gameManager->GetSoundManager()->CreateSound("deathScream", path + "Sounds/deathScreamBBB3.wav");
    mp_gameManager->GetSoundManager()->CreateSound("HUGH", path + "Sounds/HUGH.wav");
    mp_gameManager->GetSoundManager()->CreateSound("BEAM", path + "Sounds/beam.wav");
    mp_gameManager->GetSoundManager()->CreateSound("BIP", path + "Sounds/bip.wav");
    mp_gameManager->GetSoundManager()->CreateSound("heal", path + "Sounds/heal.wav");

    // Player
    mp_gameManager->GetSoundManager()->CreateSound("walkGrass", path + "Sounds/Player/Footstep_Dirt_1.wav");
    mp_gameManager->GetSoundManager()->CreateSound("walkIndoors", path + "Sounds/Player/Footsteps_Temple_Reverb_1.wav");

    // Ennemis
    mp_gameManager->GetSoundManager()->CreateSound("Crabe_Degats", path + "Sounds/Ennemis/Crabe_Degats.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Crabe_Degats_Lourds", path + "Sounds/Ennemis/Crabe_Degats_Lourds.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Crabe_Mvmt", path + "Sounds/Ennemis/Crabe_Mvmt.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Golem_Degats", path + "Sounds/Ennemis/Golem_Degats.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Golem_Degats_Lourds", path + "Sounds/Ennemis/Golem_Degats_Lourds.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Golem_Mvmt", path + "Sounds/Ennemis/Golem_Mvmt.wav");

    // Enviro
    mp_gameManager->GetSoundManager()->CreateSound("Boulder", path + "Sounds/Environment/Boulder.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Environment", path + "Sounds/Environment/Environment_sound.wav");
    mp_gameManager->GetSoundManager()->CreateSound("River", path + "Sounds/Environment/River_Sound_1.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Tree_cut", path + "Sounds/Environment/Tree_cut.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Tree_fall", path + "Sounds/Environment/Tree_fallSound.wav");

    // Weapons
    mp_gameManager->GetSoundManager()->CreateSound("WoodenSword", path + "Sounds/Slash/Sound_Slash.wav");
    mp_gameManager->GetSoundManager()->CreateSound("Hammer", path + "Sounds/Slash/Sound_Weapon2.wav");
    mp_gameManager->GetSoundManager()->CreateSound("pop", path + "Sounds/pop.wav");
    
    //Musics
    mp_gameManager->GetSoundManager()->CreateSound("Corrosion", path + "Sounds/Corrosion.wav");
    mp_gameManager->GetSoundManager()->CreateSound("ArmonizerTheme", path + "Sounds/ArmonizerTheme.wav");
    mp_gameManager->GetSoundManager()->CreateSound("TheCrimsonTideClashArena", path + "Sounds/TheCrimsonTideClashArena.wav");
    mp_gameManager->GetSoundManager()->CreateSound("TheCrimsonTideClashfight", path + "Sounds/TheCrimsonTideClashfight.wav");
    mp_gameManager->GetSoundManager()->CreateSound("TheAlphaGolem", path + "Sounds/TheAlphaGolem.wav");
}

