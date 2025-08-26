#include "pch.h"
#include "GameScene.h"
#include "Utils.h"
#include "Boulder.h"

//debug
#include <psapi.h>

//Utils::Vector3 POSITION_CHAMPS = { 5, 0, 32.5 };

// { 325, -2, 50 }
XMFLOAT3 POSITION_CHAMPS = { 325, -2, 50 };

void GameScene::Start()
{
	m_pauseIsOpen = false;

	CreateGameObject("cam", TYPE_3D, false);
	m_cam = GetGameObjectByName("cam");
	m_cam.AddComponent<CameraComponent>(new CameraComponent());
	GetGameObjectByName("cam").SetPosition({ 0, 0, 0.5f });

	// fps cam
	m_fpsCam.Init(m_cam, mp_sceneManager->GetWindow());

	// CreateGameObject("player"); //				45		-60
	// GetGameObjectByName("player").SetScale({ 1, 3, 1 });
	// XMFLOAT3 pos(POSITION_CHAMPS.x + 0, POSITION_CHAMPS.y + 15, POSITION_CHAMPS.z + 0);
	// GetGameObjectByName("player").SetPosition(pos);
	// m_player = GetGameObjectByName("player");
	//m_player.SetTexture(TEXTURES::EMPTY);

	SetParent("cam", "player");
	m_fpsCam.SetParentGO(m_cam);

	m_playerWalkSpeed = 3.f;
	m_playerRunSpeed = 6.f;
	m_playerSpeed = m_playerWalkSpeed;

	// Test player + stateMachine
	m_playerTest.Init(mp_ecsManager, mp_sceneManager->GetGameManager(), this, m_cam);
	SetParent(GetGameObjectByName("cam"), m_playerTest);
	//SetParent("cam", "player");

	RECT renderZone;
	GetClientRect(mp_sceneManager->GetGameManager()->GetRenderingManager().GetGraphicsDevice()->GetWindow(), &renderZone);
	UINT renderWidth = renderZone.right - renderZone.left;
	UINT renderHeight = renderZone.bottom - renderZone.top;
	CreateGameObject("bras", TYPE_2D, true);
	GetGameObjectByName("bras").SetMesh(MESHES::LOCAL_SQUARE);
	GetGameObjectByName("bras").SetTexture(TEXTURES::ARMS);
	GetGameObjectByName("bras").SetPosition({ (float)renderWidth / 2, (float)renderHeight / 2 + (float)renderHeight / 4, 0 });
	GetGameObjectByName("bras").SetScale({ (float)renderWidth * 0.45f, (float)renderHeight * 0.45f, 0 });
	GetGameObjectByName("bras").GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	m_playerTest.SetPlayerArm(GetGameObjectByName("bras"));

	auto b = CreateGameObject<Boulder>(mp_ecsManager, mp_sceneManager->GetGameManager(), m_playerTest, this);
	b.SetPosition({ 315, 2, 58 });
	b.SetScale({ 3, 3, 3 });

	CreateGameObject("Stick");
	XMFLOAT3 pos = { POSITION_CHAMPS.x + 2, POSITION_CHAMPS.y + 3, POSITION_CHAMPS.z + 2 };
	GetGameObjectByName("Stick").SetPosition(pos);
	GetGameObjectByName("Stick").SetScale({ 1, 1, 1 });
	GetGameObjectByName("Stick").SetMesh(MESHES::STICK);
	GetGameObjectByName("Stick").SetTexture(TEXTURES::HERBE);
	auto a = GetGameObjectByName("Stick").GetScale();
	//GetGameObjectByName("Stick").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ a.x / 2, a.y / 2, a.z / 2 })));
	GetGameObjectByName("Stick").AddComponent<Tag_Object>(new Tag_Object());
	GetGameObjectByName("Stick").SetTag(TAG_Stick);
	CreateGameObject("Stick2");
	pos = { POSITION_CHAMPS.x - 2, POSITION_CHAMPS.y + 3, POSITION_CHAMPS.z + 2 };
	GetGameObjectByName("Stick2").SetPosition(pos);
	GetGameObjectByName("Stick2").SetScale({ 2, 2, 2 });
	GetGameObjectByName("Stick2").SetMesh(MESHES::STICK);
	GetGameObjectByName("Stick2").SetTexture(TEXTURES::HERBE);
	a = GetGameObjectByName("Stick2").GetScale();
	//GetGameObjectByName("Stick2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ a.x / 2, a.y / 2, a.z / 2 })));
	GetGameObjectByName("Stick2").AddComponent<Tag_Object>(new Tag_Object());
	GetGameObjectByName("Stick2").SetTag(TAG_Stick);
	CreateGameObject("Stick3");
	pos = { POSITION_CHAMPS.x - 2, POSITION_CHAMPS.y + 3, POSITION_CHAMPS.z + 3 };
	GetGameObjectByName("Stick3").SetPosition(pos);
	GetGameObjectByName("Stick3").SetScale({ 2, 2, 2 });
	GetGameObjectByName("Stick3").SetMesh(MESHES::STICK);
	GetGameObjectByName("Stick3").SetTexture(TEXTURES::CEPHA);
	a = GetGameObjectByName("Stick3").GetScale();
	//GetGameObjectByName("Stick3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ a.x / 2, a.y / 2, a.z / 2 })));
	GetGameObjectByName("Stick3").AddComponent<Tag_Object>(new Tag_Object());
	GetGameObjectByName("Stick3").SetTag(TAG_Stick);

	CreateGameObject("Rock");
	pos = { POSITION_CHAMPS.x - 3, POSITION_CHAMPS.y + 3, POSITION_CHAMPS.z - 2 };
	GetGameObjectByName("Rock").SetPosition(pos);
	GetGameObjectByName("Rock").SetScale({ 0.2, 0.2, 0.2 });
	GetGameObjectByName("Rock").SetMesh(MESHES::CAILLOUX1);
	GetGameObjectByName("Rock").SetTexture(TEXTURES::CEPHA);
	a = GetGameObjectByName("Rock").GetScale();
	//GetGameObjectByName("Rock").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ a.x / 2, a.y / 2, a.z / 2 })));
	GetGameObjectByName("Rock").AddComponent<Tag_Object>(new Tag_Object());
	GetGameObjectByName("Rock").SetTag(TAG_Rock);


	// Audio
	CreateSoundPlex("slash1", L"../LyonPlexLib/Ressources/swordSlash1.wav");
	CreateSoundPlex("Corrosion", L"../LyonPlexLib/Ressources/Corrosion.wav");
	CreateSoundPlex("deathScream", L"../SampleProject/Ressources/Sounds/deathScreamBBB3.wav");
	CreateSoundPlex("HUGH", L"../SampleProject/Ressources/Sounds/HUGH.wav");
	PlayMusicPlex("Corrosion");


	// scene
	CreateEntity("Light1");
	AddComponent<Type_3D>("Light1", new Type_3D());
	AddComponent<MeshComponent>("Light1", new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::BOIS));
	GetComponent<TransformComponent>("Light1")->position = { 320,2,58 };
	GetComponent<TransformComponent>("Light1")->scale = { 1, 1, 1 };
	AddComponent<LightComponent>("Light1", new LightComponent(1));
	GetComponent<LightComponent>("Light1")->color = { 1,0,1 };
	GetComponent<LightComponent>("Light1")->direction = { -1, -1, -1 };
	GetComponent<LightComponent>("Light1")->range = 50;

	CreateEntity("Light2");
	AddComponent<Type_3D>("Light2", new Type_3D());
	AddComponent<MeshComponent>("Light2", new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::BOIS));
	GetComponent<TransformComponent>("Light2")->position = { 290,3,58 };
	GetComponent<TransformComponent>("Light2")->scale = { 1, 1, 1 };
	AddComponent<LightComponent>("Light2", new LightComponent(0));
	GetComponent<LightComponent>("Light2")->color = { 0,1,1 };
	GetComponent<LightComponent>("Light2")->range = 50;


	CreateGameObject("solGen", MESHES::LOCAL_CUBE, TEXTURES::HERBE);
	GetGameObjectByName("solGen").SetTag(TAG_Floor);
	//GetGameObjectByName("solGen").SetPosition(POSITION_CHAMPS);
	GetGameObjectByName("solGen").SetPosition({ 200,-8,100 });
	GetGameObjectByName("solGen").SetScale({ 400, 10, 200 });
	auto c = GetGameObjectByName("solGen").GetScale();
	GetGameObjectByName("solGen").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("field", MESHES::LOCAL_CUBE, TEXTURES::GRID);
	GetGameObjectByName("field").SetTag(TAG_Floor);
	GetGameObjectByName("field").SetPosition(POSITION_CHAMPS);
	GetGameObjectByName("field").SetScale({ 100, 5, 50 });
	c = GetGameObjectByName("field").GetScale();
	//GetGameObjectByName("field").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));
	GetGameObjectByName("field").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("Temple", MESHES::TEMPLE, TEXTURES::TEMPLE);
	GetGameObjectByName("Temple").SetTag(TAG_Floor);
	GetGameObjectByName("Temple").SetPosition({ 75,0,125 });
	//GetGameObjectByName("Temple").SetScale({ 100, 5, 100 });
	GetGameObjectByName("Temple").SetScale({ 1.25, 1.5, 1.25 });
	c = GetGameObjectByName("Temple").GetScale();
	GetGameObjectByName("Temple").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("Mountain", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
	GetGameObjectByName("Mountain").SetTag(TAG_Floor);
	GetGameObjectByName("Mountain").SetPosition({ 300,7,150 });
	GetGameObjectByName("Mountain").SetScale({ 200, 14, 100 });
	c = GetGameObjectByName("Mountain").GetScale();
	GetGameObjectByName("Mountain").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("Mountain2", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
	GetGameObjectByName("Mountain2").SetTag(TAG_Floor);
	GetGameObjectByName("Mountain2").SetPosition({ 167.5, 2, 100 });
	GetGameObjectByName("Mountain2").SetScale({ 65, 25, 20 });
	c = GetGameObjectByName("Mountain2").GetScale();
	GetGameObjectByName("Mountain2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("Mountain3", MESHES::CAILLOUX4, TEXTURES::PIERRE);
	GetGameObjectByName("Mountain3").SetTag(TAG_Floor);
	GetGameObjectByName("Mountain3").SetPosition({ 125, 2, 100 });
	GetGameObjectByName("Mountain3").SetScale({ 10, 12, 3 });
	c = GetGameObjectByName("Mountain3").GetScale();
	GetGameObjectByName("Mountain3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	{
		CreateGameObject("RTEST", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
		GetGameObjectByName("RTEST").SetTag(TAG_Floor);
		GetGameObjectByName("RTEST").SetPosition({ 175, 5, 25 });
		GetGameObjectByName("RTEST").SetScale({ 200, 5, 50 });
		GetGameObjectByName("RTEST").AddRotation({ 10,0,0 });
		c = GetGameObjectByName("RTEST").GetScale();
		GetGameObjectByName("RTEST").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

		CreateGameObject("RTEST3", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
		GetGameObjectByName("RTEST3").SetTag(TAG_Floor);
		GetGameObjectByName("RTEST3").SetPosition({ 275, 5, 45 });
		GetGameObjectByName("RTEST3").SetScale({ 20, 5, 50 });
		GetGameObjectByName("RTEST3").AddRotation({ 40,0,0 });
		c = GetGameObjectByName("RTEST3").GetScale();
		GetGameObjectByName("RTEST3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

		CreateGameObject("RTEST4", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
		GetGameObjectByName("RTEST4").SetTag(TAG_Floor);
		GetGameObjectByName("RTEST4").SetPosition({ 50, 5, 25 });
		GetGameObjectByName("RTEST4").SetScale({ 20, 5, 50 });
		GetGameObjectByName("RTEST4").AddRotation({ 50,0,0 });
		c = GetGameObjectByName("RTEST4").GetScale();
		GetGameObjectByName("RTEST4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

		CreateGameObject("RTEST2", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
		GetGameObjectByName("RTEST2").SetTag(TAG_Floor);
		GetGameObjectByName("RTEST2").SetPosition({ 175, 2, 70 });
		GetGameObjectByName("RTEST2").SetScale({ 15, 10, 50 });
		GetGameObjectByName("RTEST2").AddRotation({ 10,0,-10 });
		c = GetGameObjectByName("RTEST2").GetScale();
		GetGameObjectByName("RTEST2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

		CreateGameObject("Road1", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
		GetGameObjectByName("Road1").SetTag(TAG_Floor);
		GetGameObjectByName("Road1").SetPosition({ 175, -2, 50 });
		GetGameObjectByName("Road1").SetScale({ 200, 5, 10 });
		c = GetGameObjectByName("Road1").GetScale();
		GetGameObjectByName("Road1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

		CreateGameObject("Road2", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
		GetGameObjectByName("Road2").SetTag(TAG_Floor);
		GetGameObjectByName("Road2").SetPosition({ 80, -2, 60 });
		GetGameObjectByName("Road2").SetScale({ 10, 5, 10 });
		c = GetGameObjectByName("Road2").GetScale();
		GetGameObjectByName("Road2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

		CreateGameObject("Road3", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
		GetGameObjectByName("Road3").SetTag(TAG_Floor);
		GetGameObjectByName("Road3").SetPosition({ 75, -2, 80 });
		GetGameObjectByName("Road3").SetScale({ 75, 5, 30 });
		c = GetGameObjectByName("Road3").GetScale();
		GetGameObjectByName("Road3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

		CreateGameObject("Tree", MESHES::ARBRETEST, TEXTURES::HERBE);
		GetGameObjectByName("Tree").SetTag(TAG_Floor);
		GetGameObjectByName("Tree").SetPosition({ 80, -2, 50 });
		GetGameObjectByName("Tree").SetScale({ 50, 50, 50 });
		c = GetGameObjectByName("Tree").GetScale();
		GetGameObjectByName("Tree").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));
	}



	/*CreateGameObject("Pond", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	GetGameObjectByName("Pond").SetTag(TAG_Floor);
	GetGameObjectByName("Pond").SetPosition({ 180, -2, 150 });
	GetGameObjectByName("Pond").SetScale({ 40, 5, 80 });
	c = GetGameObjectByName("Pond").GetScale();
	GetGameObjectByName("Pond").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("DownStream", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	GetGameObjectByName("DownStream").SetTag(TAG_Floor);
	GetGameObjectByName("DownStream").SetPosition({ 140, -2, 80 });
	GetGameObjectByName("DownStream").SetScale({ 20, 5, 160 });
	c = GetGameObjectByName("DownStream").GetScale();
	GetGameObjectByName("DownStream").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));*/

	CreateGameObject("Waterfall", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	GetGameObjectByName("Waterfall").SetTag(TAG_Floor);
	GetGameObjectByName("Waterfall").SetPosition({ 199.5, 7.5, 150 });
	GetGameObjectByName("Waterfall").SetScale({ 1, 15, 40 });
	c = GetGameObjectByName("Waterfall").GetScale();
	GetGameObjectByName("Waterfall").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	//CreateGameObject("UpStream", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	//GetGameObjectByName("UpStream").SetTag(TAG_Floor);
	//GetGameObjectByName("UpStream").SetPosition({ 220, 14, 150 });
	//GetGameObjectByName("UpStream").SetScale({ 40, 2, 40 });
	//c = GetGameObjectByName("UpStream").GetScale();
	//GetGameObjectByName("UpStream").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	//CreateGameObject("UpStream1", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	//GetGameObjectByName("UpStream1").SetTag(TAG_Floor);
	//GetGameObjectByName("UpStream1").SetPosition({ 280, 14, 150 });
	//GetGameObjectByName("UpStream1").SetScale({ 80, 2, 20 });
	//c = GetGameObjectByName("UpStream1").GetScale();
	//GetGameObjectByName("UpStream1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	//CreateGameObject("UpStream2", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	//GetGameObjectByName("UpStream2").SetTag(TAG_Floor);
	//GetGameObjectByName("UpStream2").SetPosition({ 330, 14, 180 });
	//GetGameObjectByName("UpStream2").SetScale({ 20, 2, 80 });
	//c = GetGameObjectByName("UpStream2").GetScale();
	//GetGameObjectByName("UpStream2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));


	CreateWaterGameObject("Pond");
	GetGameObjectByName("Pond").SetPosition({ 180, 1, 150 });
	GetGameObjectByName("Pond").SetScale({ 20, 0.5, 40 });

	CreateWaterGameObject("DownStream");
	GetGameObjectByName("DownStream").SetPosition({ 140, 1, 80 });
	GetGameObjectByName("DownStream").SetScale({ 10, 0.5, 80 });

	//CreateWaterGameObject("Waterfall");
	//GetGameObjectByName("Waterfall").SetPosition({ 199.5, 7.5, 150 });
	//GetGameObjectByName("Waterfall").SetScale({ 1, 15, 40 });

	CreateWaterGameObject("UpStream");
	GetGameObjectByName("UpStream").SetPosition({ 220, 14.5, 150 });
	GetGameObjectByName("UpStream").SetScale({ 20, 1, 20 });

	CreateWaterGameObject("UpStream1");
	GetGameObjectByName("UpStream1").SetPosition({ 280, 14.5, 150 });
	GetGameObjectByName("UpStream1").SetScale({ 40, 1, 10 });

	CreateWaterGameObject("UpStream2");
	GetGameObjectByName("UpStream2").SetPosition({ 330, 14.5, 180 });
	GetGameObjectByName("UpStream2").SetScale({ 10, 1, 40 });

	//portal = &CreateGameObject<Portals>(mp_ecsManager, mp_sceneManager->GetGameManager(), m_playerTest, this);
	//portal->SetPosition({ 335, 2, 50 });
	////portal->SetPosition({ -10, 1, 10 });
	//portal->SetScale({ 1, 1, 0.5 });
	//portal->SetTexture(TEXTURES::EAU);



}

void GameScene::Update(float deltatime)
{	
	//debug fps
	// inside main loop, each frame
	{
		// debug fps (use deltatime provided by engine)
		double dtMs = double(deltatime) * 1000.0;
		++s_frameCount;
		s_accumMs += dtMs;

		// every 5 seconds print avg FPS and avg frame ms
		if (s_accumMs >= 5000.0)
		{
			double avgMs = s_accumMs / double(s_frameCount);
			double fps = 1000.0 / avgMs;
			std::ostringstream ss;
			ss << "Perf: avgMs=" << avgMs<< " ms, avgFPS=" << fps<< " DrawCalls=" << g_drawCalls << "\n";
			OutputDebugStringA(ss.str().c_str()); // visible in VS Output
			std::cout << ss.str();
			s_frameCount = 0;
			s_accumMs = 0.0;
			g_drawCalls = 0;
		}

		// every 30 seconds log memory usage (working set)
		// NOTE: renamed 'now' to 'now_tp' to avoid redefinition errors
		auto now_tp = std::chrono::high_resolution_clock::now();
		auto sinceReport = std::chrono::duration<double>(now_tp - s_lastReport).count();
		if (sinceReport >= 30.0)
		{
			PROCESS_MEMORY_COUNTERS pmc{};
			if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
			{
				std::ostringstream m;
				m << "ProcessMem: WorkingSet=" << pmc.WorkingSetSize
					<< " bytes, PagefileUsage=" << pmc.PagefileUsage << "\n";
				OutputDebugStringA(m.str().c_str());
				std::cout << m.str();
			}
			s_lastReport = now_tp;
		}
	}

	if (m_playerTest.IsAlive() || m_pauseIsOpen) 
	{
		m_fpsCam.Update(deltatime);
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

	if (InputManager::GetKeyIsReleased('N'))
	{
		StopMusicPlex();
	}


	//if (std::fmod(m_spawnTimer, 150.0f) == 0)
	//{
	//	// IL FAUT POUVOIR CREER DES ENEMY SANS GAMEOBJECT OU AU MOINS SANS NOM STD::STRING

	//	//Enemy* newEnemy = new Enemy(mp_ecsManager, mp_sceneManager->GetGameManager(), m_player);

	//	auto& newEnemy = CreateGameObject<Enemy>(mp_ecsManager, mp_sceneManager->GetGameManager(), m_player, this);

	//	float posX = Utils::randomFloat(-24, 24);
	//	float posZ = Utils::randomFloat(-24, 24);
	//	newEnemy.SetPosition({ posX, 1, posZ });
	//	newEnemy.SetTexture(TEXTURES::iceCream);
	//	//newEnemy.AddComponent<Tag_Enemy>(new Tag_Enemy());
	//}

	//m_spawnTimer++;

	//portal->OnUdpdate(deltatime);

	//// Enemies
	//ComponentMask mask = (1ULL << Tag_Enemy::StaticTypeID);
	//auto& ecs = mp_ecsManager;
	//float closest = 100;
	//ecs->ForEach(mask, [&](Entity e)
	//	{
	//		GetGameObjectByID(e).OnUdpdate(deltatime);
	//	});
	//// Projectiles
	//mask = (1ULL << Tag_Projectile::StaticTypeID);
	//ecs->ForEach(mask, [&](Entity e)
	//	{
	//		GetGameObjectByID(e).OnUdpdate(deltatime);
	//	});



	for (auto& gameObject : m_sceneGameObjects)
	{
		gameObject.get()->OnUdpdate(deltatime);
	}

	//// PlayerState
	m_playerTest.OnUdpdate(deltatime);


	////if (m_enemyTest.GetGameObject().alive)
	//if (m_playerTest.m_closestEnemy)
	//	m_enemyTest.OnUdpdate(deltatime);

	if (InputManager::GetKeyIsPressed('R'))
	{
		GetGameObjectByName("player").SetPosition({ 45, 3, -60 });
	}

	if (InputManager::GetKeyIsReleased('T'))
	{
		OutputDebugStringA(("\nPlayer State : " + std::string(m_playerTest.GetCurrentStateName())).c_str());
	}

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

	// Change scene [ALLWAYS AT THE END SO THERE IS NO OTHER CODE RUNNING AFTER IN THIS SCENE]
	if (InputManager::GetKeyIsReleased('A'))
	{
		ChangeScene("DevScene");
		return;
	}
}

void GameScene::Release()
{
}

void GameScene::SpawnMenu()
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
}

void GameScene::RemoveMenu() 
{
	DestroyGameObject(GetGameObjectByName("pauseMenu"));
	DestroyGameObject(GetGameObjectByName("btnMainMenu"));
}