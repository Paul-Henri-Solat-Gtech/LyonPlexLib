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
		CreateGameObject("Next 0", 2, 0);
		GetGameObjectByName("Next 0").SetPosition({ 0,0,0 });
		GetGameObjectByName("Next 0").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("Next 0").SetScale({ 1,1,1 });

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
				OutputDebugStringA("\n [ ! Start new Wave ! ] \n");
				m_waveNow++;
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