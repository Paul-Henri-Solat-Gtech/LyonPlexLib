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
	GetGameObjectByName("testGm").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ a.x / 2,a.y / 2,a.z / 2 })));


	SetParent("camera2", "player");

	m_playerWalkSpeed = 3.f;
	m_playerRunSpeed = 6.f;
	m_playerSpeed = m_playerWalkSpeed;

	// Test player + stateMachine
	m_playerTest.Init(m_player, mp_sceneManager->GetGameManager());
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
	GetGameObjectByName("GM0").SetPosition({ 0.571841,-1.384057,-2.635353 });
	GetGameObjectByName("GM0").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("GM0").SetScale({ 20.185083,0.443769,23.175503 });
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
	if (InputManager::GetKeyIsReleased(VK_LBUTTON))
	{
		//PlaySoundPlex("slash1");
	}

	// Gravity
	if (m_player.GetPosition().y > 1.f)
	{
		m_player.GetComponent<TransformComponent>()->position.y -= 9.81f * deltatime;
		m_player.GetComponent<TransformComponent>()->dirty = true;
	}

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
