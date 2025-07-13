#include "pch.h"
#include "GameScene.h"

void GameScene::Start()
{
	CreateGameObject("camera2", TYPE_3D, false);
	GetGameObjectByName("camera2").AddComponent<CameraComponent>(new CameraComponent());
	GetGameObjectByName("camera2").SetPosition({ 0, 0, 0.5f });

	CreateGameObject("player");
	GetGameObjectByName("player").SetPosition({ 0, 3, -1 });
	m_player = GetGameObjectByName("player");

	CreateGameObject("testGm");
	GetGameObjectByName("testGm").SetPosition({ 0, 1, 3 });
	GetGameObjectByName("testGm").SetTexture(TEXTURES::GRID);

	auto& a = GetGameObjectByName("testGm").GetScale();
	GetGameObjectByName("testGm").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ a.x / 2, a.y / 2, a.z / 2 })));

	GetGameObjectByName("testGm").AddComponent<Tag_Object>(new Tag_Object());
	GetGameObjectByName("testGm").SetTag(TAG_Stick);


	SetParent("camera2", "player");

	m_playerWalkSpeed = 3.f;
	m_playerRunSpeed = 6.f;
	m_playerSpeed = m_playerWalkSpeed;

	// Test player + stateMachine
	m_playerTest.Init(m_player, mp_sceneManager->GetGameManager(), this);
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
	CreateGameObject("GM0", 2, 4);
	GetGameObjectByName("GM0").SetTag(TAG_Floor);
	GetGameObjectByName("GM0").SetPosition({ 0,-5, 0 });
	GetGameObjectByName("GM0").SetScale({ 20, 10, 20 });
	auto& b = GetGameObjectByName("GM0").GetScale();
	GetGameObjectByName("GM0").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ b.x / 2, b.y / 2, b.z / 2 })));

	CreateGameObject("GM1", 2, 4);
	GetGameObjectByName("GM1").SetTag(TAG_Floor);
	GetGameObjectByName("GM1").SetPosition({ 2,1, 0 });
	GetGameObjectByName("GM1").SetScale({ 2, 1, 2 });
	auto& c = GetGameObjectByName("GM1").GetScale();
	GetGameObjectByName("GM1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));
}

void GameScene::Update(float deltatime)
{
	//Input
	// 
	// !!! STATE MACHINE MANAGE THE PLAYER !!!
	// 
	if (InputManager::GetKeyIsReleased('K'))
	{
		PlaySoundPlex("pop");
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
