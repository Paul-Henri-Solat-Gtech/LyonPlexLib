#include "pch.h"
#include "SceneResources.h"

bool SceneResources::Init(GameManager* gameManager)
{
    mp_gameManager = gameManager;

    auto& txtMngr = mp_gameManager->GetTextureManager();

    InitTextureResources(txtMngr);



    auto& meshMngr = mp_gameManager->GetMeshManager();

    InitLocalMeshResources(meshMngr);
    InitImportedMeshResources(meshMngr);

    meshMngr.BuildAndUploadGlobalBuffers();

    return true;
}

bool SceneResources::InitTextureResources(TextureManager& txtMngr)
{
    // WARNING : Dont forget to change the .h accordingly

    txtMngr.LoadTexture("../LyonPlexLib/Ressources/NoTexture.png");//1
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");//2
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/Test.png");//3
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/TestBRAS.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/grid.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/bois.jpg");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/eau.jpg");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/champ.jpg");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/parcelle1.jpg");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/parcelle2.jpg");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/parcelle3.jpg");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/parcelle4.jpg");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/chemin_terre.jpg");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/pierre.jpg");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/herbe.jpg");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/pont.jpg");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/maison.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/temple.jpg");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/Cepha1test.png");
    txtMngr.LoadTexture("../SampleProject/Ressources/icecream.png");//19
    txtMngr.LoadTexture("../SampleProject/Ressources/start.png");//20
    txtMngr.LoadTexture("../SampleProject/Ressources/stop.png");//21
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/heart-empty.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/heart-demi.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/heart-full.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/GameOver.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/Empty.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/weaponPlaceHolder.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/pauseMenuL.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/btnQuit.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/btnMainMenu.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/LyonPlexLogo.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/lightlp.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/groundmt.png");
    txtMngr.LoadTexture("../SampleProject/Ressources/portail.png");
    txtMngr.LoadTexture("../SampleProject/Ressources/titreV2.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/slash.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/zero.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/one.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/two.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/tree.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/four.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/five.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/six.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/seven.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/eight.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/nine.png");
    txtMngr.LoadTexture("../SampleProject/Ressources/btnStart.png");
    txtMngr.LoadTexture("../SampleProject/Ressources/btnArena.png");
    txtMngr.LoadTexture("../SampleProject/Ressources/closebtnV2.png");
    txtMngr.LoadTexture("../SampleProject/Ressources/testSkyboxV2.png");
    txtMngr.LoadTexture("../SampleProject/Ressources/healingrock.png");
    txtMngr.LoadTexture("../SampleProject/Ressources/bgArmonizer.png");
    txtMngr.LoadTexture("../SampleProject/Ressources/WINSCREEN.png");
    txtMngr.LoadTexture("../SampleProject/Ressources/LOSESCREEN.png");

    // CRABE IDLE
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/1.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/2.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/3.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/4.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/5.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/6.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/7.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/8.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/9.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/10.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/11.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/13.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/14.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/IDLE/15.png");
    }

    // CRABE WALK
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/WALK/1.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/WALK/2.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/WALK/3.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/WALK/4.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/WALK/5.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/WALK/6.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/WALK/7.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/WALK/8.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/WALK/9.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/WALK/10.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/WALK/11.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/WALK/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/WALK/13.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/WALK/14.png");
    }

    // CRABE ATTACK
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/1.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/2.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/3.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/4.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/5.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/6.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/7.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/8.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/9.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/10.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/11.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/13.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/14.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/15.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/16.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/17.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/18.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/19.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/20.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/21.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/22.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/23.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/24.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/25.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/26.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Crabe/ATTACK/27.png");
    }

    // GOLEM IDLE
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/1.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/2.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/3.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/4.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/5.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/6.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/7.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/8.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/9.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/10.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/11.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/13.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/14.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/15.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/16.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/17.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/18.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/19.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/IDLE/20.png");
    }

    // GOLEM WALK
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/1.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/2.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/3.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/4.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/5.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/6.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/7.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/8.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/9.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/10.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/11.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/13.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/14.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/15.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/16.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/17.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/18.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/19.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/20.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/21.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/22.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/23.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/24.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/25.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/26.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/27.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/28.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/29.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/30.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/31.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/32.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/33.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/34.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/35.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/WALK/36.png");
    }

    // GOLEM ATTACK
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/1.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/2.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/3.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/4.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/5.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/6.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/7.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/8.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/9.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/10.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/11.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/13.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/14.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/15.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/16.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/17.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/18.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/19.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/20.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/21.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/22.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/23.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/24.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/25.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Enemies/Golem/ATTACK/26.png");
    }

    // IDLE ARM (24 frames)
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/1.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/2.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/3.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/4.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/5.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/6.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/7.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/8.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/9.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/10.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/11.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/13.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/14.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/15.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/16.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/17.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/18.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/19.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/20.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/21.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/22.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/23.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/24.png"); //43
    }
    // IDLE ARM WEAPON 1
    {
        //-v2
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/1.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/2.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/3.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/4.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/5.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/6.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/7.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/8.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/9.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/10.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/11.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/13.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/14.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/15.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/IDLE/16.png");
    }
    // ATTACK 1 WEAPON 1
    {
        //--v2
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/1.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/2.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/3.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/4.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/5.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/6.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/7.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/8.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/9.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/10.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/11.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/13.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/14.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/15.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/16.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/17.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/18.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/19.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/20.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/21.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/22.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/23.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/24.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/25.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/26.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/27.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK1/28.png");
    }
    // ATTACK 2 WEAPON 1
    {
        //-v2
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/1.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/2.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/3.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/4.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/5.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/6.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/7.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/8.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/9.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/10.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/11.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/13.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/14.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/15.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/16.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/17.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK2/18.png");

    }
    // ATTACK 3 WEAPON 1
    {
        //-v2
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/1.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/2.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/3.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/4.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/5.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/6.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/7.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/8.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/9.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/10.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/11.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/13.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/14.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/15.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/16.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/17.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/18.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/19.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/20.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/21.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Player/LightWeapon/ATK3/22.png");
    }

    // IDLE ARM WEAPON 2 (11 frames)
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/AmalgateWeapon/Heavyweapon_idle_0000.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/AmalgateWeapon/Heavyweapon_idle_0001.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/AmalgateWeapon/Heavyweapon_idle_0002.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/AmalgateWeapon/Heavyweapon_idle_0003.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/AmalgateWeapon/Heavyweapon_idle_0004.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/AmalgateWeapon/Heavyweapon_idle_0005.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/AmalgateWeapon/Heavyweapon_idle_0006.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/AmalgateWeapon/Heavyweapon_idle_0007.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/AmalgateWeapon/Heavyweapon_idle_0008.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/AmalgateWeapon/Heavyweapon_idle_0009.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/AmalgateWeapon/Heavyweapon_idle_0010.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/AmalgateWeapon/Heavyweapon_idle_0011.png");
    }

    // ATTACK 1 WEAPON 2 (16 frames)
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0000.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0001.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/HeavyWeapon_attack1_0002.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/HeavyWeapon_attack1_0003.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/HeavyWeapon_attack1_0004.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/HeavyWeapon_attack1_0005.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/HeavyWeapon_attack1_0006.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/HeavyWeapon_attack1_0007.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0008.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0009.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0010.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0011.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0012.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0013.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0014.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0015.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0016.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0017.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0018.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0019.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0020.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0021.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0022.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0023.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0024.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0025.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0026.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0027.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0028.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0029.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0030.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0031.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0032.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0033.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0034.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0035.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0036.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0037.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0038.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0039.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0040.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0041.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/HeavyWeapon/Heavyweapon_attack1_0042.png");
    }
    
    // ATTACK 2 WEAPON 2 (16 frames)
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0000.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0001.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/HeavyWeapon_attack2_0002.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/HeavyWeapon_attack2_0003.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/HeavyWeapon_attack2_0004.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/HeavyWeapon_attack2_0005.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/HeavyWeapon_attack2_0006.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/HeavyWeapon_attack2_0007.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0008.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0009.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0010.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0011.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0012.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0013.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0014.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0015.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0016.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0017.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0018.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0019.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0020.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0021.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0022.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0023.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0024.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0025.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0026.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0027.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0028.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0029.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0030.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0031.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0032.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0033.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0034.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0035.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0036.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0037.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0038.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0039.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0040.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0041.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0042.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0043.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0044.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/HeavyWeapon/Heavyweapon_attack2_0045.png");
    }
    
    // ATTACK 3 WEAPON 2 (16 frames)
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0000.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0001.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/HeavyWeapon_attack3_0002.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/HeavyWeapon_attack3_0003.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/HeavyWeapon_attack3_0004.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/HeavyWeapon_attack3_0005.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/HeavyWeapon_attack3_0006.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/HeavyWeapon_attack3_0007.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0008.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0009.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0010.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0011.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0012.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0013.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0014.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0015.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0016.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0017.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0018.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0019.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0020.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0021.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0022.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0023.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/HeavyWeapon/Heavyweapon_attack3_0024.png");
    }



    // Water Maps
    //txtMngr.LoadTexture("../SampleProject/Ressources/Environnement3D/Water/WaterNormal.dds");
    //txtMngr.LoadCubeTexture("../SampleProject/Ressources/Environnement3D/Water/EnvMap.dds");


    return true;
}

bool SceneResources::InitImportedMeshResources(MeshManager& meshMngr)
{
    // A MODIFIER
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/Maison.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Objets/Baton.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Environnement/Herbe.obj");

    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Batiments/Temple.obj");

    
    // NOUVEAUX
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Bushes/Fleur.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Bushes/BigFL.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Bushes/Big.obj");    //20
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Bushes/MediumFL.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Bushes/Medium.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Bushes/little.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Rocks/Path1.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Rocks/Path2.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Rocks/Path3.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Rocks/RockBig.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Rocks/RockLM1.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Rocks/RockLM2.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Rocks/RockLM3.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Rocks/RockMedium.obj");//30



    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Environnement/Map.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Lianes/LIANE1.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Lianes/LIANE2.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Lianes/LIANE3.obj");

    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Trees/Cepha1.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Trees/Cepha2.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Trees/Cypress1.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Trees/Cypress2.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Trees/Mastic1.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Trees/Mastic2.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Trees/olivier_tronc.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Trees/olivier_sup.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Trees/Olive2.obj");

    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Batiments/PONT.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Batiments/POTEAU_INTACT.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Batiments/POTEAU_BRISE.obj");

    return true;
}

bool SceneResources::InitLocalMeshResources(MeshManager& meshMngr)
{
    meshMngr.InitTriangle();
    meshMngr.InitSquare();
    meshMngr.InitCube();
    meshMngr.InitSphere();

    return true;
}
