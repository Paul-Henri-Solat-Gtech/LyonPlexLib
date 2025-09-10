#include "pch.h"
#include "GameScene.h"
#include "Utils.h"
#include "Boulder.h"
#include "OliveTree.h"
//debug
#include <psapi.h>

//Utils::Vector3 POSITION_CHAMPS = { 5, 0, 32.5 };

// { 325, -2, 50 }
XMFLOAT3 POSITION_CHAMPS = { 325, -2, 50 };

void GameScene::Start()
{
	m_pauseIsOpen = false;


	m_cam.Init(mp_ecsManager, this);
	m_cam.AddComponent<CameraComponent>(new CameraComponent());
	GetEcsManager()->RemoveComponent<MeshComponent>(m_cam.GetEntity());

	// fps cam
	m_fpsCam.Init(m_cam, mp_sceneManager->GetWindow());
	m_fpsCam.SetAlwaysActive(true);

	m_playerWalkSpeed = 3.f;
	m_playerRunSpeed = 6.f;
	m_playerSpeed = m_playerWalkSpeed;

	// Test player + stateMachine
	m_playerTest.Init(mp_ecsManager, mp_sceneManager->GetGameManager(), this, m_cam);
	SetParent(m_cam, m_playerTest);

	m_cam.SetPosition({ 0, m_playerTest.GetScale().y / 2, 0 });

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
	GetGameObjectByName("HB 3").SetPosition({ -208,-20,-30 });
	GetGameObjectByName("HB 3").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB 3").SetScale({ 271,2,421 });
	GetGameObjectByName("HB 3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 135.5, 1, 210.5 })));
	GetGameObjectByName("HB 3").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB 3").SetTag(TAG_Environment);

	CreateGameHitbox("HB 4");// deep lac + river
	GetGameObjectByName("HB 4").SetPosition({ -5,-24,-29 });
	GetGameObjectByName("HB 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB 4").SetScale({ 156,2,416 });
	GetGameObjectByName("HB 4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 78, 1, 208 })));
	GetGameObjectByName("HB 4").AddComponent<Tag_World>(new Tag_World());
	GetGameObjectByName("HB 4").SetTag(TAG_Environment);


	XMFLOAT3 position = { 30.f,-20,10 };




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

	//CreateGameHitbox("HB_ 8");// close side map 1 (down hill)
	//GetGameObjectByName("HB_ 8").SetPosition({ 34,2,-238 });
	//GetGameObjectByName("HB_ 8").SetRotation({ 0,0.713250458,0,0.700909257 });
	//GetGameObjectByName("HB_ 8").SetScale({ 18,96,741 });
	//GetGameObjectByName("HB_ 8").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 9, 48, 370.5 })));
	//GetGameObjectByName("HB_ 8").AddComponent<Tag_World>(new Tag_World());
	//GetGameObjectByName("HB_ 8").SetTag(TAG_Environment);


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

	CreateGameHitbox("HB_T_suite 1");
	GetGameObjectByName("HB_T_suite 1").SetPosition({ -116.240844727,-3.04857111,-33.811027527 });
	GetGameObjectByName("HB_T_suite 1").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 1").SetScale({ 41.020000458,2.019999981,90.020004272 });
	GetGameObjectByName("HB_T_suite 1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 20.510000229, 1.00999999, 45.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 3");
	GetGameObjectByName("HB_T_suite 3").SetPosition({ -116.585662842,-3.04857111,71.859550476 });
	GetGameObjectByName("HB_T_suite 3").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 3").SetScale({ 41.020000458,2.019999981,90.020004272 });
	GetGameObjectByName("HB_T_suite 3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 20.510000229, 1.00999999, 45.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 4");
	GetGameObjectByName("HB_T_suite 4").SetPosition({ -271.021453857,-3.04857111,-30.085664749 });
	GetGameObjectByName("HB_T_suite 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 4").SetScale({ 41.020000458,2.019999981,90.020004272 });
	GetGameObjectByName("HB_T_suite 4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 20.510000229, 1.00999999, 45.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 5");
	GetGameObjectByName("HB_T_suite 5").SetPosition({ -271.206054688,-3.04857111,75.994880676 });
	GetGameObjectByName("HB_T_suite 5").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 5").SetScale({ 41.020000458,2.019999981,90.020004272 });
	GetGameObjectByName("HB_T_suite 5").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 20.510000229, 1.00999999, 45.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 6");
	GetGameObjectByName("HB_T_suite 6").SetPosition({ -161.185165405,-3.02259922,-58.053150177 });
	GetGameObjectByName("HB_T_suite 6").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 6").SetScale({ 49.020000458,2.019999981,41.020004272 });
	GetGameObjectByName("HB_T_suite 6").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 24.510000229, 1.00999999, 20.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 7");
	GetGameObjectByName("HB_T_suite 7").SetPosition({ -161.249969482,-3.02259922,96.368858337 });
	GetGameObjectByName("HB_T_suite 7").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 7").SetScale({ 49.020000458,2.019999981,41.020004272 });
	GetGameObjectByName("HB_T_suite 7").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 24.510000229, 1.00999999, 20.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 8");
	GetGameObjectByName("HB_T_suite 8").SetPosition({ -226.159378052,-3.02259922,100.080795288 });
	GetGameObjectByName("HB_T_suite 8").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 8").SetScale({ 49.020000458,2.019999981,41.020004272 });
	GetGameObjectByName("HB_T_suite 8").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 24.510000229, 1.00999999, 20.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 9");
	GetGameObjectByName("HB_T_suite 9").SetPosition({ -226.342651367,-3.02259922,-54.448307037 });
	GetGameObjectByName("HB_T_suite 9").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 9").SetScale({ 49.020000458,2.019999981,41.020004272 });
	GetGameObjectByName("HB_T_suite 9").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 24.510000229, 1.00999999, 20.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 10");
	GetGameObjectByName("HB_T_suite 10").SetPosition({ -134.130508423,13.72262001,60.743515015 });
	GetGameObjectByName("HB_T_suite 10").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 10").SetScale({ 29.020000458,2.019999981,66.020004272 });
	GetGameObjectByName("HB_T_suite 10").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.510000229, 1.00999999, 33.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 11");
	GetGameObjectByName("HB_T_suite 11").SetPosition({ -133.577651978,13.72262001,-23.204435349 });
	GetGameObjectByName("HB_T_suite 11").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 11").SetScale({ 29.020000458,2.019999981,66.020004272 });
	GetGameObjectByName("HB_T_suite 11").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.510000229, 1.00999999, 33.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 12");
	GetGameObjectByName("HB_T_suite 12").SetPosition({ -253.671920776,13.72262001,-18.691040039 });
	GetGameObjectByName("HB_T_suite 12").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 12").SetScale({ 29.020000458,2.019999981,66.020004272 });
	GetGameObjectByName("HB_T_suite 12").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.510000229, 1.00999999, 33.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 13");
	GetGameObjectByName("HB_T_suite 13").SetPosition({ -254.026412964,13.72262001,65.354766846 });
	GetGameObjectByName("HB_T_suite 13").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 13").SetScale({ 29.020000458,2.019999981,66.020004272 });
	GetGameObjectByName("HB_T_suite 13").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.510000229, 1.00999999, 33.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 15");
	GetGameObjectByName("HB_T_suite 15").SetPosition({ -222.184890747,13.72163105,82.829498291 });
	GetGameObjectByName("HB_T_suite 15").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 15").SetScale({ 39.020000458,2.019999981,31.020004272 });
	GetGameObjectByName("HB_T_suite 15").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 19.510000229, 1.00999999, 15.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 16");
	GetGameObjectByName("HB_T_suite 16").SetPosition({ -165.030487061,13.72163105,78.251525879 });
	GetGameObjectByName("HB_T_suite 16").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 16").SetScale({ 39.020000458,2.019999981,31.020004272 });
	GetGameObjectByName("HB_T_suite 16").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 19.510000229, 1.00999999, 15.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 17");
	GetGameObjectByName("HB_T_suite 17").SetPosition({ -165.429290771,13.71800518,-40.653587341 });
	GetGameObjectByName("HB_T_suite 17").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 17").SetScale({ 39.020000458,2.019999981,31.020004272 });
	GetGameObjectByName("HB_T_suite 17").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 19.510000229, 1.00999999, 15.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 18");
	GetGameObjectByName("HB_T_suite 18").SetPosition({ -222.511566162,13.71800518,-36.133331299 });
	GetGameObjectByName("HB_T_suite 18").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 18").SetScale({ 39.020000458,2.019999981,31.020004272 });
	GetGameObjectByName("HB_T_suite 18").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 19.510000229, 1.00999999, 15.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 19");
	GetGameObjectByName("HB_T_suite 19").SetPosition({ -178.514648438,5.46626091,-43.518615723 });
	GetGameObjectByName("HB_T_suite 19").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 19").SetScale({ 2,15,12 });
	GetGameObjectByName("HB_T_suite 19").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1, 7.5, 6 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 20");
	GetGameObjectByName("HB_T_suite 20").SetPosition({ -209.276000977,5.46626091,-40.153446198 });
	GetGameObjectByName("HB_T_suite 20").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 20").SetScale({ 2,15,12 });
	GetGameObjectByName("HB_T_suite 20").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1, 7.5, 6 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 21");
	GetGameObjectByName("HB_T_suite 21").SetPosition({ -209.25050354,5.46626091,85.676063538 });
	GetGameObjectByName("HB_T_suite 21").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 21").SetScale({ 2,15,12 });
	GetGameObjectByName("HB_T_suite 21").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1, 7.5, 6 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 23");
	GetGameObjectByName("HB_T_suite 23").SetPosition({ -178.272338867,5.46626091,81.982406616 });
	GetGameObjectByName("HB_T_suite 23").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 23").SetScale({ 2,15,12 });
	GetGameObjectByName("HB_T_suite 23").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1, 7.5, 6 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 24");
	GetGameObjectByName("HB_T_suite 24").SetPosition({ -250.947143555,-1.396932125,-12.716756821 });
	GetGameObjectByName("HB_T_suite 24").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 24").SetScale({ 1,4,42 });
	GetGameObjectByName("HB_T_suite 24").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 0.5, 2, 21 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 25");
	GetGameObjectByName("HB_T_suite 25").SetPosition({ -250.99571228,-1.396932125,58.372711182 });
	GetGameObjectByName("HB_T_suite 25").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 25").SetScale({ 1,4,42 });
	GetGameObjectByName("HB_T_suite 25").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 0.5, 2, 21 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 26");
	GetGameObjectByName("HB_T_suite 26").SetPosition({ -137.026489258,-1.396932125,-16.265182495 });
	GetGameObjectByName("HB_T_suite 26").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 26").SetScale({ 1,4,42 });
	GetGameObjectByName("HB_T_suite 26").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 0.5, 2, 21 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 27");
	GetGameObjectByName("HB_T_suite 27").SetPosition({ -136.784561157,-1.396932125,54.801616669 });
	GetGameObjectByName("HB_T_suite 27").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 27").SetScale({ 1,4,42 });
	GetGameObjectByName("HB_T_suite 27").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 0.5, 2, 21 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 29");
	GetGameObjectByName("HB_T_suite 29").SetPosition({ -229.908630371,-1.41100502,-33.778793335 });
	GetGameObjectByName("HB_T_suite 29").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 29").SetScale({ 43,4,1 });
	GetGameObjectByName("HB_T_suite 29").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 21.5, 2, 0.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 30");
	GetGameObjectByName("HB_T_suite 30").SetPosition({ -158.026245117,-1.41100502,-37.509101868 });
	GetGameObjectByName("HB_T_suite 30").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 30").SetScale({ 43,4,1 });
	GetGameObjectByName("HB_T_suite 30").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 21.5, 2, 0.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 31");
	GetGameObjectByName("HB_T_suite 31").SetPosition({ -157.802932739,-1.41100502,75.952987671 });
	GetGameObjectByName("HB_T_suite 31").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 31").SetScale({ 43,4,1 });
	GetGameObjectByName("HB_T_suite 31").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 21.5, 2, 0.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 32");
	GetGameObjectByName("HB_T_suite 32").SetPosition({ -229.949813843,-1.41100502,79.702590942 });
	GetGameObjectByName("HB_T_suite 32").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 32").SetScale({ 43,4,1 });
	GetGameObjectByName("HB_T_suite 32").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 21.5, 2, 0.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 34");
	GetGameObjectByName("HB_T_suite 34").SetPosition({ -194.001220703,32.213443756,59.79094696 });
	GetGameObjectByName("HB_T_suite 34").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 34").SetScale({ 96,1,16 });
	GetGameObjectByName("HB_T_suite 34").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 48, 0.5, 8 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));

	CreateGameHitbox("HB_T_suite 36");
	GetGameObjectByName("HB_T_suite 36").SetPosition({ -155.857131958,32.196475983,21.051273346 });
	GetGameObjectByName("HB_T_suite 36").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 36").SetScale({ 19,1,66 });
	GetGameObjectByName("HB_T_suite 36").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 9.5, 0.5, 33 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 37");
	GetGameObjectByName("HB_T_suite 37").SetPosition({ -232.756973267,32.196475983,22.633777618 });
	GetGameObjectByName("HB_T_suite 37").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 37").SetScale({ 19,1,66 });
	GetGameObjectByName("HB_T_suite 37").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 9.5, 0.5, 33 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));


	CreateGameHitbox("HB_T_suite2 4");
	GetGameObjectByName("HB_T_suite2 4").SetPosition({ -274.899505615,-11.484270096,-2.228993893 });
	GetGameObjectByName("HB_T_suite2 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 4").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 5");
	GetGameObjectByName("HB_T_suite2 5").SetPosition({ -273.622650146,-11.484270096,48.560863495 });
	GetGameObjectByName("HB_T_suite2 5").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 5").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 5").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 6");
	GetGameObjectByName("HB_T_suite2 6").SetPosition({ -273.612091064,-11.484270096,90.027816772 });
	GetGameObjectByName("HB_T_suite2 6").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 6").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 6").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 7");
	GetGameObjectByName("HB_T_suite2 7").SetPosition({ -112.599578857,-11.484270096,44.185222626 });
	GetGameObjectByName("HB_T_suite2 7").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 7").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 7").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 8");
	GetGameObjectByName("HB_T_suite2 8").SetPosition({ -112.63419342,-11.484270096,85.598518372 });
	GetGameObjectByName("HB_T_suite2 8").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 8").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 8").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 9");
	GetGameObjectByName("HB_T_suite2 9").SetPosition({ -113.955566406,-11.484270096,-6.917423725 });
	GetGameObjectByName("HB_T_suite2 9").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 9").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 9").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 10");
	GetGameObjectByName("HB_T_suite2 10").SetPosition({ -122.988365173,4.453486919,-10.090456009 });
	GetGameObjectByName("HB_T_suite2 10").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 10").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 10").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 11");
	GetGameObjectByName("HB_T_suite2 11").SetPosition({ -123.226417542,4.453486919,75.959533691 });
	GetGameObjectByName("HB_T_suite2 11").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 11").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 11").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 12");
	GetGameObjectByName("HB_T_suite2 12").SetPosition({ -148.065490723,22.411590576,52.032306671 });
	GetGameObjectByName("HB_T_suite2 12").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 12").SetScale({ 3,17,31 });
	GetGameObjectByName("HB_T_suite2 12").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8.5, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 13");
	GetGameObjectByName("HB_T_suite2 13").SetPosition({ -148.069961548,22.411590576,-10.634102821 });
	GetGameObjectByName("HB_T_suite2 13").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 13").SetScale({ 3,17,31 });
	GetGameObjectByName("HB_T_suite2 13").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8.5, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 14");
	GetGameObjectByName("HB_T_suite2 14").SetPosition({ -239.49961853,22.411590576,-9.832740784 });
	GetGameObjectByName("HB_T_suite2 14").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 14").SetScale({ 3,17,31 });
	GetGameObjectByName("HB_T_suite2 14").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8.5, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 15");
	GetGameObjectByName("HB_T_suite2 15").SetPosition({ -239.695678711,22.411590576,51.847362518 });
	GetGameObjectByName("HB_T_suite2 15").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 15").SetScale({ 3,17,31 });
	GetGameObjectByName("HB_T_suite2 15").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8.5, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 16");
	GetGameObjectByName("HB_T_suite2 16").SetPosition({ -193.999481201,32.187534332,-15.832008362 });
	GetGameObjectByName("HB_T_suite2 16").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 16").SetScale({ 96,1,21 });
	GetGameObjectByName("HB_T_suite2 16").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 48, 0.5, 10.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));





	// pour grimper sur temple
	CreateGameHitbox("Temp 0");
	GetGameObjectByName("Temp 0").SetPosition({ -157,-17,28 });
	GetGameObjectByName("Temp 0").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 0").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 0").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 1");
	GetGameObjectByName("Temp 1").SetPosition({ -156,-12,34 });
	GetGameObjectByName("Temp 1").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 1").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 2");
	GetGameObjectByName("Temp 2").SetPosition({ -156,-7,42 });
	GetGameObjectByName("Temp 2").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 2").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 3");
	GetGameObjectByName("Temp 3").SetPosition({ -150,-4,42 });
	GetGameObjectByName("Temp 3").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 3").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 4");
	GetGameObjectByName("Temp 4").SetPosition({ -144,-4,42 });
	GetGameObjectByName("Temp 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 4").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 5");
	GetGameObjectByName("Temp 5").SetPosition({ -140,-4,42 });
	GetGameObjectByName("Temp 5").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 5").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 5").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 7");
	GetGameObjectByName("Temp 7").SetPosition({ -162,-7,35 });
	GetGameObjectByName("Temp 7").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 7").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 7").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 9");
	GetGameObjectByName("Temp 9").SetPosition({ -169,-6,35 });
	GetGameObjectByName("Temp 9").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 9").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 9").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 10");
	GetGameObjectByName("Temp 10").SetPosition({ -175,-6,34 });
	GetGameObjectByName("Temp 10").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 10").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 10").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 11");
	GetGameObjectByName("Temp 11").SetPosition({ -180,-6,33 });
	GetGameObjectByName("Temp 11").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 11").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 11").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 12");
	GetGameObjectByName("Temp 12").SetPosition({ -187,-2,33 });
	GetGameObjectByName("Temp 12").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 12").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 12").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 13");
	GetGameObjectByName("Temp 13").SetPosition({ -193,4,33 });
	GetGameObjectByName("Temp 13").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 13").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 13").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 14");
	GetGameObjectByName("Temp 14").SetPosition({ -199,10,33 });
	GetGameObjectByName("Temp 14").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 14").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 14").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 15");
	GetGameObjectByName("Temp 15").SetPosition({ -206,16,34 });
	GetGameObjectByName("Temp 15").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 15").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 15").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 16");
	GetGameObjectByName("Temp 16").SetPosition({ -212,21,35 });
	GetGameObjectByName("Temp 16").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 16").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 16").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 17");
	GetGameObjectByName("Temp 17").SetPosition({ -218,27,34 });
	GetGameObjectByName("Temp 17").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 17").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 17").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 18");
	GetGameObjectByName("Temp 18").SetPosition({ -217,31,28 });
	GetGameObjectByName("Temp 18").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 18").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 18").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 19");
	GetGameObjectByName("Temp 19").SetPosition({ -151,-19,22 });
	GetGameObjectByName("Temp 19").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 19").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 19").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("Temp 20");
	GetGameObjectByName("Temp 20").SetPosition({ -151,-14,29 });
	GetGameObjectByName("Temp 20").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp 20").SetScale({ 6,6,6 });
	GetGameObjectByName("Temp 20").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	//



	CreateGameObject("Bridge 0", MESHES::BRIDGE, 4294967295);
	GetGameObjectByName("Bridge 0").SetPosition({ -32,-18,-163 });
	GetGameObjectByName("Bridge 0").SetRotation({ 0,-0.078459084,0,0.996917367 });
	GetGameObjectByName("Bridge 0").SetScale({ 1,1,2 });

	CreateGameObject("RockWall 1", 17, 4294967295);
	GetGameObjectByName("RockWall 1").SetPosition({ 57,2,-19 });
	GetGameObjectByName("RockWall 1").SetRotation({ 0,-0.078459084,0,0.996917367 });
	GetGameObjectByName("RockWall 1").SetScale({ 25,16,26 });
	CreateGameObject("RockWall 2", 17, 4294967295);
	GetGameObjectByName("RockWall 2").SetPosition({ 10,2,-58 });
	GetGameObjectByName("RockWall 2").SetRotation({ 0,-0.544638991,0,0.838670671 });
	GetGameObjectByName("RockWall 2").SetScale({ 29,25,30 });
	CreateGameObject("RockWall 3", 18, 4294967295);
	GetGameObjectByName("RockWall 3").SetPosition({ 38,-16,16 });
	GetGameObjectByName("RockWall 3").SetRotation({ 0,0.96126163,0,0.275637567 });
	GetGameObjectByName("RockWall 3").SetScale({ 48,35,40 });
	CreateGameObject("RockWall 5", 19, 4294967295);
	GetGameObjectByName("RockWall 5").SetPosition({ -57,2,-59 });
	GetGameObjectByName("RockWall 5").SetRotation({ 0,0.96126163,0,0.275637567 });
	GetGameObjectByName("RockWall 5").SetScale({ 43,80,35 });
	CreateGameObject("RockWall 6", 17, 4294967295);
	GetGameObjectByName("RockWall 6").SetPosition({ -3,-18,-8 });
	GetGameObjectByName("RockWall 6").SetRotation({ 0.557308376,0.05808115,0.254369915,0.788244784 });
	GetGameObjectByName("RockWall 6").SetScale({ 31,13,26 });

	CreateGameObject("Boulder 0", 18, 4294967295);
	GetGameObjectByName("Boulder 0").SetPosition({ -53,-21,113 });
	GetGameObjectByName("Boulder 0").SetRotation({ 0.583064735,-0.467740774,0.46044904,0.478790939 });
	GetGameObjectByName("Boulder 0").SetScale({ 11,11,11 });



	XMFLOAT2 posXZmin = { -117 , 123 };
	XMFLOAT2 posXZmax = { 41 , 111 };

	auto& boulder1 = CreateGameObject<Boulder>(mp_ecsManager, mp_sceneManager->GetGameManager(), m_playerTest, this, posXZmin, posXZmax);
	boulder1.SetPosition({ -39,-21,111 });
	boulder1.SetScale({ 7,20,9 });

	auto& boulder2 = CreateGameObject<Boulder>(mp_ecsManager, mp_sceneManager->GetGameManager(), m_playerTest, this, posXZmin, posXZmax);
	boulder2.SetPosition({ -20,-19,111 });
	boulder2.SetScale({ 6,14,19 });

	//CreateGameObject("Boulder 1", 18, 4294967295);
	//GetGameObjectByName("Boulder 1").SetPosition({ -39,-21,111 });
	//GetGameObjectByName("Boulder 1").SetRotation({ 0.113225348,-0.030704228,0.993081927,-0.00505937 });
	//GetGameObjectByName("Boulder 1").SetScale({ 7,20,9 });

	//CreateGameObject("Boulder 2", 18, 4294967295);
	//GetGameObjectByName("Boulder 2").SetPosition({ -20,-19,111 });
	//GetGameObjectByName("Boulder 2").SetRotation({ 0.076485023,0.680503786,0.723926127,-0.083639987 });
	//GetGameObjectByName("Boulder 2").SetScale({ 6,14,19 });


	//GetGameObjectByName("field").SetPosition({ 3,-22,76 });
	//GetGameObjectByName("field").SetRotation({ 0,0,0,1 });
	//GetGameObjectByName("field").SetScale({ 121,1,71 });





	CreateGameObject("BigRock", 20, 4294967295);
	GetGameObjectByName("BigRock").SetPosition({ 9,-6,147 });
	GetGameObjectByName("BigRock").SetRotation({ 0,-0.878817022,0,0.477158964 });
	GetGameObjectByName("BigRock").SetScale({ 36,41,41 });



	// CHAMPS
	CreateGameObject("Champs 0", 2, 33);
	GetGameObjectByName("Champs 0").SetPosition({ 239,-20,-131 });
	GetGameObjectByName("Champs 0").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Champs 0").SetScale({ 150,2,100 });
	CreateGameObject("Maison", 4, 1);
	GetGameObjectByName("Maison").SetPosition({ 178,-19,-94 });
	GetGameObjectByName("Maison").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Maison").SetScale({ 2,2,2 });
	CreateGameObject("Champs 2", 2, 7);
	GetGameObjectByName("Champs 2").SetPosition({ 253,-19,-99 });
	GetGameObjectByName("Champs 2").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Champs 2").SetScale({ 110,2,25 });
	CreateGameObject("Champs 3", 2, 7);
	GetGameObjectByName("Champs 3").SetPosition({ 253,-19,-132 });
	GetGameObjectByName("Champs 3").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Champs 3").SetScale({ 110,2,25 });
	CreateGameObject("Champs 4", 2, 7);
	GetGameObjectByName("Champs 4").SetPosition({ 253,-19,-164 });
	GetGameObjectByName("Champs 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Champs 4").SetScale({ 110,2,25 });

	// OLIVIERS DECO
	CreateGameObject("Tree 8", 34, 4294967295);
	GetGameObjectByName("Tree 8").SetPosition({ 8,91,-61 });
	GetGameObjectByName("Tree 8").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Tree 8").SetScale({ 16,16,16 });
	CreateGameObject("Tree 9", 34, 4294967295);
	GetGameObjectByName("Tree 9").SetPosition({ 101,1,-92 });
	GetGameObjectByName("Tree 9").SetRotation({ 0,-0.788010716,0,0.615661561 });
	GetGameObjectByName("Tree 9").SetScale({ 6,6,6 });
	CreateGameObject("Tree 10", 34, 4294967295);
	GetGameObjectByName("Tree 10").SetPosition({ 329,1,-196 });
	GetGameObjectByName("Tree 10").SetRotation({ 0,-0.882947743,0,-0.469471335 });
	GetGameObjectByName("Tree 10").SetScale({ 6,6,6 });
	CreateGameObject("Tree 11", 34, 4294967295);
	GetGameObjectByName("Tree 11").SetPosition({ 255,27,-2 });
	GetGameObjectByName("Tree 11").SetRotation({ 0,-0.882947743,0,-0.469471335 });
	GetGameObjectByName("Tree 11").SetScale({ 6,6,6 });
	CreateGameObject("Tree 12", 34, 4294967295);
	GetGameObjectByName("Tree 12").SetPosition({ 281,28,91 });
	GetGameObjectByName("Tree 12").SetRotation({ 0,0.15643461,0,0.987688363 });
	GetGameObjectByName("Tree 12").SetScale({ 7,7,7 });

	CreateGameObject("Olivier_trunk 13", 32, 4294967295);
	GetGameObjectByName("Olivier_trunk 13").SetPosition({ -79,-22,-115 });
	GetGameObjectByName("Olivier_trunk 13").SetRotation({ 0,0.656059146,0,0.754709542 });
	GetGameObjectByName("Olivier_trunk 13").SetScale({ 7,7,7 });

	CreateGameObject("Tree 16", 34, 4294967295);
	GetGameObjectByName("Tree 16").SetPosition({ -47,6,-232 });
	GetGameObjectByName("Tree 16").SetRotation({ -0.138627812,-0.479704678,-0.037643887,0.865591586 });
	GetGameObjectByName("Tree 16").SetScale({ 8,8,8 });

	// ARBRES CHAMPS
	CreateGameObject("Tree 17", 28, 4294967295);
	GetGameObjectByName("Tree 17").SetPosition({ 308,-7,-179 });
	GetGameObjectByName("Tree 17").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Tree 17").SetScale({ 2,2,2 });
	CreateGameObject("Tree 18", 28, 4294967295);
	GetGameObjectByName("Tree 18").SetPosition({ 307,-7,-84 });
	GetGameObjectByName("Tree 18").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Tree 18").SetScale({ 2,2,2 });
	CreateGameObject("Tree 19", 28, 4294967295);
	GetGameObjectByName("Tree 19").SetPosition({ 167,-7,-83 });
	GetGameObjectByName("Tree 19").SetRotation({ 0,0.999048233,0,-0.043619186 });
	GetGameObjectByName("Tree 19").SetScale({ 2,2,2 });
	CreateGameObject("Tree 20", 28, 4294967295);
	GetGameObjectByName("Tree 20").SetPosition({ 168,-7,-178 });
	GetGameObjectByName("Tree 20").SetRotation({ 0,0.999048233,0,-0.043619186 });
	GetGameObjectByName("Tree 20").SetScale({ 2,2,2 });

	// OLIVES COMPETENCE
	// CASCADE
	position = { 72,1,149 };
	//position = { 100,5,100 };
	auto& oliveTree = CreateGameObject<OliveTree>(mp_ecsManager, this, position, 1);
	oliveTree.SetScale({ 4,4,4 });
	oliveTree.SetRotation({ -0.015740039,-0.043857157,0.012615366,0.998834133 });

	// PASSAGE TEMPLE
	position = { -14,2,-21 };
	auto& oliveTree2 = CreateGameObject<OliveTree>(mp_ecsManager, this, position, 2);
	oliveTree2.SetScale({ 6,7,7 });
	oliveTree2.SetRotation({ 0,0.737277627,0,-0.675589979 });

	/*CreateGameHitbox(" 0");
	GetGameObjectByName(" 0").SetPosition({ -14,0,-21 });
	GetGameObjectByName(" 0").SetRotation({ 0,0,0,1 });
	GetGameObjectByName(" 0").SetScale({ 250,2,250 });
	GetGameObjectByName(" 0").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 125, 1, 125 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));

	CreateGameHitbox(" 1");
	GetGameObjectByName(" 1").SetPosition({ 0,0,0 });
	GetGameObjectByName(" 1").SetRotation({ 0,0,0,1 });
	GetGameObjectByName(" 1").SetScale({ 1,10,1 });*/
	//GetGameObjectByName(" 1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 125, 1, 125 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));

	CreateGameHitbox("HB_LAKE 0");
	GetGameObjectByName("HB_LAKE 0").SetPosition({ -54,-20,113 });
	GetGameObjectByName("HB_LAKE 0").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_LAKE 0").SetScale({ 10,10,15 });
	GetGameObjectByName("HB_LAKE 0").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 5, 5, 7.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	/*CreateGameHitbox("HB_LAKE 1");
	GetGameObjectByName("HB_LAKE 1").SetPosition({ -38,-18,112 });
	GetGameObjectByName("HB_LAKE 1").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_LAKE 1").SetScale({ 11,12,11 });
	GetGameObjectByName("HB_LAKE 1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 5.5, 6, 5.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_LAKE 2");
	GetGameObjectByName("HB_LAKE 2").SetPosition({ -20,-18,111 });
	GetGameObjectByName("HB_LAKE 2").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_LAKE 2").SetScale({ 11,19,11 });
	GetGameObjectByName("HB_LAKE 2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 5.5, 9.5, 5.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));*/
	CreateGameHitbox("HB_LAKE 3");
	GetGameObjectByName("HB_LAKE 3").SetPosition({ 12.619031906,-19.762268066,136.884719849 });
	GetGameObjectByName("HB_LAKE 3").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_LAKE 3").SetScale({ 36,19,41 });
	GetGameObjectByName("HB_LAKE 3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 18, 9.5, 20.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_LAKE 4");
	GetGameObjectByName("HB_LAKE 4").SetPosition({ 14.275276184,-16.169765472,143.986968994 });
	GetGameObjectByName("HB_LAKE 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_LAKE 4").SetScale({ 36,19,41 });
	GetGameObjectByName("HB_LAKE 4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 18, 9.5, 20.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_LAKE 5");
	GetGameObjectByName("HB_LAKE 5").SetPosition({ 22.305616379,-19.80868721,136.464157104 });
	GetGameObjectByName("HB_LAKE 5").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_LAKE 5").SetScale({ 36,19,41 });
	GetGameObjectByName("HB_LAKE 5").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 18, 9.5, 20.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	//CreateGameHitbox("HB_LAKE 6");
	//GetGameObjectByName("HB_LAKE 6").SetPosition({ 52.282047272,-11.43447113,128.391662598 });
	//GetGameObjectByName("HB_LAKE 6").SetRotation({ 0,0,0,1 });
	//GetGameObjectByName("HB_LAKE 6").SetScale({ 16,19,31 });
	//GetGameObjectByName("HB_LAKE 6").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8, 9.5, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));

	CreateGameHitbox("HB_UPSTREAM 1");
	GetGameObjectByName("HB_UPSTREAM 1").SetPosition({ 72.454551697,-2.514286518,89.278663635 });
	GetGameObjectByName("HB_UPSTREAM 1").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_UPSTREAM 1").SetScale({ 21,6,166 });
	GetGameObjectByName("HB_UPSTREAM 1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 10.5, 3, 83 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_UPSTREAM 2");
	GetGameObjectByName("HB_UPSTREAM 2").SetPosition({ 206.016464233,1.502984762,73.236419678 });
	GetGameObjectByName("HB_UPSTREAM 2").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_UPSTREAM 2").SetScale({ 256,6,176 });
	GetGameObjectByName("HB_UPSTREAM 2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 128, 3, 88 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_UPSTREAM 3");// WATERFALL
	GetGameObjectByName("HB_UPSTREAM 3").SetPosition({ 62.914527893,-15.86863327,80.58568573 });
	GetGameObjectByName("HB_UPSTREAM 3").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_UPSTREAM 3").SetScale({ 3,21,156 });
	GetGameObjectByName("HB_UPSTREAM 3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 10.5, 78 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));

	CreateGameHitbox("MiddleRocks 1");
	GetGameObjectByName("MiddleRocks 1").SetPosition({ 32.100036621,-13.396051407,18.657812119 });
	GetGameObjectByName("MiddleRocks 1").SetRotation({ 0,-0.275637329,0,0.961261749 });
	GetGameObjectByName("MiddleRocks 1").SetScale({ 40,30,30 });
	GetGameObjectByName("MiddleRocks 1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 20, 15, 15 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));

	CreateGameHitbox("MiddleRocks 2");
	GetGameObjectByName("MiddleRocks 2").SetPosition({ 61.833629608,-13.396051407,24.963226318 });
	GetGameObjectByName("MiddleRocks 2").SetRotation({ 0,-0.069756389,0,0.997564077 });
	GetGameObjectByName("MiddleRocks 2").SetScale({ 38,30,40 });
	GetGameObjectByName("MiddleRocks 2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 19, 15, 20 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("MiddleRocks 3");
	GetGameObjectByName("MiddleRocks 3").SetPosition({ 6.974430084,-8.886211395,-19.0909729 });
	GetGameObjectByName("MiddleRocks 3").SetRotation({ 0,-0.37460652,0,0.927183926 });
	GetGameObjectByName("MiddleRocks 3").SetScale({ 58,30,65 });
	GetGameObjectByName("MiddleRocks 3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 29, 15, 32.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("MiddleRocks 4");
	GetGameObjectByName("MiddleRocks 4").SetPosition({ -18.031211853,-12.179989815,7.130444527 });
	GetGameObjectByName("MiddleRocks 4").SetRotation({ 0,-0.37460652,0,0.927183926 });
	GetGameObjectByName("MiddleRocks 4").SetScale({ 48,25,15 });
	GetGameObjectByName("MiddleRocks 4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 24, 12.5, 7.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("MiddleRocks 5");
	GetGameObjectByName("MiddleRocks 5").SetPosition({ -59.122394562,-2.865666389,-51.741119385 });
	GetGameObjectByName("MiddleRocks 5").SetRotation({ 0,-0.147809193,0,0.989015937 });
	GetGameObjectByName("MiddleRocks 5").SetScale({ 68,55,30 });
	GetGameObjectByName("MiddleRocks 5").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 34, 27.5, 15 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("MiddleRocks 6");
	GetGameObjectByName("MiddleRocks 6").SetPosition({ -58.247680664,-2.865666389,-69.050384521 });
	GetGameObjectByName("MiddleRocks 6").SetRotation({ 0,-0.147809193,0,0.989015937 });
	GetGameObjectByName("MiddleRocks 6").SetScale({ 68,55,40 });
	GetGameObjectByName("MiddleRocks 6").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 34, 27.5, 20 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("MiddleRocks 7");
	GetGameObjectByName("MiddleRocks 7").SetPosition({ -1.207934856,-2.865666389,-71.183433533 });
	GetGameObjectByName("MiddleRocks 7").SetRotation({ 0,0.233445346,0,0.972369969 });
	GetGameObjectByName("MiddleRocks 7").SetScale({ 48,55,40 });
	GetGameObjectByName("MiddleRocks 7").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 24, 27.5, 20 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("MiddleRocks 8");
	GetGameObjectByName("MiddleRocks 8").SetPosition({ 26.881340027,-2.865666389,-71.527770996 });
	GetGameObjectByName("MiddleRocks 8").SetRotation({ 0,-0.069756478,0,0.997564077 });
	GetGameObjectByName("MiddleRocks 8").SetScale({ 38,55,50 });
	GetGameObjectByName("MiddleRocks 8").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 19, 27.5, 25 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("MiddleRocks 9");
	GetGameObjectByName("MiddleRocks 9").SetPosition({ 48.76807785,-2.865666389,-43.133491516 });
	GetGameObjectByName("MiddleRocks 9").SetRotation({ 0,-0.20791164,0,0.978147626 });
	GetGameObjectByName("MiddleRocks 9").SetScale({ 58,45,30 });
	GetGameObjectByName("MiddleRocks 9").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 29, 22.5, 15 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("MiddleRocks 10");
	GetGameObjectByName("MiddleRocks 10").SetPosition({ 55.417121887,18.206371307,-16.908542633 });
	GetGameObjectByName("MiddleRocks 10").SetRotation({ 0,-0.043619391,0,0.999048233 });
	GetGameObjectByName("MiddleRocks 10").SetScale({ 51,36,61 });
	GetGameObjectByName("MiddleRocks 10").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 25.5, 18, 30.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("MiddleRocks 11");
	GetGameObjectByName("MiddleRocks 11").SetPosition({ 9.378818512,18.206371307,-48.766422272 });
	GetGameObjectByName("MiddleRocks 11").SetRotation({ 0,-0.156434402,0,0.987688422 });
	GetGameObjectByName("MiddleRocks 11").SetScale({ 66,71,61 });
	GetGameObjectByName("MiddleRocks 11").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 33, 35.5, 30.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));

	/*auto* a1 = &CreateGameHitbox("Temp_slope 0");
	GetGameObjectByName("Temp_slope 0").SetPosition({ -35,-25,74 });
	GetGameObjectByName("Temp_slope 0").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temp_slope 0").SetScale({ 21,6,11 });
	GetGameObjectByName("Temp_slope 0").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 10.5, 3, 5.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	a1->SetTag(TAG_Floor);
	auto* a2 = &CreateGameHitbox("Temp_slope 1");
	GetGameObjectByName("Temp_slope 1").SetPosition({ 11,-25,79 });
	GetGameObjectByName("Temp_slope 1").SetRotation({ 0,0,0.267238349,0.963630497 });
	GetGameObjectByName("Temp_slope 1").SetScale({ 26,6,16 });
	GetGameObjectByName("Temp_slope 1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 13, 3, 8 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	a2->SetTag(TAG_Floor);
	auto* a3 = &CreateGameHitbox("Temp_slope 2");
	GetGameObjectByName("Temp_slope 2").SetPosition({ -32,-23,38 });
	GetGameObjectByName("Temp_slope 2").SetRotation({ 0.216233701,0.009440946,0.042585358,0.975366831 });
	GetGameObjectByName("Temp_slope 2").SetScale({ 26,6,21 });
	GetGameObjectByName("Temp_slope 2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 13, 3, 10.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	a3->SetTag(TAG_Floor);
	auto* a4 = &CreateGameHitbox("Temp_slope 3");
	GetGameObjectByName("Temp_slope 3").SetPosition({ 19.286569595,-21.031072617,54.787345886 });
	GetGameObjectByName("Temp_slope 3").SetRotation({ 0,0,0.069756463,0.997564077 });
	GetGameObjectByName("Temp_slope 3").SetScale({ 106,11,11 });
	GetGameObjectByName("Temp_slope 3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 53, 5.5, 5.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	a4->SetTag(TAG_Floor);*/
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
		gameObject.get()->OnUpdate(deltatime);
	}

	//// PlayerState
	m_playerTest.OnUpdate(deltatime);


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
			m_fpsCam.SetAlwaysActive(false);
		}
		else
		{
			RemoveMenu();
			m_fpsCam.SetAlwaysActive(true);
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