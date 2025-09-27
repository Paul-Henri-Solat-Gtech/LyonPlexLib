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
	std::string path;
#ifdef _DEBUG
	path = debugPath;
#else
	path = releasePath;
#endif

    txtMngr.LoadTexture(path + "Image2D/NoTexture.png");//1
    txtMngr.LoadTexture(path + "Environnement3D/Batiments/Amalgate.png");//2
    txtMngr.LoadTexture(path + "Divers/ALGUE.png");//3
    txtMngr.LoadTexture(path + "Divers/ALGUE1.png");//3
    txtMngr.LoadTexture(path + "Image2D/TestBRAS.png");
    txtMngr.LoadTexture(path + "Image2D/grid.png");
    txtMngr.LoadTexture(path + "Image2D/bois.jpg");
    txtMngr.LoadTexture(path + "Image2D/eau.jpg");
    txtMngr.LoadTexture(path + "Image2D/champ.jpg");
    txtMngr.LoadTexture(path + "Image2D/parcelle1.jpg");
    txtMngr.LoadTexture(path + "Image2D/parcelle2.jpg");
    txtMngr.LoadTexture(path + "Image2D/parcelle3.jpg");
    txtMngr.LoadTexture(path + "Image2D/parcelle4.jpg");
    txtMngr.LoadTexture(path + "Image2D/chemin_terre.jpg");
    txtMngr.LoadTexture(path + "Environnement3D/pierre.png");
    txtMngr.LoadTexture(path + "Environnement3D/Herbe.png");
    txtMngr.LoadTexture(path + "Image2D/pont.jpg");
    txtMngr.LoadTexture(path + "Image2D/maison.png");
    txtMngr.LoadTexture(path + "Image2D/temple.jpg");
    txtMngr.LoadTexture(path + "Image2D/Cepha1test.png");
    txtMngr.LoadTexture(path + "Image2D/icecream.png");//19
    txtMngr.LoadTexture(path + "Image2D/start.png");//20
    txtMngr.LoadTexture(path + "Image2D/stop.png");//21
    txtMngr.LoadTexture(path + "Image2D/heart-empty.png");
    txtMngr.LoadTexture(path + "Image2D/heart-demi.png");
    txtMngr.LoadTexture(path + "Image2D/heart-full.png");
    txtMngr.LoadTexture(path + "Image2D/Empty.png");
    txtMngr.LoadTexture(path + "Image2D/weaponPlaceHolder.png");
    txtMngr.LoadTexture(path + "Image2D/pauseMenuL.png");
    txtMngr.LoadTexture(path + "Image2D/btnQuit.png");
    txtMngr.LoadTexture(path + "Image2D/btnMainMenu.png");
    txtMngr.LoadTexture(path + "Image2D/LyonPlexLogo.png");
    txtMngr.LoadTexture(path + "Image2D/lightlp.png");
    txtMngr.LoadTexture(path + "Image2D/groundmt.png");
    txtMngr.LoadTexture(path + "Image2D/portail.png");
    txtMngr.LoadTexture(path + "Image2D/titreV2.png");
    txtMngr.LoadTexture(path + "Image2D/slash.png");
    txtMngr.LoadTexture(path + "Image2D/zero.png");
    txtMngr.LoadTexture(path + "Image2D/one.png");
    txtMngr.LoadTexture(path + "Image2D/two.png");
    txtMngr.LoadTexture(path + "Image2D/tree.png");
    txtMngr.LoadTexture(path + "Image2D/four.png");
    txtMngr.LoadTexture(path + "Image2D/five.png");
    txtMngr.LoadTexture(path + "Image2D/six.png");
    txtMngr.LoadTexture(path + "Image2D/seven.png");
    txtMngr.LoadTexture(path + "Image2D/eight.png");
    txtMngr.LoadTexture(path + "Image2D/nine.png");
    txtMngr.LoadTexture(path + "Image2D/btnStart.png");
    txtMngr.LoadTexture(path + "Image2D/btnArena.png");
    txtMngr.LoadTexture(path + "Image2D/closebtnV2.png");
    txtMngr.LoadTexture(path + "Image2D/testSkyboxV2.png");
    txtMngr.LoadTexture(path + "Image2D/healingrock.png");
    txtMngr.LoadTexture(path + "Image2D/bgArmonizer.png");
    txtMngr.LoadTexture(path + "Image2D/WINSCREEN.png");
    txtMngr.LoadTexture(path + "Image2D/LOSESCREEN.png");
    txtMngr.LoadTexture(path + "Image2D/ScrollSpeed.png");
    txtMngr.LoadTexture(path + "Image2D/ScrollAtk.png");
    txtMngr.LoadTexture(path + "Image2D/WeaponWood.png");
    txtMngr.LoadTexture(path + "Image2D/WeaponRock.png");
    txtMngr.LoadTexture(path + "Image2D/laser.png");
    txtMngr.LoadTexture(path + "Image2D/air.png");
    txtMngr.LoadTexture(path + "Image2D/wood.png");

	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/NoTexture.png");//1
	// txtMngr.LoadTexture(path + "Environnement3D/Batiments/Amalgate.png");//2
	// //txtMngr.LoadTexture(path + "Divers/ALGUE.jpg");//3
	// txtMngr.LoadTexture(path + "Divers/ALGUE.png");//3
	// txtMngr.LoadTexture(path + "Divers/ALGUE1.png");//3
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/TestBRAS.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/grid.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/bois.jpg");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/eau.jpg");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/champ.jpg");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/parcelle1.jpg");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/parcelle2.jpg");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/parcelle3.jpg");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/parcelle4.jpg");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/chemin_terre.jpg");
	// txtMngr.LoadTexture(path + "Environnement3D/pierre.png");
	// txtMngr.LoadTexture(path + "Environnement3D/Herbe.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/pont.jpg");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/maison.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/temple.jpg");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/Cepha1test.png");
	// txtMngr.LoadTexture(path + "Image2D/icecream.png");//19
	// txtMngr.LoadTexture(path + "Image2D/start.png");//20
	// txtMngr.LoadTexture(path + "Image2D/stop.png");//21
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/heart-empty.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/heart-demi.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/heart-full.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/GameOver.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/Empty.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/weaponPlaceHolder.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/pauseMenuL.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/btnQuit.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/btnMainMenu.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/LyonPlexLogo.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/lightlp.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/groundmt.png");
	// txtMngr.LoadTexture(path + "Image2D/portail.png");
	// txtMngr.LoadTexture(path + "Image2D/titreV2.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/slash.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/zero.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/one.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/two.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/tree.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/four.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/five.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/six.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/seven.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/eight.png");
	// txtMngr.LoadTexture("../LyonPlexLib/Ressources/nine.png");
	// txtMngr.LoadTexture(path + "Image2D/btnStart.png");
	// txtMngr.LoadTexture(path + "Image2D/btnArena.png");
	// txtMngr.LoadTexture(path + "Image2D/closebtnV2.png");
	// txtMngr.LoadTexture(path + "Image2D/testSkyboxV2.png");
	// txtMngr.LoadTexture(path + "Image2D/healingrock.png");
	// txtMngr.LoadTexture(path + "Image2D/bgArmonizer.png");
	// txtMngr.LoadTexture(path + "Image2D/WINSCREEN.png");
	// txtMngr.LoadTexture(path + "Image2D/LOSESCREEN.png");
	// txtMngr.LoadTexture(path + "Image2D/ScrollSpeed.png");
	// txtMngr.LoadTexture(path + "Image2D/ScrollAtk.png");
	// txtMngr.LoadTexture(path + "Image2D/WeaponWood.png");
	// txtMngr.LoadTexture(path + "Image2D/WeaponRock.png");

	// CRABE IDLE
	{
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/1.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/2.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/3.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/4.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/5.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/6.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/7.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/8.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/9.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/10.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/11.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/12.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/13.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/14.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/IDLE/15.png");
	}

	// CRABE WALK
	{
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/WALK/1.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/WALK/2.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/WALK/3.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/WALK/4.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/WALK/5.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/WALK/6.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/WALK/7.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/WALK/8.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/WALK/9.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/WALK/10.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/WALK/11.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/WALK/12.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/WALK/13.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/WALK/14.png");
	}

	// CRABE ATTACK
	{
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/1.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/2.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/3.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/4.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/5.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/6.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/7.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/8.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/9.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/10.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/11.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/12.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/13.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/14.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/15.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/16.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/17.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/18.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/19.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/20.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/21.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/22.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/23.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/24.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/25.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/26.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Crabe/ATTACK/27.png");
	}

	// GOLEM IDLE
	{
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/1.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/2.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/3.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/4.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/5.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/6.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/7.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/8.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/9.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/10.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/11.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/12.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/13.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/14.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/15.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/16.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/17.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/18.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/19.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/IDLE/20.png");
	}

	// GOLEM WALK
	{
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/1.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/2.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/3.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/4.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/5.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/6.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/7.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/8.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/9.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/10.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/11.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/12.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/13.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/14.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/15.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/16.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/17.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/18.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/19.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/20.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/21.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/22.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/23.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/24.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/25.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/26.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/27.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/28.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/29.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/30.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/31.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/32.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/33.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/34.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/35.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/WALK/36.png");
	}

	// GOLEM ATTACK
	{
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/1.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/2.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/3.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/4.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/5.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/6.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/7.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/8.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/9.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/10.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/11.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/12.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/13.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/14.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/15.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/16.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/17.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/18.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/19.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/20.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/21.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/22.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/23.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/24.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/25.png");
	    txtMngr.LoadTexture(path + "Animations/Enemies/Golem/ATTACK/26.png");
	}

	// IDLE ARM (24 frames)
	{
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/1.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/2.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/3.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/4.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/5.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/6.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/7.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/8.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/9.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/10.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/11.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/12.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/13.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/14.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/15.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/16.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/17.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/18.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/19.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/20.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/21.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/22.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/23.png");
		txtMngr.LoadTexture(path + "Animations/Player/Idle/NoWeapons/24.png"); //43
	}
	// IDLE ARM WEAPON 1
	{
		//-v2
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/1.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/2.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/3.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/4.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/5.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/6.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/7.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/8.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/9.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/10.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/11.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/12.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/13.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/14.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/15.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/IDLE/16.png");
	}
	// ATTACK 1 WEAPON 1
	{
		//--v2
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/1.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/2.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/3.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/4.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/5.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/6.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/7.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/8.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/9.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/10.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/11.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/12.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/13.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/14.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/15.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/16.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/17.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/18.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/19.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/20.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/21.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/22.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/23.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/24.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/25.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/26.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/27.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK1/28.png");
	}
	// ATTACK 2 WEAPON 1
	{
		//-v2
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/1.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/2.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/3.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/4.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/5.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/6.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/7.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/8.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/9.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/10.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/11.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/12.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/13.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/14.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/15.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/16.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/17.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK2/18.png");

	}
	// ATTACK 3 WEAPON 1
	{
		//-v2
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/1.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/2.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/3.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/4.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/5.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/6.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/7.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/8.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/9.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/10.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/11.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/12.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/13.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/14.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/15.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/16.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/17.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/18.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/19.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/20.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/21.png");
		txtMngr.LoadTexture(path + "Animations/Player/LightWeapon/ATK3/22.png");
	}

	// IDLE ARM WEAPON 2 (11 frames)
	{
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/IDLE/1.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/IDLE/2.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/IDLE/3.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/IDLE/4.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/IDLE/5.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/IDLE/6.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/IDLE/7.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/IDLE/8.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/IDLE/9.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/IDLE/10.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/IDLE/11.png");
	}

	// ATTACK 1 WEAPON 2 (16 frames)
	{
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/1.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/2.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/3.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/4.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/5.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/6.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/8.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/9.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/10.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/11.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/12.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/13.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/14.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/15.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/16.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/17.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/18.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/19.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/20.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/21.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/22.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/23.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/24.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/25.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/26.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/27.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/28.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/29.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/30.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/31.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/32.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/33.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/34.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/35.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/36.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/37.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/38.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK1/39.png");
	}

	// ATTACK 2 WEAPON 2 (16 frames)
	{
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/1.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/2.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/3.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/4.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/5.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/6.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/8.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/9.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/10.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/11.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/12.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/13.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/14.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/15.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/16.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/17.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/18.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/19.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/20.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/21.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/22.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/23.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/24.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/25.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/26.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/27.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/28.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/29.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/30.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/31.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/32.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/33.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/34.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/35.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/36.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/37.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/38.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/39.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/40.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/41.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/42.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/43.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/44.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/45.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/46.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK2/47.png");
	}

	// ATTACK 3 WEAPON 2 (16 frames)
	{
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/2.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/3.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/4.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/5.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/6.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/8.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/9.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/10.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/11.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/12.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/13.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/14.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/15.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/16.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/17.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/18.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/19.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/20.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/21.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/22.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/23.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/24.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/25.png");
		txtMngr.LoadTexture(path + "Animations/Player/HeavyWeapon/ATK3/26.png");
	}





	return true;
}

bool SceneResources::InitImportedMeshResources(MeshManager& meshMngr)
{

	std::string path;
#ifdef _DEBUG
	path = debugPath;
#else
	path = releasePath;
#endif
    // A MODIFIER
    meshMngr.LoadMeshFromFile(path + "Environnement3D/Batiments/Maison.obj");
    meshMngr.LoadMeshFromFile(path + "Environnement3D/Objets/Baton.obj");
    meshMngr.LoadMeshFromFile(path + "Environnement3D/Environnement/Herbe.obj");

	meshMngr.LoadMeshFromFile(path + "Environnement3D/Batiments/Temple.obj");


	// NOUVEAUX
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Bushes/Fleur.obj");
	//meshMngr.LoadMeshFromFile(path + "Environnement3D/Bushes/Feuille.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Bushes/BigFL.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Bushes/Big.obj");    //20
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Bushes/MediumFL.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Bushes/Medium.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Bushes/little.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Rocks/Path1.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Rocks/Path2.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Rocks/Path3.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Rocks/RockBig.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Rocks/RockLM1.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Rocks/RockLM2.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Rocks/RockLM3.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Rocks/RockMedium.obj");//30



	meshMngr.LoadMeshFromFile(path + "Environnement3D/Environnement/Map.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Lianes/LIANE1.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Lianes/LIANE2.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Lianes/LIANE3.obj");

	meshMngr.LoadMeshFromFile(path + "Environnement3D/Trees/Cepha1.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Trees/Cepha2.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Trees/Cypress1.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Trees/Cypress2.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Trees/Mastic1.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Trees/Mastic2.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Trees/Olive1.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Trees/Olive1_tronc.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Trees/Olive1_sup.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Trees/Olive2.obj");

	meshMngr.LoadMeshFromFile(path + "Environnement3D/Batiments/PONT.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Batiments/POTEAU_INTACT.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Batiments/PILIER_BRISE.obj");

	meshMngr.LoadMeshFromFile(path + "Environnement3D/Batiments/Wall.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Batiments/Wall_Broken.obj");
	meshMngr.LoadMeshFromFile(path + "Environnement3D/Batiments/Wall_Doorway.obj");

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
