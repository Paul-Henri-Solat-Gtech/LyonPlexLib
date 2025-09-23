#include "pch.h"
#include "MainMenuScene.h"

void MainMenuScene::Start()
{
	// Camera
	CreateGameObject("camera2", TYPE_3D, false);
	FindGameObjectByName("camera2")->AddComponent<CameraComponent>(new CameraComponent());
	FindGameObjectByName("camera2")->SetPosition({ 0, 0, 0.5f });/*
	GetGameObjectByName("camera2").AddComponent<CameraComponent>(new CameraComponent());
	GetGameObjectByName("camera2").SetPosition({ 0, 0, 0.5f });*/

	RECT renderZone;
	GetClientRect(GetSceneManager()->GetGameManager()->GetRenderingManager().GetGraphicsDevice()->GetWindow(), &renderZone);
	UINT renderWidth = renderZone.right - renderZone.left;
	UINT renderHeight = renderZone.bottom - renderZone.top;

	// Title
	auto& gmTitle = CreateGameObject("Title", TYPE_2D, true);
	//m_playerHeart1 = mp_scene->GetGameObjectByName("Heart1");
	gmTitle.SetMesh(MESHES::LOCAL_SQUARE);
	gmTitle.SetTexture(TEXTURES::TITLE);
	gmTitle.SetPosition({ (float)renderWidth - 300, ((float)renderHeight / 2) - 200, 0 });
	gmTitle.SetScale({ 220, 120, 1 });
	gmTitle.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	// Buttons
	mp_buttonStart = &CreateGameObject<Button>(this, mp_sceneManager->GetWindow(), TEXTURES::BTN_START, "btnStart");
	mp_buttonStart->SetScale({ 200, 80, 1 });
	mp_buttonStart->SetPosition({ 210, ((float)renderHeight / 2) - 50, 0 });

	mp_buttonArene = &CreateGameObject<Button>(this, mp_sceneManager->GetWindow(), TEXTURES::BTN_ARENA, "btnArene");
	mp_buttonArene->SetScale({ 300, 80, 1 });
	mp_buttonArene->SetPosition({ 350, ((float)renderHeight / 2) + 130, 0 });

	mp_buttonQuit = &CreateGameObject<Button>(this, mp_sceneManager->GetWindow(), TEXTURES::BTN_SHUTDOWN, "btnquit");
	mp_buttonQuit->SetScale({ 30, 30, 1 });
	mp_buttonQuit->SetPosition({ (float)renderWidth - 70, (float)renderHeight - 70, 0 });
	
	// Background
	auto& gmBg = CreateGameObject("BG", TYPE_2D, true);
	//m_playerHeart1 = mp_scene->GetGameObjectByName("Heart1");
	gmBg.SetMesh(MESHES::LOCAL_SQUARE);
	gmBg.SetTexture(TEXTURES::BGMAINMENU);
	gmBg.SetPosition({ (float)renderWidth / 2, (float)renderHeight / 2, 1 });
	gmBg.SetScale({ 595, 320, 1 });
	gmBg.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	m_sceneHasChanged = false;
	m_btnStartSelected = false;
	m_btnArenaSelected = false;

	// Music
	PlayMusicPlex("ArmonizerTheme");
}

void MainMenuScene::Update(float deltatime)
{
	//START
	if (mp_buttonStart->GetMouseOnBtn() && !m_sceneHasChanged)
	{
		//OutputDebugStringA("\nDont touche me !\n");
		mp_buttonStart->SetScale({ 220, 100, 1 });
		if ((!m_btnStartSelected && m_btnArenaSelected) || (!m_btnStartSelected && !m_btnArenaSelected))
		{
			GetSceneManager()->GetGameManager()->GetSoundManager()->PlaySoundPlex("BIP");
			m_btnStartSelected = true;
			m_btnArenaSelected = false;
		}
	}
	if (!mp_buttonStart->GetMouseOnBtn() && !m_sceneHasChanged)
	{
		//OutputDebugStringA("\nDont touche me !\n");
		mp_buttonStart->SetScale({ 200, 80, 1 });
		m_btnStartSelected = false;
	}
	if (mp_buttonStart->GetBtnIsClicked() && !m_sceneHasChanged)
	{
		//OutputDebugStringA("\nHO YOU DARE CLICK ME !?\n");
		m_sceneHasChanged = true;
		ChangeScene("GameScene");
		return;
	}

	//ARENE
	if (mp_buttonArene->GetMouseOnBtn() && !m_sceneHasChanged)
	{
		//OutputDebugStringA("\nDont touche me !\n");
		mp_buttonArene->SetScale({ 270, 100, 1 });

		if ((m_btnStartSelected && !m_btnArenaSelected) || (!m_btnStartSelected && !m_btnArenaSelected))
		{
			GetSceneManager()->GetGameManager()->GetSoundManager()->PlaySoundPlex("BIP");
			m_btnStartSelected = false;
			m_btnArenaSelected = true;
		}
	}
	if (!mp_buttonArene->GetMouseOnBtn() && !m_sceneHasChanged)
	{
		//OutputDebugStringA("\nDont touche me !\n");
		mp_buttonArene->SetScale({ 250, 80, 1 });
		m_btnArenaSelected = false;
	}
	if (mp_buttonArene->GetBtnIsClicked() && !m_sceneHasChanged)
	{
		//OutputDebugStringA("\nHO YOU DARE CLICK ME !?\n");
		m_sceneHasChanged = true;
		ChangeScene("ArenaScene");
		return;
	}

	//QUIT
	if (mp_buttonQuit->GetMouseOnBtn() && !m_sceneHasChanged)
	{
		mp_buttonQuit->SetScale({ 50, 50, 1 });
	}
	if (!mp_buttonQuit->GetMouseOnBtn() && !m_sceneHasChanged)
	{
		mp_buttonQuit->SetScale({ 30, 30, 1 });
	}
	if (mp_buttonQuit->GetBtnIsClicked() && !m_sceneHasChanged)
	{
		//Quit the application
		PostQuitMessage(0);
		return;
	}

	//WORLD EDIT
	if (InputManager::GetKeyIsReleased('A'))
	{
		ChangeScene("DevScene");
		return;
	}
}

void MainMenuScene::Release()
{
	mp_buttonStart = nullptr;
	mp_buttonArene = nullptr;
}
