#include "pch.h"
#include "GameScene.h"

void GameScene::Start()
{
	CreateGameObject("cam", TYPE_3D, false);
	m_cam = GetGameObjectByName("cam");
	m_cam.AddComponent<CameraComponent>(new CameraComponent());
	GetGameObjectByName("cam").SetPosition({ 0, 0, 0.5f });
	
	// fps cam
	m_fpsCam.Init(m_cam, mp_sceneManager->GetWindow());

	CreateGameObject("player");
	GetGameObjectByName("player").SetPosition({ 0, 3, -1 });
	m_player = GetGameObjectByName("player");

	CreateGameObject("testGm");
	GetGameObjectByName("testGm").SetPosition({ 0, 10, 3 });
	GetGameObjectByName("testGm").SetTexture(TEXTURES::GRID);
	
	CreateGameObject("testDestory");
	GetGameObjectByName("testDestory").SetPosition({ 0, 1, 5 });
	GetGameObjectByName("testDestory").SetTexture(TEXTURES::EAU);

	auto& a = GetGameObjectByName("testGm").GetScale();
	GetGameObjectByName("testGm").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ a.x / 2, a.y / 2, a.z / 2 })));

	GetGameObjectByName("testGm").AddComponent<Tag_Object>(new Tag_Object());
	GetGameObjectByName("testGm").SetTag(TAG_Stick);


	SetParent("cam", "player");
	m_fpsCam.SetParentGO(m_cam);

	m_playerWalkSpeed = 3.f;
	m_playerRunSpeed = 6.f;
	m_playerSpeed = m_playerWalkSpeed;

	// Test player + stateMachine
	m_playerTest.Init(m_player, mp_sceneManager->GetGameManager(), this, m_cam);
	m_enemyTest.Init(GetGameObjectByName("testGm"), m_player, mp_sceneManager->GetGameManager());

	CreateGameObject("bras", TYPE_2D, true);
	GetGameObjectByName("bras").SetTexture(TEXTURES::ARMS);
	GetGameObjectByName("bras").SetPosition({ 400, 450, 0 });
	GetGameObjectByName("bras").SetScale({ 800, 500, 0 });
	GetGameObjectByName("bras").GetComponent<TransformComponent>()->AddRotation(0, 0, 180);


	m_playerTest.SetPlayerArm(GetGameObjectByName("bras"));


	// Audio
	CreateSoundPlex("slash1", L"../LyonPlexLib/Ressources/swordSlash1.wav");
	CreateSoundPlex("Corrosion", L"../LyonPlexLib/Ressources/Corrosion.wav");
	PlayMusicPlex("Corrosion");

	// scene
	/*CreateGameObject("GM0", 2, 4);
	GetGameObjectByName("GM0").SetTag(TAG_Floor);
	GetGameObjectByName("GM0").SetPosition({ 0,-50, 0 });
	GetGameObjectByName("GM0").SetScale({ 20, 100, 20 });
	auto& b = GetGameObjectByName("GM0").GetScale();
	GetGameObjectByName("GM0").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ b.x / 2, b.y / 2, b.z / 2 })));*/

	CreateGameObject("GM1", 2, 4);
	GetGameObjectByName("GM1").SetTag(TAG_Floor);
	GetGameObjectByName("GM1").SetPosition({ 2,1, 0 });
	GetGameObjectByName("GM1").SetScale({ 2, 1, 2 });
	auto& c = GetGameObjectByName("GM1").GetScale();
	GetGameObjectByName("GM1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	{
		CreateGameObject("GM0", 2, 1);
		GetGameObjectByName("GM0").SetPosition({ 0,0,0 });
		GetGameObjectByName("GM0").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM0").SetScale({ 40,6,40 });
		GetGameObjectByName("GM0").SetTag(TAG_Floor);
		auto& d = GetGameObjectByName("GM0").GetScale();
		GetGameObjectByName("GM0").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM3", 2, 0);
		GetGameObjectByName("GM3").SetPosition({ -8,1,13 });
		GetGameObjectByName("GM3").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM3").SetScale({ 20,6,10 });
		GetGameObjectByName("GM3").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM3").GetScale();
		GetGameObjectByName("GM3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM5", 2, 0);
		GetGameObjectByName("GM5").SetPosition({ -8,1,0 });
		GetGameObjectByName("GM5").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM5").SetScale({ 20,6,10 });
		GetGameObjectByName("GM5").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM5").GetScale();
		GetGameObjectByName("GM5").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM6", 2, 0);
		GetGameObjectByName("GM6").SetPosition({ -8,1,-13 });
		GetGameObjectByName("GM6").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM6").SetScale({ 20,6,10 });
		GetGameObjectByName("GM6").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM6").GetScale();
		GetGameObjectByName("GM6").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM7", 2, 0);
		GetGameObjectByName("GM7").SetPosition({ 11,1,-8 });
		GetGameObjectByName("GM7").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM7").SetScale({ 11,6,20 });
		GetGameObjectByName("GM7").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM7").GetScale();
		GetGameObjectByName("GM7").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM9", 2, 2);
		GetGameObjectByName("GM9").SetPosition({ 11,8,11 });
		GetGameObjectByName("GM9").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM9").SetScale({ 11,11,15 });
		GetGameObjectByName("GM9").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM9").GetScale();
		GetGameObjectByName("GM9").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM10", 2, 1);
		GetGameObjectByName("GM10").SetPosition({ 29,0,-10 });
		GetGameObjectByName("GM10").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM10").SetScale({ 19,6,12 });
		GetGameObjectByName("GM10").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM10").GetScale();
		GetGameObjectByName("GM10").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM11", 2, 1);
		GetGameObjectByName("GM11").SetPosition({ 48,0,-10 });
		GetGameObjectByName("GM11").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM11").SetScale({ 19,6,12 });
		GetGameObjectByName("GM11").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM11").GetScale();
		GetGameObjectByName("GM11").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM12", 2, 1);
		GetGameObjectByName("GM12").SetPosition({ 67,0,-10 });
		GetGameObjectByName("GM12").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM12").SetScale({ 19,6,12 });
		GetGameObjectByName("GM12").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM12").GetScale();
		GetGameObjectByName("GM12").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM13", 2, 1);
		GetGameObjectByName("GM13").SetPosition({ 86,0,-10 });
		GetGameObjectByName("GM13").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM13").SetScale({ 19,6,12 });
		GetGameObjectByName("GM13").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM13").GetScale();
		GetGameObjectByName("GM13").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM18", 2, 1);
		GetGameObjectByName("GM18").SetPosition({ 102,0,-17 });
		GetGameObjectByName("GM18").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM18").SetScale({ 13,6,27 });
		GetGameObjectByName("GM18").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM18").GetScale();
		GetGameObjectByName("GM18").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM19", 2, 1);
		GetGameObjectByName("GM19").SetPosition({ 102,0,-44 });
		GetGameObjectByName("GM19").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM19").SetScale({ 13,6,27 });
		GetGameObjectByName("GM19").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM19").GetScale();
		GetGameObjectByName("GM19").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM20", 2, 1);
		GetGameObjectByName("GM20").SetPosition({ 102,0,-71 });
		GetGameObjectByName("GM20").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM20").SetScale({ 13,6,27 });
		GetGameObjectByName("GM20").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM20").GetScale();
		GetGameObjectByName("GM20").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM21", 2, 1);
		GetGameObjectByName("GM21").SetPosition({ 102,0,-110 });
		GetGameObjectByName("GM21").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM21").SetScale({ 61,6,51 });
		GetGameObjectByName("GM21").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM21").GetScale();
		GetGameObjectByName("GM21").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM22", 2, 1);
		GetGameObjectByName("GM22").SetPosition({ 101,0,-149 });
		GetGameObjectByName("GM22").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM22").SetScale({ 13,6,27 });
		GetGameObjectByName("GM22").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM22").GetScale();
		GetGameObjectByName("GM22").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM24", 2, 1);
		GetGameObjectByName("GM24").SetPosition({ 101,0,-176 });
		GetGameObjectByName("GM24").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM24").SetScale({ 13,6,27 });
		GetGameObjectByName("GM24").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM24").GetScale();
		GetGameObjectByName("GM24").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM25", 2, 1);
		GetGameObjectByName("GM25").SetPosition({ 88,0,-176 });
		GetGameObjectByName("GM25").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM25").SetScale({ 13,6,27 });
		GetGameObjectByName("GM25").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM25").GetScale();
		GetGameObjectByName("GM25").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM26", 2, 1);
		GetGameObjectByName("GM26").SetPosition({ 88,0,-203 });
		GetGameObjectByName("GM26").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM26").SetScale({ 13,6,27 });
		GetGameObjectByName("GM26").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM26").GetScale();
		GetGameObjectByName("GM26").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM27", 2, 1);
		GetGameObjectByName("GM27").SetPosition({ 75,0,-176 });
		GetGameObjectByName("GM27").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM27").SetScale({ 13,6,27 });
		GetGameObjectByName("GM27").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM27").GetScale();
		GetGameObjectByName("GM27").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM28", 2, 1);
		GetGameObjectByName("GM28").SetPosition({ 62,0,-176 });
		GetGameObjectByName("GM28").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM28").SetScale({ 13,6,27 });
		GetGameObjectByName("GM28").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM28").GetScale();
		GetGameObjectByName("GM28").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM31", 2, 1);
		GetGameObjectByName("GM31").SetPosition({ 75,0,-203 });
		GetGameObjectByName("GM31").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM31").SetScale({ 13,6,27 });
		GetGameObjectByName("GM31").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM31").GetScale();
		GetGameObjectByName("GM31").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM32", 2, 1);
		GetGameObjectByName("GM32").SetPosition({ 62,0,-203 });
		GetGameObjectByName("GM32").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM32").SetScale({ 13,6,27 });
		GetGameObjectByName("GM32").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM32").GetScale();
		GetGameObjectByName("GM32").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM33", 2, 1);
		GetGameObjectByName("GM33").SetPosition({ 49,0,-189 });
		GetGameObjectByName("GM33").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM33").SetScale({ 13,6,27 });
		GetGameObjectByName("GM33").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM33").GetScale();
		GetGameObjectByName("GM33").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM34", 2, 1);
		GetGameObjectByName("GM34").SetPosition({ 49,0,-216 });
		GetGameObjectByName("GM34").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM34").SetScale({ 13,21,27 });
		GetGameObjectByName("GM34").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM34").GetScale();
		GetGameObjectByName("GM34").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM36", 2, 1);
		GetGameObjectByName("GM36").SetPosition({ 49,0,-162 });
		GetGameObjectByName("GM36").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM36").SetScale({ 13,21,27 });
		GetGameObjectByName("GM36").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM36").GetScale();
		GetGameObjectByName("GM36").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM37", 2, 1);
		GetGameObjectByName("GM37").SetPosition({ 36,12,-162 });
		GetGameObjectByName("GM37").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM37").SetScale({ 13,21,27 });
		GetGameObjectByName("GM37").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM37").GetScale();
		GetGameObjectByName("GM37").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM38", 2, 1);
		GetGameObjectByName("GM38").SetPosition({ 36,12,-189 });
		GetGameObjectByName("GM38").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM38").SetScale({ 13,21,27 });
		GetGameObjectByName("GM38").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM38").GetScale();
		GetGameObjectByName("GM38").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM39", 2, 1);
		GetGameObjectByName("GM39").SetPosition({ 36,12,-216 });
		GetGameObjectByName("GM39").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM39").SetScale({ 13,21,27 });
		GetGameObjectByName("GM39").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM39").GetScale();
		GetGameObjectByName("GM39").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM40", 2, 1);
		GetGameObjectByName("GM40").SetPosition({ 15,21,-189 });
		GetGameObjectByName("GM40").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM40").SetScale({ 28,9,17 });
		GetGameObjectByName("GM40").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM40").GetScale();
		GetGameObjectByName("GM40").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM41", 2, 1);
		GetGameObjectByName("GM41").SetPosition({ -13,21,-189 });
		GetGameObjectByName("GM41").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM41").SetScale({ 28,9,17 });
		GetGameObjectByName("GM41").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM41").GetScale();
		GetGameObjectByName("GM41").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM42", 2, 1);
		GetGameObjectByName("GM42").SetPosition({ -41,21,-189 });
		GetGameObjectByName("GM42").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM42").SetScale({ 28,9,17 });
		GetGameObjectByName("GM42").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM42").GetScale();
		GetGameObjectByName("GM42").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM44", 2, 1);
		GetGameObjectByName("GM44").SetPosition({ -41,21,-172 });
		GetGameObjectByName("GM44").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM44").SetScale({ 28,9,17 });
		GetGameObjectByName("GM44").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM44").GetScale();
		GetGameObjectByName("GM44").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM45", 2, 1);
		GetGameObjectByName("GM45").SetPosition({ -41,21,-155 });
		GetGameObjectByName("GM45").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM45").SetScale({ 28,9,17 });
		GetGameObjectByName("GM45").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM45").GetScale();
		GetGameObjectByName("GM45").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM48", 2, 1);
		GetGameObjectByName("GM48").SetPosition({ -41,21,-138 });
		GetGameObjectByName("GM48").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM48").SetScale({ 28,9,17 });
		GetGameObjectByName("GM48").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM48").GetScale();
		GetGameObjectByName("GM48").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM49", 2, 1);
		GetGameObjectByName("GM49").SetPosition({ -41,21,-121 });
		GetGameObjectByName("GM49").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM49").SetScale({ 28,9,17 });
		GetGameObjectByName("GM49").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM49").GetScale();
		GetGameObjectByName("GM49").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM50", 2, 1);
		GetGameObjectByName("GM50").SetPosition({ -13,21,-121 });
		GetGameObjectByName("GM50").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM50").SetScale({ 28,9,17 });
		GetGameObjectByName("GM50").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM50").GetScale();
		GetGameObjectByName("GM50").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM51", 2, 1);
		GetGameObjectByName("GM51").SetPosition({ 15,21,-121 });
		GetGameObjectByName("GM51").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM51").SetScale({ 28,9,17 });
		GetGameObjectByName("GM51").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM51").GetScale();
		GetGameObjectByName("GM51").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM52", 2, 1);
		GetGameObjectByName("GM52").SetPosition({ 43,21,-121 });
		GetGameObjectByName("GM52").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM52").SetScale({ 28,9,17 });
		GetGameObjectByName("GM52").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM52").GetScale();
		GetGameObjectByName("GM52").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM53", 2, 1);
		GetGameObjectByName("GM53").SetPosition({ -41,21,-104 });
		GetGameObjectByName("GM53").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM53").SetScale({ 28,9,17 });
		GetGameObjectByName("GM53").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM53").GetScale();
		GetGameObjectByName("GM53").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM54", 2, 1);
		GetGameObjectByName("GM54").SetPosition({ -13,21,-104 });
		GetGameObjectByName("GM54").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM54").SetScale({ 28,9,17 });
		GetGameObjectByName("GM54").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM54").GetScale();
		GetGameObjectByName("GM54").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM55", 2, 1);
		GetGameObjectByName("GM55").SetPosition({ 15,21,-104 });
		GetGameObjectByName("GM55").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM55").SetScale({ 28,9,17 });
		GetGameObjectByName("GM55").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM55").GetScale();
		GetGameObjectByName("GM55").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM56", 2, 1);
		GetGameObjectByName("GM56").SetPosition({ 15,21,-87 });
		GetGameObjectByName("GM56").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM56").SetScale({ 28,9,17 });
		GetGameObjectByName("GM56").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM56").GetScale();
		GetGameObjectByName("GM56").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM57", 2, 1);
		GetGameObjectByName("GM57").SetPosition({ 15,21,-70 });
		GetGameObjectByName("GM57").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM57").SetScale({ 28,9,17 });
		GetGameObjectByName("GM57").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM57").GetScale();
		GetGameObjectByName("GM57").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM58", 2, 1);
		GetGameObjectByName("GM58").SetPosition({ -13,21,-87 });
		GetGameObjectByName("GM58").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM58").SetScale({ 28,9,17 });
		GetGameObjectByName("GM58").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM58").GetScale();
		GetGameObjectByName("GM58").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM59", 2, 1);
		GetGameObjectByName("GM59").SetPosition({ -41,21,-87 });
		GetGameObjectByName("GM59").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM59").SetScale({ 28,9,17 });
		GetGameObjectByName("GM59").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM59").GetScale();
		GetGameObjectByName("GM59").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM62", 2, 1);
		GetGameObjectByName("GM62").SetPosition({ -41,21,-70 });
		GetGameObjectByName("GM62").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM62").SetScale({ 28,9,17 });
		GetGameObjectByName("GM62").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM62").GetScale();
		GetGameObjectByName("GM62").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM63", 2, 1);
		GetGameObjectByName("GM63").SetPosition({ -13,21,-70 });
		GetGameObjectByName("GM63").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM63").SetScale({ 28,9,17 });
		GetGameObjectByName("GM63").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM63").GetScale();
		GetGameObjectByName("GM63").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM65", 2, 1);
		GetGameObjectByName("GM65").SetPosition({ 9,11,-59 });
		GetGameObjectByName("GM65").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM65").SetScale({ 38,24,3 });
		GetGameObjectByName("GM65").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM65").GetScale();
		GetGameObjectByName("GM65").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM66", 2, 1);
		GetGameObjectByName("GM66").SetPosition({ -29,9,-60 });
		GetGameObjectByName("GM66").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM66").SetScale({ 38,24,3 });
		GetGameObjectByName("GM66").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM66").GetScale();
		GetGameObjectByName("GM66").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM71", 2, 1);
		GetGameObjectByName("GM71").SetPosition({ 9,1,-58 });
		GetGameObjectByName("GM71").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM71").SetScale({ 38,24,3 });
		GetGameObjectByName("GM71").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM71").GetScale();
		GetGameObjectByName("GM71").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

		CreateGameObject("GM85", 2, 1);
		GetGameObjectByName("GM85").SetPosition({ -29,1,-58 });
		GetGameObjectByName("GM85").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM85").SetScale({ 38,24,3 });
		GetGameObjectByName("GM85").SetTag(TAG_Floor);
		d = GetGameObjectByName("GM85").GetScale();
		GetGameObjectByName("GM85").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ d.x / 2, d.y / 2, d.z / 2 })));

	}
}

void GameScene::Update(float deltatime)
{
	m_fpsCam.Update(deltatime);

	if (InputManager::GetKeyIsReleased('K'))
	{
		PlaySoundPlex("pop");
		DestroyGameObject(GetGameObjectByName("testDestory"));
	}
	if (InputManager::GetKeyIsReleased('N'))
	{
		StopMusicPlex();
	}

	//// Gravity
	//if (m_player.GetPosition().y > 1.f)
	//{
	//	m_player.GetComponent<TransformComponent>()->position.y -= 9.81f * deltatime;
	//	m_player.GetComponent<TransformComponent>()->dirty = true;
	//}

	// PlayerState
	m_playerTest.OnUdpdate(deltatime);
	m_enemyTest.OnUdpdate(deltatime);


	if (InputManager::GetKeyIsReleased('T'))
	{
		OutputDebugStringA(("\nPlayer State : " + std::string(m_playerTest.GetCurrentStateName())).c_str());
	}

	// Change scene [ALLWAYS AT THE END SO THERE IS NO OTHER CODE RUNNING AFTER IN THIS SCENE]
	if (InputManager::GetKeyIsReleased('A'))
	{
		ChangeScene("DevScene");
	}
}

void GameScene::Release()
{
}
