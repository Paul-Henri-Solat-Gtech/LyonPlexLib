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

    txtMngr.LoadTexture("../LyonPlexLib/Ressources/Test3.jpg");//0
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/Test.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/TestBRAS.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/grid.png");
    txtMngr.LoadTexture("../LyonPlexLib/Ressources/NoTexture.png");
    txtMngr.LoadTexture("../SampleProject/Ressources/icecream.png");//5

    // IDLE ARM (24 frame
    {
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/1.png"); //6
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
        txtMngr.LoadTexture("../SampleProject/Ressources/Animations/Idle/24.png"); //30
    }


    return true;
}

bool SceneResources::InitImportedMeshResources(MeshManager& meshMngr)
{

    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/ArbreTest.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/Cepha1.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/Cube.obj");


    return true;
}

bool SceneResources::InitLocalMeshResources(MeshManager& meshMngr)
{
    meshMngr.InitTriangle();
    meshMngr.InitSquare();
    meshMngr.InitCube();

    return true;
}
