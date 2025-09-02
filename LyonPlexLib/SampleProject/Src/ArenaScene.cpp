#include "pch.h"
#include "ArenaScene.h"

void ArenaScene::Start()
{
	//SCREEN SIZE
	RECT renderZone;
	GetClientRect(mp_sceneManager->GetGameManager()->GetRenderingManager().GetGraphicsDevice()->GetWindow(), &renderZone);
	UINT renderWidth = renderZone.right - renderZone.left;
	UINT renderHeight = renderZone.bottom - renderZone.top;

	//CAMERA
	CreateGameObject("cam", TYPE_3D, false);
	m_cam = GetGameObjectByName("cam");
	mp_ecsManager->RemoveComponent<MeshComponent>(m_cam.GetEntity());
	m_cam.AddComponent<CameraComponent>(new CameraComponent());
	GetGameObjectByName("cam").SetPosition({ 0, 0, 0.5f });


	m_fpsCam.Init(m_cam, mp_sceneManager->GetWindow());

	SetParent("cam", "player");
	m_fpsCam.SetParentGO(m_cam);

	m_fpsCam.SetAlwaysActive(true);

	//PLAYER
	m_player.Init(mp_ecsManager, mp_sceneManager->GetGameManager(), this, m_cam);
	SetParent(GetGameObjectByName("cam"), m_player);
	m_player.SetPosition({ 0,0,0 });

	//SOUNDS
	mp_sceneManager->GetGameManager()->GetSoundManager()->CreateSound("swordSlash1", L"../LyonPlexLib/Ressources/swordSlash1.wav");
	mp_sceneManager->GetGameManager()->GetSoundManager()->CreateSound("swordSpecialSlash", L"../LyonPlexLib/Ressources/swordSpecialSlash.wav");
	mp_sceneManager->GetGameManager()->GetSoundManager()->CreateSound("deathScream", L"../SampleProject/Ressources/Sounds/deathScreamBBB3.wav");
	mp_sceneManager->GetGameManager()->GetSoundManager()->CreateSound("HUGH", L"../SampleProject/Ressources/Sounds/HUGH.wav");

	//PLAYER ARMS
	CreateGameObject("bras", TYPE_2D, true);
	GetGameObjectByName("bras").SetMesh(MESHES::LOCAL_SQUARE);
	GetGameObjectByName("bras").SetTexture(TEXTURES::ARMS);
	GetGameObjectByName("bras").SetPosition({ (float)renderWidth / 2, (float)renderHeight / 2 + (float)renderHeight / 4, 0 });
	GetGameObjectByName("bras").SetScale({ (float)renderWidth * 0.45f, (float)renderHeight * 0.45f, 0 });
	GetGameObjectByName("bras").GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	m_player.SetPlayerArm(GetGameObjectByName("bras"));

	//MENU PAUSE
	m_pauseIsOpen = false;

	//WAVE
	m_waveNow = 1;
	m_waveMax = 5;
	m_waveFinished = false;
	m_waveStarted = true;
	m_cooldownNextWave = 10.f;
	m_portalNbSpawned = 0;
	m_portalHasSpawned = false;
	m_fisrtEnnemyHasSpawned = false;
	m_youWin = false;

	//WAVE HUD
	m_waveNowHud = CreateGameObject("waveNowHud", TYPE_2D, true);
	m_waveNowHud.SetMesh(MESHES::LOCAL_SQUARE);
	m_waveNowHud.SetTexture(TEXTURES::ZERO);
	m_waveNowHud.SetPosition({ (float)renderWidth - 80, (float)renderHeight / 6, 0 });
	m_waveNowHud.SetScale({ (float)renderWidth * 0.05f, (float)renderHeight * 0.1f, 0 });
	m_waveNowHud.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	m_slash = CreateGameObject("slashHud", TYPE_2D, true);
	m_slash.SetMesh(MESHES::LOCAL_SQUARE);
	m_slash.SetTexture(TEXTURES::SLASH);
	m_slash.SetPosition({ (float)renderWidth - 160, (float)renderHeight / 6, 0 });
	m_slash.SetScale({ (float)renderWidth * 0.05f, (float)renderHeight * 0.1f, 0 });
	m_slash.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	m_waveMaxHud = CreateGameObject("waveMaxHud", TYPE_2D, true);
	m_waveMaxHud.SetMesh(MESHES::LOCAL_SQUARE);
	m_waveMaxHud.SetTexture(TEXTURES::NINE);
	m_waveMaxHud.SetPosition({ (float)renderWidth - 250, (float)renderHeight / 6, 0 });
	m_waveMaxHud.SetScale({ (float)renderWidth * 0.05f, (float)renderHeight * 0.1f, 0 });
	m_waveMaxHud.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	//ITEMS
	CreateGameObject("Stick");
	GetGameObjectByName("Stick").SetPosition({ 0, -10, 0 });
	GetGameObjectByName("Stick").SetScale({ 2, 2, 2 });
	GetGameObjectByName("Stick").SetMesh(MESHES::STICK);
	GetGameObjectByName("Stick").SetTexture(TEXTURES::HERBE);
	GetGameObjectByName("Stick").AddComponent<Tag_Object>(new Tag_Object());
	GetGameObjectByName("Stick").SetTag(TAG_Stick);

	//PORTALS
	//Use pos : y ~ -10 Xmax Xmin getmainmoutain size
	//m_portal = &CreateGameObject<Portals>(mp_ecsManager, mp_sceneManager->GetGameManager(), m_player, this);
	//m_portal->SetPosition({ 30, -10, 30 });
	//m_portal->SetScale({ 1, 1, 0.5 });
	//m_portal->SetTexture(TEXTURES::EAU);

	//SCENE
	{
		CreateGameObject("skybox", 2, 0);
		GetGameObjectByName("skybox").SetPosition({ 0,0,0 });
		GetGameObjectByName("skybox").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("skybox").SetScale({ -1000,-1000,-1000 });
		GetGameObjectByName("skybox").SetMesh(MESHES::LOCAL_SPHERE);
		GetGameObjectByName("skybox").SetTexture(TEXTURES::SKYBOX);

		CreateGameObject("MainMountain", 2, 0);
		GetGameObjectByName("MainMountain").SetTexture(TEXTURES::GroundMountain);
		GetGameObjectByName("MainMountain").SetPosition({ 0,-99,0 });
		GetGameObjectByName("MainMountain").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("MainMountain").SetScale({ 640,174,640 });
		auto c = GetGameObjectByName("MainMountain").GetScale();
		GetGameObjectByName("MainMountain").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

		CreateGameObject("Next 2", 2, 5);
		GetGameObjectByName("Next 2").SetPosition({ 18,-12,-23 });
		GetGameObjectByName("Next 2").SetRotation({ -0.270501554,0.773190141,-0.493573099,-0.292218328 });
		GetGameObjectByName("Next 2").SetScale({ 1,5,1 });
		CreateGameObject("Next 3", 2, 5);
		GetGameObjectByName("Next 3").SetPosition({ 16,-10,-24 });
		GetGameObjectByName("Next 3").SetRotation({ -0.245439559,0.323551387,-0.876536727,-0.258374661 });
		GetGameObjectByName("Next 3").SetScale({ 1,5,1 });
		CreateGameObject("Next 6", 2, 5);
		GetGameObjectByName("Next 6").SetPosition({ 14,-12,8 });
		GetGameObjectByName("Next 6").SetRotation({ -0.596881986,0.332339525,-0.4358491,-0.585933387 });
		GetGameObjectByName("Next 6").SetScale({ 1,5,1 });
		CreateGameObject("Next 8", 2, 5);
		GetGameObjectByName("Next 8").SetPosition({ -31,-12,0 });
		GetGameObjectByName("Next 8").SetRotation({ -0.718239546,-0.164727539,-0.013248777,-0.675885499 });
		GetGameObjectByName("Next 8").SetScale({ 1,5,1 });
		CreateGameObject("Next 9", 2, 5);
		GetGameObjectByName("Next 9").SetPosition({ -26,-12,-29 });
		GetGameObjectByName("Next 9").SetRotation({ -0.957677901,-0.085378788,0.088328496,-0.260310769 });
		GetGameObjectByName("Next 9").SetScale({ 1,5,1 });

		//-----

		CreateGameObject("Next 0b", 2, 0);
		GetGameObjectByName("Next 0b").SetPosition({ 0,0,0 });
		GetGameObjectByName("Next 0b").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("Next 0b").SetScale({ 1,1,1 });
		GetGameObjectByName("Next 0b").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ 0.5, 0.5, 0.5 })));
		CreateGameObject("Next 2b", 2, 5);
		GetGameObjectByName("Next 2b").SetPosition({ -1,-12,-120 });
		GetGameObjectByName("Next 2b").SetRotation({ -0.667234242,-0.637259066,0.29850179,0.244123131 });
		GetGameObjectByName("Next 2b").SetScale({ 1,13,12 });
		CreateGameObject("Next 3b", 2, 5);
		GetGameObjectByName("Next 3b").SetPosition({ 56,-12,115 });
		GetGameObjectByName("Next 3b").SetRotation({ -0.663810909,-0.610748649,0.276965022,0.331106514 });
		GetGameObjectByName("Next 3b").SetScale({ 1,13,12 });
		CreateGameObject("Next 6b", 2, 5);
		GetGameObjectByName("Next 6b").SetPosition({ 83,-12,-7 });
		GetGameObjectByName("Next 6b").SetRotation({ -0.689234376,-0.710599065,0.07979539,0.116780572 });
		GetGameObjectByName("Next 6b").SetScale({ 1,20,24 });
		GetGameObjectByName("Next 6b").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ 0.5, 10, 12 })));
		CreateGameObject("Next 8b", 2, 5);
		GetGameObjectByName("Next 8b").SetPosition({ -153,-12,44 });
		GetGameObjectByName("Next 8b").SetRotation({ 0.381226152,0.272696972,0.493557602,-0.732600868 });
		GetGameObjectByName("Next 8b").SetScale({ 1,20,24 });
		GetGameObjectByName("Next 8b").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ 0.5, 10, 12 })));
		CreateGameObject("Next 1b", 2, 0);
		GetGameObjectByName("Next 1b").SetPosition({ 6,0,5 });
		GetGameObjectByName("Next 1b").SetRotation({ -0.351867527,-0.378683448,0.092660606,0.851000667 });
		GetGameObjectByName("Next 1b").SetScale({ 1,1,1 });
		CreateGameObject("Next 4b", 2, 0);
		GetGameObjectByName("Next 4b").SetPosition({ -80,-12,63 });
		GetGameObjectByName("Next 4b").SetRotation({ -0.161777586,-0.827331543,0.101396948,0.528270125 });
		GetGameObjectByName("Next 4b").SetScale({ 1,13,12 });
		GetGameObjectByName("Next 4b").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ 0.5, 6.5, 6 })));
		CreateGameObject("Next 5b", 2, 0);
		GetGameObjectByName("Next 5b").SetPosition({ -77,-12,-71 });
		GetGameObjectByName("Next 5b").SetRotation({ -0.632475138,-0.734387934,0.162499338,0.185050413 });
		GetGameObjectByName("Next 5b").SetScale({ 1,13,12 });
		GetGameObjectByName("Next 5b").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ 0.5, 6.5, 6 })));
		CreateGameObject("Next 7b", 2, 0);
		GetGameObjectByName("Next 7b").SetPosition({ -140,-12,54 });
		GetGameObjectByName("Next 7b").SetRotation({ 0.10527686,-0.797380924,0.537758529,-0.252816647 });
		GetGameObjectByName("Next 7b").SetScale({ 1,20,24 });
		GetGameObjectByName("Next 7b").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ 0.5, 10, 12 })));
	}


}

void ArenaScene::Update(float deltatime)
{
	//Pause menu
	if (InputManager::GetKeyIsReleased(VK_ESCAPE))
	{
		m_pauseIsOpen = !m_pauseIsOpen;
		if (m_pauseIsOpen)
		{
			SpawnMenu();
		}
		else
		{
			RemoveMenu();
		}
	}

	if (m_pauseIsOpen)
	{
		if (mp_btnMainMenu->GetMouseOnBtn())
		{
			mp_btnMainMenu->SetScale({ 170, 100, 0 });
		}
		if (!mp_btnMainMenu->GetMouseOnBtn())
		{
			mp_btnMainMenu->SetScale({ 120, 50, 0 });
		}
		if (mp_btnMainMenu->GetBtnIsClicked())
		{
			ChangeScene("MainMenuScene");
			return;
		}
	}
	else
	{
		//All updates here (so pause can actually pause everything)

		m_fpsCam.Update(deltatime);
		m_player.OnUdpdate(deltatime);

		//for (auto& gameObject : m_sceneGameObjects)
		//{
		//	gameObject.get()->OnUdpdate(deltatime);
		//}

		std::vector<GameObject*> snapshot;
		snapshot.reserve(m_sceneGameObjects.size());
		for (auto& up : m_sceneGameObjects)
		{
			if (up) snapshot.push_back(up.get());
		}
		for (auto* go : snapshot)
		{
			if (go) go->OnUdpdate(deltatime);
		}

		if (!m_youWin) 
		{
			WaveSystem(deltatime);
		}
	}
}

void ArenaScene::Release()
{
}

void ArenaScene::SpawnMenu()
{
	RECT renderZone;
	GetClientRect(mp_sceneManager->GetGameManager()->GetRenderingManager().GetGraphicsDevice()->GetWindow(), &renderZone);
	UINT renderWidth = renderZone.right - renderZone.left;
	UINT renderHeight = renderZone.bottom - renderZone.top;

	// Pause menu
	CreateGameObject("pauseMenu", TYPE_2D, true);
	GetGameObjectByName("pauseMenu").SetMesh(MESHES::LOCAL_SQUARE);
	GetGameObjectByName("pauseMenu").SetTexture(TEXTURES::PAUSEMENU);
	GetGameObjectByName("pauseMenu").SetPosition({ (float)renderWidth / 2, (float)renderHeight / 2, 0 });
	GetGameObjectByName("pauseMenu").SetScale({ (float)renderWidth * 0.2f, (float)renderHeight * 0.4f, 0 });
	GetGameObjectByName("pauseMenu").GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	// Buttons
	mp_btnMainMenu = &CreateGameObject<Button>(this, mp_sceneManager->GetWindow(), TEXTURES::BTN_MAINMENU, "btnMainMenu");
	mp_btnMainMenu->SetScale({ 120, 50, 0 });
	auto posPauseMenu = GetGameObjectByName("pauseMenu").GetPosition();
	mp_btnMainMenu->SetPosition({ posPauseMenu.x,posPauseMenu.y + 140,posPauseMenu.z });
	m_fpsCam.SetAlwaysActive(false);
}

void ArenaScene::RemoveMenu()
{
	DestroyGameObject(GetGameObjectByName("pauseMenu"));
	DestroyGameObject(GetGameObjectByName("btnMainMenu"));
	m_fpsCam.SetAlwaysActive(true);
}

void ArenaScene::WeaponSystem()
{
}

void ArenaScene::WaveSystem(float deltatime)
{
	if (m_waveNow < m_waveMax) 
	{
		if (m_waveStarted && !m_waveFinished && /*m_portalNbSpawned <= 0 &&*/ !m_portalHasSpawned)
		{
			OutputDebugStringA("\n [ ! Lets go ! ] \n");
			UpdateWaveHUD();
			SpawnPortal();
			m_portalHasSpawned = true;
		}

		if (GetEnnemyNb() >= 1)
		{
			m_fisrtEnnemyHasSpawned = true;
		}

		if (GetEnnemyNb() <= 0 && m_waveStarted && !m_waveFinished && m_portalHasSpawned && m_fisrtEnnemyHasSpawned)
		{
			m_waveFinished = true;
			m_waveStarted = false;
			m_portalHasSpawned = false;
			//m_portal = nullptr;
			m_portalNbSpawned = 0;
			m_cooldownNextWave = 10.0f;
			OutputDebugStringA("\n [ ! Wave is finished ! ] \n");
		}

		if (m_waveFinished)
		{
			if (m_cooldownNextWave <= 0)
			{
				m_waveStarted = true;
				m_waveFinished = false;
				m_fisrtEnnemyHasSpawned = false;
				m_waveNow++;
				OutputDebugStringA("\n [ ! Start new Wave ! ] \n");
			}
			else
			{
				m_cooldownNextWave -= 1 * deltatime;
				//OutputDebugStringA((std::string("\nNext wave in : ") + std::to_string(m_cooldownNextWave)).c_str());
			}
		}
	}
	else
	{
		OutputDebugStringA("\n [ ! You WIN ! ] \n");
		m_youWin = true;
	}
}

void ArenaScene::SpawnPortal() 
{
	int nbEnnemy = 3 + m_waveNow;

	m_portal = &CreateGameObject<Portals>(m_player, this, nbEnnemy);
	m_portal->SetPosition({ 30, -10, 30 });
	m_portal->SetScale({ 1, 1, 0.5 });
	m_portal->SetTexture(TEXTURES::PORTAL);

	m_portalNbSpawned++;
}

void ArenaScene::UpdateWaveHUD() 
{
	switch (m_waveNow)
	{
	case 0:
		m_waveNowHud.SetTexture(TEXTURES::ZERO);
		break;
	case 1:
		m_waveNowHud.SetTexture(TEXTURES::ONE);
		break;
	case 2:
		m_waveNowHud.SetTexture(TEXTURES::TWO);
		break;
	case 3:
		m_waveNowHud.SetTexture(TEXTURES::TREE);
		break;
	case 4:
		m_waveNowHud.SetTexture(TEXTURES::FOUR);
		break;
	case 5:
		m_waveNowHud.SetTexture(TEXTURES::FIVE);
		break;
	case 6:
		m_waveNowHud.SetTexture(TEXTURES::SIX);
		break;
	case 7:
		m_waveNowHud.SetTexture(TEXTURES::SEVEN);
		break;
	case 8:
		m_waveNowHud.SetTexture(TEXTURES::EIGHT);
		break;
	case 9:
		m_waveNowHud.SetTexture(TEXTURES::NINE);
		break;
	default:
		break;
	}

	switch (m_waveMax)
	{
	case 0:
		m_waveMaxHud.SetTexture(TEXTURES::ZERO);
		break;
	case 1:
		m_waveMaxHud.SetTexture(TEXTURES::ONE);
		break;
	case 2:
		m_waveMaxHud.SetTexture(TEXTURES::TWO);
		break;
	case 3:
		m_waveMaxHud.SetTexture(TEXTURES::TREE);
		break;
	case 4:
		m_waveMaxHud.SetTexture(TEXTURES::FOUR);
		break;
	case 5:
		m_waveMaxHud.SetTexture(TEXTURES::FIVE);
		break;
	case 6:
		m_waveMaxHud.SetTexture(TEXTURES::SIX);
		break;
	case 7:
		m_waveMaxHud.SetTexture(TEXTURES::SEVEN);
		break;
	case 8:
		m_waveMaxHud.SetTexture(TEXTURES::EIGHT);
		break;
	case 9:
		m_waveMaxHud.SetTexture(TEXTURES::NINE);
		break;
	default:
		break;
	}
}