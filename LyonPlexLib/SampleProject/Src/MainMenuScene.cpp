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

	// Buttons
	mp_buttonStart = &CreateGameObject<Button>(this, mp_sceneManager->GetWindow(), TEXTURES::start, "btnStart");
	
	//mp_buttonArene = &CreateGameObject<Button>(this, mp_sceneManager->GetWindow(), TEXTURES::TEMPLE, "btnArene");
	//mp_buttonArene->SetPosition({(float)renderWidth / 2, mp_buttonStart->GetPosition().y + 200, 0});

	m_sceneHasChanged = false;
}

void MainMenuScene::Update(float deltatime)
{
	//if (InputManager::GetKeyIsReleased('A'))
	//{
	//	ChangeScene("SampleScene2");
	//	return; // ! ne pas oublier
	//}

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
		OutputDebugStringA("\nHO YOU DARE CLICK ME !?\n");
		m_sceneHasChanged = true;
		ChangeScene("GameScene");
		return;
	}
	//ARENE
	//if (mp_buttonArene->GetMouseOnBtn() && !m_sceneHasChanged)
	//{
	//	//OutputDebugStringA("\nDont touche me !\n");
	//	mp_buttonArene->SetScale({ 450, 150, 0 });
	//}
	//if (!mp_buttonArene->GetMouseOnBtn() && !m_sceneHasChanged)
	//{
	//	//OutputDebugStringA("\nDont touche me !\n");
	//	mp_buttonArene->SetScale({ 400, 100, 0 });
	//}
}

void MainMenuScene::Release()
{
	mp_buttonStart = nullptr;
}
