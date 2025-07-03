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

    return true;
}

bool SceneResources::InitImportedMeshResources(MeshManager& meshMngr)
{

    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/ArbreTest.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/Cepha1.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/Cube.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/TEMPLE.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/Maison.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/RockBig.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/RockLM1.obj");
    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/RockLM2.obj");

    meshMngr.LoadMeshFromFile("../LyonPlexLib/Ressources/maison2.obj");
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


    return true;
}

bool SceneResources::InitLocalMeshResources(MeshManager& meshMngr)
{
    meshMngr.InitTriangle();
    meshMngr.InitSquare();
    meshMngr.InitCube();

    return true;
}
