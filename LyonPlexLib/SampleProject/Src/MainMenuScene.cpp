#include "pch.h"
#include "MainMenuScene.h"

void MainMenuScene::Start()
{
	// Camera
	CreateGameObject("camera2", TYPE_3D, false);
	GetGameObjectByName("camera2").AddComponent<CameraComponent>(new CameraComponent());
	GetGameObjectByName("camera2").SetPosition({ 0, 0, 0.5f });

	RECT renderZone;
	GetClientRect(GetSceneManager()->GetGameManager()->GetRenderingManager().GetGraphicsDevice()->GetWindow(), &renderZone);
	UINT renderWidth = renderZone.right - renderZone.left;
	UINT renderHeight = renderZone.bottom - renderZone.top;

	// Title
	auto& gmTitle = CreateGameObject("Title", TYPE_2D, true);
	//m_playerHeart1 = mp_scene->GetGameObjectByName("Heart1");
	gmTitle.SetMesh(MESHES::LOCAL_SQUARE);
	gmTitle.SetTexture(TEXTURES::TITLE);
	gmTitle.SetPosition({ (float)renderWidth / 2, ((float)renderHeight / 2) - 200, 0 });
	gmTitle.SetScale({ (float)renderWidth * 0.5f , (float)renderHeight * 0.5f, 0 });
	gmTitle.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	// Buttons
	mp_buttonStart = &CreateGameObject<Button>(this, mp_sceneManager->GetWindow(), TEXTURES::BTN_START, "btnStart");

	mp_buttonArene = &CreateGameObject<Button>(this, mp_sceneManager->GetWindow(), TEXTURES::BTN_ARENA, "btnArene");
	mp_buttonArene->SetPosition({ (float)renderWidth / 2, mp_buttonStart->GetPosition().y + 200, 0 });

	mp_buttonQuit = &CreateGameObject<Button>(this, mp_sceneManager->GetWindow(), TEXTURES::BTN_SHUTDOWN, "btnquit");
	mp_buttonQuit->SetPosition({ (float)renderWidth - 70, (float)renderHeight - 70, 0 });
	mp_buttonQuit->SetScale({50, 50, 1});

	m_sceneHasChanged = false;
}

void MainMenuScene::Update(float deltatime)
{
	//START
	if (mp_buttonStart->GetMouseOnBtn() && !m_sceneHasChanged)
	{
		//OutputDebugStringA("\nDont touche me !\n");
		mp_buttonStart->SetScale({ 450, 150, 0 });
	}
	if (!mp_buttonStart->GetMouseOnBtn() && !m_sceneHasChanged)
	{
		//OutputDebugStringA("\nDont touche me !\n");
		mp_buttonStart->SetScale({ 400, 100, 0 });
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
		mp_buttonArene->SetScale({ 450, 150, 0 });
	}
	if (!mp_buttonArene->GetMouseOnBtn() && !m_sceneHasChanged)
	{
		//OutputDebugStringA("\nDont touche me !\n");
		mp_buttonArene->SetScale({ 400, 100, 0 });
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
		mp_buttonQuit->SetScale({ 70, 70, 1 });
	}
	if (!mp_buttonQuit->GetMouseOnBtn() && !m_sceneHasChanged)
	{
		mp_buttonQuit->SetScale({ 50, 50, 1 });
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
