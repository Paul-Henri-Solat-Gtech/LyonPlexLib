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
	GetEcsManager()->RemoveComponent<MeshComponent>(GetGameObjectByName("cam").GetEntity());

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

	//auto b = CreateGameObject<Boulder>(mp_ecsManager, mp_sceneManager->GetGameManager(), m_playerTest, this);
	//b.SetPosition({ 315, 2, 58 });
	//b.SetScale({ 3, 3, 3 });

	//CreateGameObject("Stick");
	//XMFLOAT3 pos = { POSITION_CHAMPS.x + 2, POSITION_CHAMPS.y + 3, POSITION_CHAMPS.z + 2 };
	//GetGameObjectByName("Stick").SetPosition(pos);
	//GetGameObjectByName("Stick").SetScale({ 1, 1, 1 });
	//GetGameObjectByName("Stick").SetMesh(MESHES::STICK);
	//GetGameObjectByName("Stick").SetTexture(TEXTURES::HERBE);
	//auto a = GetGameObjectByName("Stick").GetScale();
	////GetGameObjectByName("Stick").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ a.x / 2, a.y / 2, a.z / 2 })));
	//GetGameObjectByName("Stick").AddComponent<Tag_Object>(new Tag_Object());
	//GetGameObjectByName("Stick").SetTag(TAG_Stick);
	//CreateGameObject("Stick2");
	//pos = { POSITION_CHAMPS.x - 2, POSITION_CHAMPS.y + 3, POSITION_CHAMPS.z + 2 };
	//GetGameObjectByName("Stick2").SetPosition(pos);
	//GetGameObjectByName("Stick2").SetScale({ 2, 2, 2 });
	//GetGameObjectByName("Stick2").SetMesh(MESHES::STICK);
	//GetGameObjectByName("Stick2").SetTexture(TEXTURES::HERBE);
	//a = GetGameObjectByName("Stick2").GetScale();
	////GetGameObjectByName("Stick2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ a.x / 2, a.y / 2, a.z / 2 })));
	//GetGameObjectByName("Stick2").AddComponent<Tag_Object>(new Tag_Object());
	//GetGameObjectByName("Stick2").SetTag(TAG_Stick);
	//CreateGameObject("Stick3");
	//pos = { POSITION_CHAMPS.x - 2, POSITION_CHAMPS.y + 3, POSITION_CHAMPS.z + 3 };
	//GetGameObjectByName("Stick3").SetPosition(pos);
	//GetGameObjectByName("Stick3").SetScale({ 2, 2, 2 });
	//GetGameObjectByName("Stick3").SetMesh(MESHES::STICK);
	//GetGameObjectByName("Stick3").SetTexture(TEXTURES::CEPHA);
	//a = GetGameObjectByName("Stick3").GetScale();
	////GetGameObjectByName("Stick3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ a.x / 2, a.y / 2, a.z / 2 })));
	//GetGameObjectByName("Stick3").AddComponent<Tag_Object>(new Tag_Object());
	//GetGameObjectByName("Stick3").SetTag(TAG_Stick);

	//CreateGameObject("Rock");
	//pos = { POSITION_CHAMPS.x - 3, POSITION_CHAMPS.y + 3, POSITION_CHAMPS.z - 2 };
	//GetGameObjectByName("Rock").SetPosition(pos);
	//GetGameObjectByName("Rock").SetScale({ 0.2, 0.2, 0.2 });
	//GetGameObjectByName("Rock").SetMesh(MESHES::ROCKBIG);
	//GetGameObjectByName("Rock").SetTexture(TEXTURES::CEPHA);
	//a = GetGameObjectByName("Rock").GetScale();
	////GetGameObjectByName("Rock").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ a.x / 2, a.y / 2, a.z / 2 })));
	//GetGameObjectByName("Rock").AddComponent<Tag_Object>(new Tag_Object());
	//GetGameObjectByName("Rock").SetTag(TAG_Rock);


	// Audio
	CreateSoundPlex("slash1", L"../LyonPlexLib/Ressources/swordSlash1.wav");
	CreateSoundPlex("Corrosion", L"../LyonPlexLib/Ressources/Corrosion.wav");
	CreateSoundPlex("deathScream", L"../SampleProject/Ressources/Sounds/deathScreamBBB3.wav");
	CreateSoundPlex("HUGH", L"../SampleProject/Ressources/Sounds/HUGH.wav");
	PlayMusicPlex("Corrosion");


	//// scene
	//CreateEntity("Light1");
	//AddComponent<Type_3D>("Light1", new Type_3D());
	//AddComponent<MeshComponent>("Light1", new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::BOIS));
	//GetComponent<TransformComponent>("Light1")->position = { 320,2,58 };
	//GetComponent<TransformComponent>("Light1")->scale = { 1, 1, 1 };
	//AddComponent<LightComponent>("Light1", new LightComponent(1));
	//GetComponent<LightComponent>("Light1")->color = { 1,0,1 };
	//GetComponent<LightComponent>("Light1")->direction = { -1, -1, -1 };
	//GetComponent<LightComponent>("Light1")->range = 50;

	//CreateEntity("Light2");
	//AddComponent<Type_3D>("Light2", new Type_3D());
	//AddComponent<MeshComponent>("Light2", new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::BOIS));
	//GetComponent<TransformComponent>("Light2")->position = { 290,3,58 };
	//GetComponent<TransformComponent>("Light2")->scale = { 1, 1, 1 };
	//AddComponent<LightComponent>("Light2", new LightComponent(0));
	//GetComponent<LightComponent>("Light2")->color = { 0,1,1 };
	//GetComponent<LightComponent>("Light2")->range = 50;






	//XMFLOAT2 posXZmin = { POSITION_CHAMPS.x - 45 , POSITION_CHAMPS.z - 20 };
	//XMFLOAT2 posXZmax = { POSITION_CHAMPS.x + 45 , POSITION_CHAMPS.z + 20 };
	//auto boulder = CreateGameObject<Boulder>(mp_ecsManager, mp_sceneManager->GetGameManager(), m_playerTest, this, posXZmin, posXZmax);
	//boulder.SetPosition(POSITION_CHAMPS);
	//boulder.GetPosition().y += 5;
	////boulder.SetScale({ 3, 3, 3 });


	//auto boulder2 = CreateGameObject<Boulder>(mp_ecsManager, mp_sceneManager->GetGameManager(), m_playerTest, this, posXZmin, posXZmax);
	//boulder2.SetPosition({ POSITION_CHAMPS.x - 5, POSITION_CHAMPS.y + 5, POSITION_CHAMPS.z - 10 });
	//boulder2.SetScale({ 3, 3, 3 });


	//auto boulder3 = CreateGameObject<Boulder>(mp_ecsManager, mp_sceneManager->GetGameManager(), m_playerTest, this, posXZmin, posXZmax);
	//boulder3.SetPosition({ POSITION_CHAMPS.x + 5, POSITION_CHAMPS.y + 5, POSITION_CHAMPS.z + 10 });
	//boulder3.SetScale({ 3, 5, 2 });
	//boulder3.SetTransformRotation(XMFLOAT3(15, 0, 0));







	//CreateGameObject("solGen", MESHES::LOCAL_CUBE, TEXTURES::HERBE);
	//GetGameObjectByName("solGen").SetTag(TAG_Floor);
	////GetGameObjectByName("solGen").SetPosition(POSITION_CHAMPS);
	//GetGameObjectByName("solGen").SetPosition({ 200,-8,100 });
	//GetGameObjectByName("solGen").SetScale({ 400, 10, 200 });
	//auto c = GetGameObjectByName("solGen").GetScale();
	//GetGameObjectByName("solGen").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	//CreateGameObject("field", MESHES::LOCAL_CUBE, TEXTURES::GRID);
	//GetGameObjectByName("field").SetTag(TAG_Floor);
	//GetGameObjectByName("field").SetPosition(POSITION_CHAMPS);
	//GetGameObjectByName("field").SetScale({ 100, 5, 50 });
	//c = GetGameObjectByName("field").GetScale();
	////GetGameObjectByName("field").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));
	//GetGameObjectByName("field").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	//CreateGameObject("Temple", MESHES::TEMPLE, TEXTURES::TEMPLE);
	//GetGameObjectByName("Temple").SetTag(TAG_Floor);
	//GetGameObjectByName("Temple").SetPosition({ 75,0,125 });
	////GetGameObjectByName("Temple").SetScale({ 100, 5, 100 });
	//GetGameObjectByName("Temple").SetScale({ 1.25, 1.5, 1.25 });
	//c = GetGameObjectByName("Temple").GetScale();
	//GetGameObjectByName("Temple").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	//CreateGameObject("Mountain", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
	//GetGameObjectByName("Mountain").SetTag(TAG_Floor);
	//GetGameObjectByName("Mountain").SetPosition({ 300,7,150 });
	//GetGameObjectByName("Mountain").SetScale({ 200, 14, 100 });
	//c = GetGameObjectByName("Mountain").GetScale();
	//GetGameObjectByName("Mountain").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	//CreateGameObject("Mountain2", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
	//GetGameObjectByName("Mountain2").SetTag(TAG_Floor);
	//GetGameObjectByName("Mountain2").SetPosition({ 167.5, 2, 100 });
	//GetGameObjectByName("Mountain2").SetScale({ 65, 25, 20 });
	//c = GetGameObjectByName("Mountain2").GetScale();
	//GetGameObjectByName("Mountain2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	//CreateGameObject("Mountain3", MESHES::ROCKMedium, TEXTURES::PIERRE);
	//GetGameObjectByName("Mountain3").SetTag(TAG_Floor);
	//GetGameObjectByName("Mountain3").SetPosition({ 125, 2, 100 });
	//GetGameObjectByName("Mountain3").SetScale({ 10, 12, 3 });
	//c = GetGameObjectByName("Mountain3").GetScale();
	//GetGameObjectByName("Mountain3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	//{
	//	CreateGameObject("RTEST", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
	//	GetGameObjectByName("RTEST").SetTag(TAG_Floor);
	//	GetGameObjectByName("RTEST").SetPosition({ 175, 5, 25 });
	//	GetGameObjectByName("RTEST").SetScale({ 200, 5, 50 });
	//	GetGameObjectByName("RTEST").AddRotation({ 10,0,0 });
	//	c = GetGameObjectByName("RTEST").GetScale();
	//	GetGameObjectByName("RTEST").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	//	CreateGameObject("RTEST3", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
	//	GetGameObjectByName("RTEST3").SetTag(TAG_Floor);
	//	GetGameObjectByName("RTEST3").SetPosition({ 275, 5, 45 });
	//	GetGameObjectByName("RTEST3").SetScale({ 20, 5, 50 });
	//	GetGameObjectByName("RTEST3").AddRotation({ 40,0,0 });
	//	c = GetGameObjectByName("RTEST3").GetScale();
	//	GetGameObjectByName("RTEST3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	//	CreateGameObject("RTEST4", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
	//	GetGameObjectByName("RTEST4").SetTag(TAG_Floor);
	//	GetGameObjectByName("RTEST4").SetPosition({ 50, 5, 25 });
	//	GetGameObjectByName("RTEST4").SetScale({ 20, 5, 50 });
	//	GetGameObjectByName("RTEST4").AddRotation({ 50,0,0 });
	//	c = GetGameObjectByName("RTEST4").GetScale();
	//	GetGameObjectByName("RTEST4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	//	CreateGameObject("RTEST2", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
	//	GetGameObjectByName("RTEST2").SetTag(TAG_Floor);
	//	GetGameObjectByName("RTEST2").SetPosition({ 175, 2, 70 });
	//	GetGameObjectByName("RTEST2").SetScale({ 15, 10, 50 });
	//	GetGameObjectByName("RTEST2").AddRotation({ 10,0,-10 });
	//	c = GetGameObjectByName("RTEST2").GetScale();
	//	GetGameObjectByName("RTEST2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	//	CreateGameObject("Road1", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
	//	GetGameObjectByName("Road1").SetTag(TAG_Floor);
	//	GetGameObjectByName("Road1").SetPosition({ 175, -2, 50 });
	//	GetGameObjectByName("Road1").SetScale({ 200, 5, 10 });
	//	c = GetGameObjectByName("Road1").GetScale();
	//	GetGameObjectByName("Road1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	//	CreateGameObject("Road2", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
	//	GetGameObjectByName("Road2").SetTag(TAG_Floor);
	//	GetGameObjectByName("Road2").SetPosition({ 80, -2, 60 });
	//	GetGameObjectByName("Road2").SetScale({ 10, 5, 10 });
	//	c = GetGameObjectByName("Road2").GetScale();
	//	GetGameObjectByName("Road2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	//	CreateGameObject("Road3", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
	//	GetGameObjectByName("Road3").SetTag(TAG_Floor);
	//	GetGameObjectByName("Road3").SetPosition({ 75, -2, 80 });
	//	GetGameObjectByName("Road3").SetScale({ 75, 5, 30 });
	//	c = GetGameObjectByName("Road3").GetScale();
	//	GetGameObjectByName("Road3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));

	//	CreateGameObject("Tree", MESHES::MASTIC_1, TEXTURES::HERBE);
	//	GetGameObjectByName("Tree").SetTag(TAG_Floor);
	//	GetGameObjectByName("Tree").SetPosition({ 80, -2, 50 });
	//	GetGameObjectByName("Tree").SetScale({ 50, 50, 50 });
	//	c = GetGameObjectByName("Tree").GetScale();
	//	GetGameObjectByName("Tree").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ c.x / 2, c.y / 2, c.z / 2 })));
	//}



	///*CreateGameObject("Pond", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	//GetGameObjectByName("Pond").SetTag(TAG_Floor);
	//GetGameObjectByName("Pond").SetPosition({ 180, -2, 150 });
	//GetGameObjectByName("Pond").SetScale({ 40, 5, 80 });
	//c = GetGameObjectByName("Pond").GetScale();
	//GetGameObjectByName("Pond").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	//CreateGameObject("DownStream", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	//GetGameObjectByName("DownStream").SetTag(TAG_Floor);
	//GetGameObjectByName("DownStream").SetPosition({ 140, -2, 80 });
	//GetGameObjectByName("DownStream").SetScale({ 20, 5, 160 });
	//c = GetGameObjectByName("DownStream").GetScale();
	//GetGameObjectByName("DownStream").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));*/

	//CreateGameObject("Waterfall", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	//GetGameObjectByName("Waterfall").SetTag(TAG_Floor);
	//GetGameObjectByName("Waterfall").SetPosition({ 199.5, 7.5, 150 });
	//GetGameObjectByName("Waterfall").SetScale({ 1, 15, 40 });
	//c = GetGameObjectByName("Waterfall").GetScale();
	//GetGameObjectByName("Waterfall").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	////CreateGameObject("UpStream", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	////GetGameObjectByName("UpStream").SetTag(TAG_Floor);
	////GetGameObjectByName("UpStream").SetPosition({ 220, 14, 150 });
	////GetGameObjectByName("UpStream").SetScale({ 40, 2, 40 });
	////c = GetGameObjectByName("UpStream").GetScale();
	////GetGameObjectByName("UpStream").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	////CreateGameObject("UpStream1", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	////GetGameObjectByName("UpStream1").SetTag(TAG_Floor);
	////GetGameObjectByName("UpStream1").SetPosition({ 280, 14, 150 });
	////GetGameObjectByName("UpStream1").SetScale({ 80, 2, 20 });
	////c = GetGameObjectByName("UpStream1").GetScale();
	////GetGameObjectByName("UpStream1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	////CreateGameObject("UpStream2", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	////GetGameObjectByName("UpStream2").SetTag(TAG_Floor);
	////GetGameObjectByName("UpStream2").SetPosition({ 330, 14, 180 });
	////GetGameObjectByName("UpStream2").SetScale({ 20, 2, 80 });
	////c = GetGameObjectByName("UpStream2").GetScale();
	////GetGameObjectByName("UpStream2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));


	//CreateWaterGameObject("Pond");
	//GetGameObjectByName("Pond").SetPosition({ 180, 1, 150 });
	//GetGameObjectByName("Pond").SetScale({ 20, 0.5, 40 });

	//CreateWaterGameObject("DownStream");
	//GetGameObjectByName("DownStream").SetPosition({ 140, 1, 80 });
	//GetGameObjectByName("DownStream").SetScale({ 10, 0.5, 80 });

	////CreateWaterGameObject("Waterfall");
	////GetGameObjectByName("Waterfall").SetPosition({ 199.5, 7.5, 150 });
	////GetGameObjectByName("Waterfall").SetScale({ 1, 15, 40 });

	//CreateWaterGameObject("UpStream");
	//GetGameObjectByName("UpStream").SetPosition({ 220, 14.5, 150 });
	//GetGameObjectByName("UpStream").SetScale({ 20, 1, 20 });

	//CreateWaterGameObject("UpStream1");
	//GetGameObjectByName("UpStream1").SetPosition({ 280, 14.5, 150 });
	//GetGameObjectByName("UpStream1").SetScale({ 40, 1, 10 });

	//CreateWaterGameObject("UpStream2");
	//GetGameObjectByName("UpStream2").SetPosition({ 330, 14.5, 180 });
	//GetGameObjectByName("UpStream2").SetScale({ 10, 1, 40 });

	//portal = &CreateGameObject<Portals>(m_playerTest, this, 3);
	//portal->SetPosition({ 335, 2, 50 });
	////portal->SetPosition({ -10, 1, 10 });
	//portal->SetScale({ 1, 1, 0.5 });
	//portal->SetTexture(TEXTURES::EAU);

	CreateGameObject("Map");
	auto a = GetGameObjectByName("Map");
	a.SetMesh(MESHES::MAP);
	a.SetPosition({ 0,0,0 });
	a.SetScale({ 2,2,2 });

	//CreateGameObject("Temple", MESHES::TEMPLE);
	//GetGameObjectByName("Temple").SetPosition({ -185,0,-4 });
	//GetGameObjectByName("Temple").SetRotation({ 0,0,0,1 });
	//GetGameObjectByName("Temple").SetScale({ 2,3,2 });
	CreateGameObject("Temple", MESHES::TEMPLE);
	GetGameObjectByName("Temple").SetPosition({ -194,-6,21 });
	GetGameObjectByName("Temple").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temple").SetScale({ 2,2,2 });

	CreateGameObject("repere 1", MESHES::LOCAL_CUBE, 0);
	GetGameObjectByName("repere 1").SetPosition({ -72,-16,116 });
	GetGameObjectByName("repere 1").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("repere 1").SetScale({ 1,5,1 });

	CreateGameObject("repere 2", MESHES::LOCAL_CUBE, 0);
	GetGameObjectByName("repere 2").SetPosition({ 235,-17,-68 });
	GetGameObjectByName("repere 2").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("repere 2").SetScale({ 1,5,1 });

	CreateGameHitbox("HB 1"); // start zone 1
	GetGameObjectByName("HB 1").SetPosition({ 220,-23,-132 });
	GetGameObjectByName("HB 1").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB 1").SetScale({ 326,6,206 });
	GetGameObjectByName("HB 1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 163, 3, 103 })));
	GetGameObjectByName("HB 1").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB 1").SetTag(TAG_Environment);

	CreateGameHitbox("HB 2");// start zone 2
	GetGameObjectByName("HB 2").SetPosition({ 28,-23,-134 });
	GetGameObjectByName("HB 2").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB 2").SetScale({ 76,6,206 });
	GetGameObjectByName("HB 2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 38, 3, 103 })));
	GetGameObjectByName("HB 2").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB 2").SetTag(TAG_Environment);

	CreateGameHitbox("HB 3");// temple zone 
	GetGameObjectByName("HB 3").SetPosition({ -208,-23,-30 });
	GetGameObjectByName("HB 3").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB 3").SetScale({ 271,6,421 });
	GetGameObjectByName("HB 3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 135.5, 3, 210.5 })));
	GetGameObjectByName("HB 3").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB 3").SetTag(TAG_Environment);

	CreateGameHitbox("HB 4");// deep lac + river
	GetGameObjectByName("HB 4").SetPosition({ -5,-26,-29 });
	GetGameObjectByName("HB 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB 4").SetScale({ 156,6,416 });
	GetGameObjectByName("HB 4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 78, 3, 208 })));
	GetGameObjectByName("HB 4").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB 4").SetTag(TAG_Environment);

	CreateGameHitbox("HB 5");// RockWall
	GetGameObjectByName("HB 5").SetPosition({ 206,-3,-32 });
	GetGameObjectByName("HB 5").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB 5").SetScale({ 276,41,46 });
	GetGameObjectByName("HB 5").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 138, 20.5, 23 })));
	GetGameObjectByName("HB 5").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB 5").SetTag(TAG_Environment);


	CreateGameHitbox("HB_ 1"); // right side map 1
	GetGameObjectByName("HB_ 1").SetPosition({ 355,3,-153 });
	GetGameObjectByName("HB_ 1").SetRotation({ 0,-0.104528427,0,0.994521916 });
	GetGameObjectByName("HB_ 1").SetScale({ 11,51,176 });
	GetGameObjectByName("HB_ 1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 5.5, 25.5, 88 })));
	GetGameObjectByName("HB_ 1").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_ 1").SetTag(TAG_Environment);

	CreateGameHitbox("HB_ 2");// right side map 2
	GetGameObjectByName("HB_ 2").SetPosition({ 340,31,47 });
	GetGameObjectByName("HB_ 2").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_ 2").SetScale({ 16,111,246 });
	GetGameObjectByName("HB_ 2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8, 55.5, 123 })));
	GetGameObjectByName("HB_ 2").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_ 2").SetTag(TAG_Environment);

	CreateGameHitbox("HB_ 3");// far side map 1 (up hill)
	GetGameObjectByName("HB_ 3").SetPosition({ 303,31,168 });
	GetGameObjectByName("HB_ 3").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_ 3").SetScale({ 71,86,11 });
	GetGameObjectByName("HB_ 3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 35.5, 43, 5.5 })));
	GetGameObjectByName("HB_ 3").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_ 3").SetTag(TAG_Environment);

	CreateGameHitbox("HB_ 4");// far side map 2
	GetGameObjectByName("HB_ 4").SetPosition({ 210,31,161 });
	GetGameObjectByName("HB_ 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_ 4").SetScale({ 133,86,11 });
	GetGameObjectByName("HB_ 4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 66.5, 43, 5.5 })));
	GetGameObjectByName("HB_ 4").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_ 4").SetTag(TAG_Environment);

	CreateGameHitbox("HB_ 5");// far side map 3
	GetGameObjectByName("HB_ 5").SetPosition({ 69,31,163 });
	GetGameObjectByName("HB_ 5").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_ 5").SetScale({ 153,106,11 });
	GetGameObjectByName("HB_ 5").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 76.5, 53, 5.5 })));
	GetGameObjectByName("HB_ 5").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_ 5").SetTag(TAG_Environment);

	CreateGameHitbox("HB_ 6");// far side map 4
	GetGameObjectByName("HB_ 6").SetPosition({ -158,19,156 });
	GetGameObjectByName("HB_ 6").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_ 6").SetScale({ 313,106,11 });
	GetGameObjectByName("HB_ 6").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 156.5, 53, 5.5 })));
	GetGameObjectByName("HB_ 6").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_ 6").SetTag(TAG_Environment);

	CreateGameHitbox("HB_ 7");// left side map
	GetGameObjectByName("HB_ 7").SetPosition({ -307,19,-18 });
	GetGameObjectByName("HB_ 7").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_ 7").SetScale({ 18,106,436 });
	GetGameObjectByName("HB_ 7").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 9, 53, 218 })));
	GetGameObjectByName("HB_ 7").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_ 7").SetTag(TAG_Environment);

	CreateGameHitbox("HB_ 8");// close side map 1 (down hill)
	GetGameObjectByName("HB_ 8").SetPosition({ 34,2,-238 });
	GetGameObjectByName("HB_ 8").SetRotation({ 0,0.713250458,0,0.700909257 });
	GetGameObjectByName("HB_ 8").SetScale({ 18,96,741 });
	GetGameObjectByName("HB_ 8").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 9, 48, 370.5 })));
	GetGameObjectByName("HB_ 8").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_ 8").SetTag(TAG_Environment);

	
	// HITBOXES TEMPLE
	CreateGameHitbox("HB_Temple 1");
	GetGameObjectByName("HB_Temple 1").SetPosition({ -127,-13,-75 });
	GetGameObjectByName("HB_Temple 1").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 1").SetScale({ 59,18,3 });
	GetGameObjectByName("HB_Temple 1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 29.5, 9, 1.5 })));
	GetGameObjectByName("HB_Temple 1").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 1").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 2");
	GetGameObjectByName("HB_Temple 2").SetPosition({ -261,-13,-72 });
	GetGameObjectByName("HB_Temple 2").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 2").SetScale({ 59,18,3 });
	GetGameObjectByName("HB_Temple 2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 29.5, 9, 1.5 })));
	GetGameObjectByName("HB_Temple 2").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 2").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 3");
	GetGameObjectByName("HB_Temple 3").SetPosition({ -222,-12,117 });
	GetGameObjectByName("HB_Temple 3").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 3").SetScale({ 79,16,3 });
	GetGameObjectByName("HB_Temple 3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 39.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 3").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 3").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 4");
	GetGameObjectByName("HB_Temple 4").SetPosition({ -106,-12,114 });
	GetGameObjectByName("HB_Temple 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 4").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 4").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 4").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 5");
	GetGameObjectByName("HB_Temple 5").SetPosition({ -175,-12,114 });
	GetGameObjectByName("HB_Temple 5").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 5").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 5").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 5").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 5").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 6");
	GetGameObjectByName("HB_Temple 6").SetPosition({ -281,-12,117 });
	GetGameObjectByName("HB_Temple 6").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 6").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 6").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 6").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 6").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 7");
	GetGameObjectByName("HB_Temple 7").SetPosition({ -212,-12,-72 });
	GetGameObjectByName("HB_Temple 7").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 7").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 7").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 7").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 7").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 8");
	GetGameObjectByName("HB_Temple 8").SetPosition({ -175,-12,-75 });
	GetGameObjectByName("HB_Temple 8").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 8").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 8").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 8").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 8").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 9");
	GetGameObjectByName("HB_Temple 9").SetPosition({ -130,5,-51 });
	GetGameObjectByName("HB_Temple 9").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 9").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 9").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 9").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 9").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 10");
	GetGameObjectByName("HB_Temple 10").SetPosition({ -216,5,-48 });
	GetGameObjectByName("HB_Temple 10").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 10").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 10").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 10").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 10").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 11");
	GetGameObjectByName("HB_Temple 11").SetPosition({ -259,5,39 });
	GetGameObjectByName("HB_Temple 11").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 11").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 11").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 11").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 11").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 12");
	GetGameObjectByName("HB_Temple 12").SetPosition({ -259,5,8 });
	GetGameObjectByName("HB_Temple 12").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 12").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 12").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 12").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 12").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 13");
	GetGameObjectByName("HB_Temple 13").SetPosition({ -258,5,94 });
	GetGameObjectByName("HB_Temple 13").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 13").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 13").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 13").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 13").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 14");
	GetGameObjectByName("HB_Temple 14").SetPosition({ -130,5,90 });
	GetGameObjectByName("HB_Temple 14").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 14").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 14").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 14").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 14").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 15");
	GetGameObjectByName("HB_Temple 15").SetPosition({ -129,5,35 });
	GetGameObjectByName("HB_Temple 15").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 15").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 15").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 15").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 15").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 16");
	GetGameObjectByName("HB_Temple 16").SetPosition({ -129,5,4 });
	GetGameObjectByName("HB_Temple 16").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 16").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 16").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 16").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 16").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 17");
	GetGameObjectByName("HB_Temple 17").SetPosition({ -141,-13,114 });
	GetGameObjectByName("HB_Temple 17").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 17").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 17").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 15, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 17").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 17").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 18");
	GetGameObjectByName("HB_Temple 18").SetPosition({ -126,-13,99 });
	GetGameObjectByName("HB_Temple 18").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 18").SetScale({ 31,16,3 });
	GetGameObjectByName("HB_Temple 18").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 15.5, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 18").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 18").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 19");
	GetGameObjectByName("HB_Temple 19").SetPosition({ -168,-13,99 });
	GetGameObjectByName("HB_Temple 19").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 19").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 19").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.750005722, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 19").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 19").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 20");
	GetGameObjectByName("HB_Temple 20").SetPosition({ -219,-13,104 });
	GetGameObjectByName("HB_Temple 20").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 20").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 20").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.850008011, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 20").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 20").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 21");
	GetGameObjectByName("HB_Temple 21").SetPosition({ -260,-13,104 });
	GetGameObjectByName("HB_Temple 21").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 21").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 21").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.850008011, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 21").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 21").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 22");
	GetGameObjectByName("HB_Temple 22").SetPosition({ -261,-13,-57 });
	GetGameObjectByName("HB_Temple 22").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 22").SetScale({ 31,16,3 });
	GetGameObjectByName("HB_Temple 22").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 15.4500103, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 22").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 22").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 23");
	GetGameObjectByName("HB_Temple 23").SetPosition({ -127,-13,-62 });
	GetGameObjectByName("HB_Temple 23").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 23").SetScale({ 29,16,3 });
	GetGameObjectByName("HB_Temple 23").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.700016022, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 23").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 23").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 24");
	GetGameObjectByName("HB_Temple 24").SetPosition({ -168,-13,-62 });
	GetGameObjectByName("HB_Temple 24").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 24").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 24").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.850019455, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 24").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 24").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 25");
	GetGameObjectByName("HB_Temple 25").SetPosition({ -219,-13,-57 });
	GetGameObjectByName("HB_Temple 25").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 25").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 25").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.850019455, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 25").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 25").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 26");
	GetGameObjectByName("HB_Temple 26").SetPosition({ -165,4,-51 });
	GetGameObjectByName("HB_Temple 26").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 26").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 26").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.850019455, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 26").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 26").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 27");
	GetGameObjectByName("HB_Temple 27").SetPosition({ -251,4,-48 });
	GetGameObjectByName("HB_Temple 27").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 27").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 27").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 27").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 27").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 28");
	GetGameObjectByName("HB_Temple 28").SetPosition({ -164,4,90 });
	GetGameObjectByName("HB_Temple 28").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 28").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 28").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 28").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 28").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 29");
	GetGameObjectByName("HB_Temple 29").SetPosition({ -223,4,93 });
	GetGameObjectByName("HB_Temple 29").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 29").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 29").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 29").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 29").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 30");
	GetGameObjectByName("HB_Temple 30").SetPosition({ -162,22,-25 });
	GetGameObjectByName("HB_Temple 30").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 30").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 30").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 30").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 30").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 31");
	GetGameObjectByName("HB_Temple 31").SetPosition({ -226,22,-24 });
	GetGameObjectByName("HB_Temple 31").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 31").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 31").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 31").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 31").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 32");
	GetGameObjectByName("HB_Temple 32").SetPosition({ -226,22,66 });
	GetGameObjectByName("HB_Temple 32").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 32").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 32").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 32").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 32").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 33");
	GetGameObjectByName("HB_Temple 33").SetPosition({ -162,22,66 });
	GetGameObjectByName("HB_Temple 33").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 33").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 33").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 33").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 33").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 34");
	GetGameObjectByName("HB_Temple 34").SetPosition({ -148,22,-11 });
	GetGameObjectByName("HB_Temple 34").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 34").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 34").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 34").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 34").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 35");
	GetGameObjectByName("HB_Temple 35").SetPosition({ -148,22,53 });
	GetGameObjectByName("HB_Temple 35").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 35").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 35").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 35").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 35").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 36");
	GetGameObjectByName("HB_Temple 36").SetPosition({ -240,22,52 });
	GetGameObjectByName("HB_Temple 36").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 36").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 36").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 36").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 36").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 37");
	GetGameObjectByName("HB_Temple 37").SetPosition({ -239,22,-11 });
	GetGameObjectByName("HB_Temple 37").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 37").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 37").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 37").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 37").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 38");
	GetGameObjectByName("HB_Temple 38").SetPosition({ -123,5,76 });
	GetGameObjectByName("HB_Temple 38").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 38").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 38").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 38").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 38").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 39");
	GetGameObjectByName("HB_Temple 39").SetPosition({ -123,5,-10 });
	GetGameObjectByName("HB_Temple 39").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 39").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 39").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 39").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 39").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 40");
	GetGameObjectByName("HB_Temple 40").SetPosition({ -264,5,-6 });
	GetGameObjectByName("HB_Temple 40").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 40").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 40").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 40").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 40").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 41");
	GetGameObjectByName("HB_Temple 41").SetPosition({ -265,5,80 });
	GetGameObjectByName("HB_Temple 41").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 41").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 41").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 41").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 41").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 42");
	GetGameObjectByName("HB_Temple 42").SetPosition({ -275,-13,-44 });
	GetGameObjectByName("HB_Temple 42").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 42").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 42").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 42").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 42").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 43");
	GetGameObjectByName("HB_Temple 43").SetPosition({ -114,-13,-48 });
	GetGameObjectByName("HB_Temple 43").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 43").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 43").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 43").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 43").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 44");
	GetGameObjectByName("HB_Temple 44").SetPosition({ -114,-13,-6 });
	GetGameObjectByName("HB_Temple 44").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 44").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 44").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 44").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 44").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 45");
	GetGameObjectByName("HB_Temple 45").SetPosition({ -113,-13,44 });
	GetGameObjectByName("HB_Temple 45").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 45").SetScale({ 31,16,3 });
	GetGameObjectByName("HB_Temple 45").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 15.450021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 45").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 45").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 46");
	GetGameObjectByName("HB_Temple 46").SetPosition({ -113,-13,86 });
	GetGameObjectByName("HB_Temple 46").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 46").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 46").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 46").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 46").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 47");
	GetGameObjectByName("HB_Temple 47").SetPosition({ -274,-13,90 });
	GetGameObjectByName("HB_Temple 47").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 47").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 47").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 47").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 47").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 48");
	GetGameObjectByName("HB_Temple 48").SetPosition({ -274,-13,48 });
	GetGameObjectByName("HB_Temple 48").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 48").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 48").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 48").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 48").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 49");
	GetGameObjectByName("HB_Temple 49").SetPosition({ -275,-13,-2 });
	GetGameObjectByName("HB_Temple 49").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 49").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 49").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	GetGameObjectByName("HB_Temple 49").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 49").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 50");
	GetGameObjectByName("HB_Temple 50").SetPosition({ -100,-12,72 });
	GetGameObjectByName("HB_Temple 50").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 50").SetScale({ 3,16,86 });
	GetGameObjectByName("HB_Temple 50").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 43 })));
	GetGameObjectByName("HB_Temple 50").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 50").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 51");
	GetGameObjectByName("HB_Temple 51").SetPosition({ -99,-12,-33 });
	GetGameObjectByName("HB_Temple 51").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 51").SetScale({ 3,16,86 });
	GetGameObjectByName("HB_Temple 51").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 43 })));
	GetGameObjectByName("HB_Temple 51").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 51").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 52");
	GetGameObjectByName("HB_Temple 52").SetPosition({ -288,-12,-29 });
	GetGameObjectByName("HB_Temple 52").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 52").SetScale({ 3,16,86 });
	GetGameObjectByName("HB_Temple 52").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 43 })));
	GetGameObjectByName("HB_Temple 52").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 52").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 53");
	GetGameObjectByName("HB_Temple 53").SetPosition({ -288,-12,76 });
	GetGameObjectByName("HB_Temple 53").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 53").SetScale({ 3,16,86 });
	GetGameObjectByName("HB_Temple 53").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 43 })));
	GetGameObjectByName("HB_Temple 53").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 53").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 54");
	GetGameObjectByName("HB_Temple 54").SetPosition({ -123,4,42 });
	GetGameObjectByName("HB_Temple 54").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 54").SetScale({ 3,16,16 });
	GetGameObjectByName("HB_Temple 54").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 8 })));
	GetGameObjectByName("HB_Temple 54").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 54").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 55");
	GetGameObjectByName("HB_Temple 55").SetPosition({ -123,4,-45 });
	GetGameObjectByName("HB_Temple 55").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 55").SetScale({ 3,16,16 });
	GetGameObjectByName("HB_Temple 55").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 8.199993134 })));
	GetGameObjectByName("HB_Temple 55").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 55").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 56");
	GetGameObjectByName("HB_Temple 56").SetPosition({ -265,4,45 });
	GetGameObjectByName("HB_Temple 56").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 56").SetScale({ 3,16,16 });
	GetGameObjectByName("HB_Temple 56").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 8.199993134 })));
	GetGameObjectByName("HB_Temple 56").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 56").SetTag(TAG_Environment);

	CreateGameHitbox("HB_Temple 57");
	GetGameObjectByName("HB_Temple 57").SetPosition({ -264,4,-41 });
	GetGameObjectByName("HB_Temple 57").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 57").SetScale({ 3,16,16 });
	GetGameObjectByName("HB_Temple 57").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 8.199993134 })));
	GetGameObjectByName("HB_Temple 57").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB_Temple 57").SetTag(TAG_Environment);

	//
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
			ss << "Perf: avgMs=" << avgMs << " ms, avgFPS=" << fps << " DrawCalls=" << g_drawCalls << "\n";
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