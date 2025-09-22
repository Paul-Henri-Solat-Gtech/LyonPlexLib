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
	m_cam = *FindGameObjectByName("cam");
	mp_ecsManager->RemoveComponent<MeshComponent>(m_cam.GetEntity());
	m_cam.AddComponent<CameraComponent>(new CameraComponent());
	FindGameObjectByName("cam")->SetPosition({ 0, 0, 0.5f });

	m_fpsCam.Init(m_cam, mp_sceneManager->GetWindow());

	

	m_fpsCam.SetAlwaysActive(true);

	//PLAYER
	m_player.Init(mp_ecsManager, mp_sceneManager->GetGameManager(), this, m_cam);
	SetParent(*FindGameObjectByName("cam"), m_player);
	m_player.SetPosition({ 0,0,0 });
	//SetParent("cam", "player");
	//PLAYER ARMS
	CreateGameObject("bras", TYPE_2D, true);
	FindGameObjectByName("bras")->SetMesh(MESHES::LOCAL_SQUARE);
	FindGameObjectByName("bras")->SetTexture(TEXTURES::ARMS);
	FindGameObjectByName("bras")->SetPosition({ (float)renderWidth / 2, (float)renderHeight / 2 + (float)renderHeight / 4, 0 });
	FindGameObjectByName("bras")->SetScale({ (float)renderWidth * 0.45f, (float)renderHeight * 0.45f, 0 });
	FindGameObjectByName("bras")->GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	m_player.SetPlayerArm(*FindGameObjectByName("bras"));

	// MUSIC
	PlayMusicPlex("TheCrimsonTideClashArena");

	//MENU PAUSE
	m_pauseIsOpen = false;

	//WAVE
	m_waveNow = 1;
	m_waveMax = 5;
	m_waveFinished = false;
	m_waveStarted = true;
	m_cooldownNextWave = 5.f;
	m_portalNbSpawned = 0;
	m_portalHasSpawned = false;
	m_fisrtEnnemyHasSpawned = false;
	m_youWin = false;
	m_chronoChangeScene = 5.f;
	m_bonusIsOpen = false;
	m_bonusCanBeSelected = false;
	m_bonusSpawnedThisWave = false;

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
	FindGameObjectByName("Stick")->SetPosition({ 0, -10, 0 });
	FindGameObjectByName("Stick")->SetScale({ 5, 5, 5 });
	FindGameObjectByName("Stick")->SetMesh(MESHES::STICK);
	FindGameObjectByName("Stick")->SetTexture(TEXTURES::HERBE);
	FindGameObjectByName("Stick")->AddComponent<Tag_Object>(new Tag_Object());
	FindGameObjectByName("Stick")->SetTag(TAG_Stick);

	CreateGameObject("Rock");
	FindGameObjectByName("Rock")->SetPosition({ 0, -10, 50 });
	FindGameObjectByName("Rock")->SetScale({ 8, 8, 8 });
	FindGameObjectByName("Rock")->SetMesh(MESHES::ROCKLM3);
	FindGameObjectByName("Rock")->SetTexture(TEXTURES::GroundMountain);
	FindGameObjectByName("Rock")->AddComponent<Tag_Object>(new Tag_Object());
	FindGameObjectByName("Rock")->SetTag(TAG_Rock);

	//LIGHT
	CreateGameObject("WorldLight");
	auto* light = FindGameObjectByName("WorldLight");

	light->AddComponent<Type_3D>(new Type_3D());
	light->AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::BOIS));
	//GetComponent<TransformComponent>("WorldLight")->position = { 290,3,58 };
	light->SetPosition({ 290,3,58 });
	light->AddComponent<LightComponent>(new LightComponent(0));
	light->SetScale( { 1, 1, 1 });
	light->GetComponent<LightComponent>()->color = {1,1,1};
	light->GetComponent<LightComponent>()->range = 50;

	//SCENE
	{
		CreateGameObject("skybox", 2, 0);
		FindGameObjectByName("skybox")->SetPosition({ 0,0,0 });
		FindGameObjectByName("skybox")->SetRotation({ 0,0,0,1 });
		FindGameObjectByName("skybox")->SetScale({ -1000,-1000,-1000 });
		FindGameObjectByName("skybox")->SetMesh(MESHES::LOCAL_SPHERE);
		FindGameObjectByName("skybox")->SetTexture(TEXTURES::SKYBOX);

		CreateGameObject("MainMountain", 2, 0);
		FindGameObjectByName("MainMountain")->SetTexture(TEXTURES::GroundMountain);
		FindGameObjectByName("MainMountain")->SetPosition({ 0,-99,0 });
		FindGameObjectByName("MainMountain")->SetRotation({ 0,0,0,1 });
		FindGameObjectByName("MainMountain")->SetScale({ 640,174,640 });
		auto c = FindGameObjectByName("MainMountain")->GetScale();
		FindGameObjectByName("MainMountain")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

		CreateGameObject("Next 2", 2, 5);
		FindGameObjectByName("Next 2")->SetPosition({ 18,-12,-23 });
		FindGameObjectByName("Next 2")->SetRotation({ -0.270501554,0.773190141,-0.493573099,-0.292218328 });
		FindGameObjectByName("Next 2")->SetScale({ 1,5,1 });
		CreateGameObject("Next 3", 2, 5);
		FindGameObjectByName("Next 3")->SetPosition({ 16,-10,-24 });
		FindGameObjectByName("Next 3")->SetRotation({ -0.245439559,0.323551387,-0.876536727,-0.258374661 });
		FindGameObjectByName("Next 3")->SetScale({ 1,5,1 });
		CreateGameObject("Next 6", 2, 5);
		FindGameObjectByName("Next 6")->SetPosition({ 14,-12,8 });
		FindGameObjectByName("Next 6")->SetRotation({ -0.596881986,0.332339525,-0.4358491,-0.585933387 });
		FindGameObjectByName("Next 6")->SetScale({ 1,5,1 });
		CreateGameObject("Next 8", 2, 5);
		FindGameObjectByName("Next 8")->SetPosition({ -31,-12,0 });
		FindGameObjectByName("Next 8")->SetRotation({ -0.718239546,-0.164727539,-0.013248777,-0.675885499 });
		FindGameObjectByName("Next 8")->SetScale({ 1,5,1 });
		CreateGameObject("Next 9", 2, 5);
		FindGameObjectByName("Next 9")->SetPosition({ -26,-12,-29 });
		FindGameObjectByName("Next 9")->SetRotation({ -0.957677901,-0.085378788,0.088328496,-0.260310769 });
		FindGameObjectByName("Next 9")->SetScale({ 1,5,1 });

		//-----

		CreateGameObject("Next 0b", 2, 0);
		FindGameObjectByName("Next 0b")->SetPosition({ 0,0,0 });
		FindGameObjectByName("Next 0b")->SetRotation({ 0,0,0,1 });
		FindGameObjectByName("Next 0b")->SetScale({ 1,1,1 });
		FindGameObjectByName("Next 0b")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ 0.5, 0.5, 0.5 })));
		CreateGameObject("Next 2b", 2, 5);
		FindGameObjectByName("Next 2b")->SetPosition({ -1,-12,-120 });
		FindGameObjectByName("Next 2b")->SetRotation({ -0.667234242,-0.637259066,0.29850179,0.244123131 });
		FindGameObjectByName("Next 2b")->SetScale({ 1,13,12 });
		CreateGameObject("Next 3b", 2, 5);
		FindGameObjectByName("Next 3b")->SetPosition({ 56,-12,115 });
		FindGameObjectByName("Next 3b")->SetRotation({ -0.663810909,-0.610748649,0.276965022,0.331106514 });
		FindGameObjectByName("Next 3b")->SetScale({ 1,13,12 });
		CreateGameObject("Next 6b", 2, 5);
		FindGameObjectByName("Next 6b")->SetPosition({ 83,-12,-7 });
		FindGameObjectByName("Next 6b")->SetRotation({ -0.689234376,-0.710599065,0.07979539,0.116780572 });
		FindGameObjectByName("Next 6b")->SetScale({ 1,20,24 });
		FindGameObjectByName("Next 6b")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ 0.5, 10, 12 })));
		CreateGameObject("Next 8b", 2, 5);
		FindGameObjectByName("Next 8b")->SetPosition({ -153,-12,44 });
		FindGameObjectByName("Next 8b")->SetRotation({ 0.381226152,0.272696972,0.493557602,-0.732600868 });
		FindGameObjectByName("Next 8b")->SetScale({ 1,20,24 });
		FindGameObjectByName("Next 8b")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ 0.5, 10, 12 })));
		CreateGameObject("Next 1b", 2, 0);
		FindGameObjectByName("Next 1b")->SetPosition({ 6,0,5 });
		FindGameObjectByName("Next 1b")->SetRotation({ -0.351867527,-0.378683448,0.092660606,0.851000667 });
		FindGameObjectByName("Next 1b")->SetScale({ 1,1,1 });
		CreateGameObject("Next 4b", 2, 0);
		FindGameObjectByName("Next 4b")->SetPosition({ -80,-12,63 });
		FindGameObjectByName("Next 4b")->SetRotation({ -0.161777586,-0.827331543,0.101396948,0.528270125 });
		FindGameObjectByName("Next 4b")->SetScale({ 1,13,12 });
		FindGameObjectByName("Next 4b")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ 0.5, 6.5, 6 })));
		CreateGameObject("Next 5b", 2, 0);
		FindGameObjectByName("Next 5b")->SetPosition({ -77,-12,-71 });
		FindGameObjectByName("Next 5b")->SetRotation({ -0.632475138,-0.734387934,0.162499338,0.185050413 });
		FindGameObjectByName("Next 5b")->SetScale({ 1,13,12 });
		FindGameObjectByName("Next 5b")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ 0.5, 6.5, 6 })));
		CreateGameObject("Next 7b", 2, 0);
		FindGameObjectByName("Next 7b")->SetPosition({ -140,-12,54 });
		FindGameObjectByName("Next 7b")->SetRotation({ 0.10527686,-0.797380924,0.537758529,-0.252816647 });
		FindGameObjectByName("Next 7b")->SetScale({ 1,20,24 });
		FindGameObjectByName("Next 7b")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ 0.5, 10, 12 })));
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
		m_player.OnUpdate(deltatime);

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
			if (go) go->OnUpdate(deltatime);
		}

		if (!m_youWin)
		{
			if (!m_bonusCanBeSelected)
			{
				WaveSystem(deltatime);
			}
		}
		else
		{
			m_chronoChangeScene -= 1.f * deltatime;

			if (m_chronoChangeScene <= 0)
			{
				ChangeScene("MainMenuScene");
				return;
			}
		}

		// Toute les 2 vagues (le +1 pour la fin de wave)
		if (m_waveNow % 2 == 0 && !m_bonusIsOpen && !m_bonusCanBeSelected && m_waveFinished && !m_bonusSpawnedThisWave)
		{
			BonusEndWave();
		}
		if (m_bonusCanBeSelected)
		{
			if (mp_btnAddAtk->GetMouseOnBtn())
			{
				mp_btnAddAtk->SetScale({ 300, 350, 0 });
			}
			if (!mp_btnAddAtk->GetMouseOnBtn())
			{
				mp_btnAddAtk->SetScale({ 250, 300, 0 });
			}
			if (mp_btnAddAtk->GetBtnIsClicked())
			{
				CloseBonus();
			}

			if (mp_btnAddSpeed->GetMouseOnBtn())
			{
				mp_btnAddSpeed->SetScale({ 300, 350, 0 });
			}
			if (!mp_btnAddSpeed->GetMouseOnBtn())
			{
				mp_btnAddSpeed->SetScale({ 250, 300, 0 });
			}
			if (mp_btnAddSpeed->GetBtnIsClicked())
			{
				m_player.SetMoveSpeed(m_player.GetMoveSpeed() + 50);
				m_player.SetRunSpeed(m_player.GetRunSpeed() + 50);
				CloseBonus();
			}
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
	FindGameObjectByName("pauseMenu")->SetMesh(MESHES::LOCAL_SQUARE);
	FindGameObjectByName("pauseMenu")->SetTexture(TEXTURES::PAUSEMENU);
	FindGameObjectByName("pauseMenu")->SetPosition({ (float)renderWidth / 2, (float)renderHeight / 2, 0 });
	FindGameObjectByName("pauseMenu")->SetScale({ (float)renderWidth * 0.2f, (float)renderHeight * 0.4f, 0 });
	FindGameObjectByName("pauseMenu")->GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	// Buttons
	mp_btnMainMenu = &CreateGameObject<Button>(this, mp_sceneManager->GetWindow(), TEXTURES::BTN_MAINMENU, "btnMainMenu");
	mp_btnMainMenu->SetScale({ 120, 50, 0 });
	auto posPauseMenu = FindGameObjectByName("pauseMenu")->GetPosition();
	mp_btnMainMenu->SetPosition({ posPauseMenu.x,posPauseMenu.y + 140,posPauseMenu.z });
	m_fpsCam.SetAlwaysActive(false);
}

void ArenaScene::RemoveMenu()
{
	DestroyGameObject(*FindGameObjectByName("pauseMenu"));
	DestroyGameObject(*FindGameObjectByName("btnMainMenu"));
	m_fpsCam.SetAlwaysActive(true);
}

void ArenaScene::WeaponSystem()
{
}

void ArenaScene::WaveSystem(float deltatime)
{
	if (m_waveNow <= m_waveMax) 
	{
		if (m_waveStarted && !m_waveFinished && !m_portalHasSpawned)
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
				m_bonusSpawnedThisWave = false;
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

		RECT renderZone;
		GetClientRect(mp_sceneManager->GetGameManager()->GetRenderingManager().GetGraphicsDevice()->GetWindow(), &renderZone);
		UINT renderWidth = renderZone.right - renderZone.left;
		UINT renderHeight = renderZone.bottom - renderZone.top;

		CreateGameObject("Win", TYPE_2D, true);
		auto& win = *FindGameObjectByName("Win");
		win.SetMesh(MESHES::LOCAL_SQUARE);
		win.SetTexture(TEXTURES::WINSCREEN);
		win.SetPosition({ (float)renderWidth / 2, (float)renderHeight / 2, 0 });
		win.SetScale({ (float)renderWidth * 0.4f, (float)renderHeight * 0.4f, 0 });
		win.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

		m_youWin = true;
	}
}

void ArenaScene::SpawnPortal() 
{
	int nbEnnemy = 3 + m_waveNow;

	m_portal = &CreateGameObject<Portals>(m_player, this, nbEnnemy,-10);
	m_portal->SetPosition({ 30, -10, 30 });

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

void ArenaScene::BonusEndWave()
{
	RECT renderZone;
	GetClientRect(mp_sceneManager->GetGameManager()->GetRenderingManager().GetGraphicsDevice()->GetWindow(), &renderZone);
	UINT renderWidth = renderZone.right - renderZone.left;
	UINT renderHeight = renderZone.bottom - renderZone.top;

	// Buttons
	mp_btnAddAtk = &CreateGameObject<Button>(this, mp_sceneManager->GetWindow(), TEXTURES::ScrollAtk, "btnAddAtk");
	mp_btnAddAtk->SetScale({ 250, 300, 0 });
	mp_btnAddAtk->SetPosition({ 250, (float)renderHeight/2, 1 });

	mp_btnAddSpeed = &CreateGameObject<Button>(this, mp_sceneManager->GetWindow(), TEXTURES::ScrollSpeed, "btnAddSpeed");
	mp_btnAddSpeed->SetScale({ 250, 300, 0 });
	mp_btnAddSpeed->SetPosition({ (float)renderWidth - 250, (float)renderHeight / 2, 1 });

	m_bonusIsOpen = true;
	m_bonusCanBeSelected = true;

	m_fpsCam.SetAlwaysActive(false);

	OutputDebugStringA("\n bonus yea \n");

	m_bonusSpawnedThisWave = true;
}

void ArenaScene::CloseBonus()
{
	m_bonusCanBeSelected = false;
	DestroyGameObject(*FindGameObjectByName("btnAddAtk"));
	DestroyGameObject(*FindGameObjectByName("btnAddSpeed"));
	m_fpsCam.SetAlwaysActive(true);
	m_bonusIsOpen = false;
}