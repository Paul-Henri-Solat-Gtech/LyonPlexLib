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
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/1.png"); //21
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/2.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/3.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/4.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/5.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/6.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/7.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/8.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/9.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/10.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/11.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/13.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/14.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/15.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/16.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/17.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/18.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/19.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/20.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/21.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/22.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/23.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/24.png"); //43
    }
    // ATTACK 1 (16 frames)
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/1.png"); //44
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/2.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/3.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/4.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/5.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/6.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/7.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/8.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/9.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/10.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/11.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/13.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/14.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/15.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack1/16.png"); //59
    }
    // ATTACK 2 (24 frames)
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/1.png"); //60
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/2.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/3.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/4.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/5.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/6.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/7.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/8.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/9.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/10.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/11.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/13.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/14.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/15.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/16.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/17.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/18.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/19.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/20.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/21.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/22.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/23.png"); 
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack2/24.png"); //84
    }
    // ATTACK 3 (17 frames)
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/1.png"); //85
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/2.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/3.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/4.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/5.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/6.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/7.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/8.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/9.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/10.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/11.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/12.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/13.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/14.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/15.png");
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/16.png"); //100
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Attack3/17.png"); //100
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
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/Baton.obj");


    return true;
}

bool SceneResources::InitLocalMeshResources(MeshManager& meshMngr)
{
    meshMngr.InitTriangle();
    meshMngr.InitSquare();
    meshMngr.InitCube();

    return true;
}
