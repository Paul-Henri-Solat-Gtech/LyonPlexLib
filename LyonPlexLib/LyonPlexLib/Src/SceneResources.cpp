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

    txtMngr.LoadTexture("../LyonPlexLib/Ressources/NoTexture.png");//0
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");//1
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/Test.png");//2
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/TestBRAS.png");//3
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/grid.png");//4
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

    // Place single image up
    // Down is reserved for animations frame (to avoid redoing all enum)

    // IDLE ARM (24 frames)
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/NoWeapons/1.png"); //21
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
    // ATTACK 1 (16 frames)
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0000.png"); //44
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0001.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0002.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0003.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0004.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0005.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0006.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0007.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0008.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0009.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0010.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0011.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0012.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0013.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0014.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0015.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0016.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0017.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0018.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0019.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0020.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0021.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0022.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0023.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0024.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0025.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0026.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0027.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0028.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0029.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0030.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0031.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0032.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0033.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0034.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0035.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0036.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0037.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0038.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0039.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0040.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0041.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0042.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/LightWeapon/Lightweapon_attack1_0043.png"); //87
    }
    // ATTACK 2 (24 frames)
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0000.png"); //88
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0001.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0002.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0003.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0004.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0005.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0006.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0007.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0008.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0009.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0010.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0011.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0012.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0013.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0014.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0015.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0016.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0017.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0018.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0019.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0020.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0021.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0022.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0023.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0024.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/LightWeapon/Lightweapon_attack2_0025.png"); // 113

        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/1.png"); //88
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/2.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/3.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/4.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/5.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/6.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/7.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/8.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/9.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/10.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/11.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/12.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/13.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/14.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/15.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/16.png"); 
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/17.png"); 
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/18.png"); 
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/19.png"); 
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/20.png"); 
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/21.png"); 
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/22.png"); 
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/23.png"); 
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/24.png"); //84
    }
    // ATTACK 3 (17 frames)
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0000.png"); // 114
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0001.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0002.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0003.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0004.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0005.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0006.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0007.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0008.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0009.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0010.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0011.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0012.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0013.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0014.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0015.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0016.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0017.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0018.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0019.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0020.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0021.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0022.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0023.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0024.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0025.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0026.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0027.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0028.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0029.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0030.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0031.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0032.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0033.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0034.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0035.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0036.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0037.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0038.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/LightWeapon/Lightweapon_attack3_0039.png"); // 153

        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/1.png"); //85
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/2.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/3.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/4.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/5.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/6.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/7.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/8.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/9.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/10.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/11.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/12.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/13.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/14.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/15.png");
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/16.png"); //100
        //txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/17.png"); //100
    }


    return true;
}

bool SceneResources::InitImportedMeshResources(MeshManager& meshMngr)
{

    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/ArbreTest.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/Cepha1.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/Cube.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/TEMPLE.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/Maison.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/maison2.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/RockBig.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/RockLM1.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/RockLM2.obj");

    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/cepha_gros.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/cepha_petit.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/cypress_gros.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/cypress_petit.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/masitics.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/olivier.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/buisson_fleur.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/buisson_gros_fleur.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/buisson_gros.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/buisson_moyen_fleur.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/buisson_moyen.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/buisson_petit.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/cailloux_sol1.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/cailloux_sol2.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/cailloux_sol3.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/cailloux1.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/cailloux2.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/cailloux3.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/cailloux4.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Objets/Baton.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Environnement/Herbe.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Environnement/RouteDroite.obj");
    meshMngr.LoadMeshFromFile("../SampleProject/Ressources/Environnement3D/Environnement/RouteTournante.obj");


    return true;
}

bool SceneResources::InitLocalMeshResources(MeshManager& meshMngr)
{
    meshMngr.InitTriangle();
    meshMngr.InitSquare();
    meshMngr.InitCube();

    return true;
}
