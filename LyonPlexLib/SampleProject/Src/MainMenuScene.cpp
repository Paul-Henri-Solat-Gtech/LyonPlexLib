#include "pch.h"
#include "MainMenuScene.h"

void MainMenuScene::Start()
{
	// Camera
	CreateGameObject("camera2", TYPE_3D, false);
	GetGameObjectByName("camera2").AddComponent<CameraComponent>(new CameraComponent());
	GetGameObjectByName("camera2").SetPosition({ 0, 0, 0.5f });

	// Buttons
	mp_buttonStart = &CreateGameObject<Button>(this, mp_sceneManager->GetWindow());
	//GetGameObjectByName("btnStart").SetTexture(TEXTURES::start);
	//GetGameObjectByName("btnStart").SetPosition({ 400, 500, 0 });
	//GetGameObjectByName("btnStart").SetScale({ 400, 100, 0 });
}

void MainMenuScene::Update(float deltatime)
{
	//if (InputManager::GetKeyIsReleased('A'))
	//{
	//	ChangeScene("SampleScene2");
	//	return; // ! ne pas oublier
	//}
	if (mp_buttonStart->GetMouseOnBtn())
	{
		//OutputDebugStringA("\nDont touche me !\n");
		mp_buttonStart->SetScale({ 450, 150, 0 });
	}
	if (!mp_buttonStart->GetMouseOnBtn())
	{
		//OutputDebugStringA("\nDont touche me !\n");
		mp_buttonStart->SetScale({ 400, 100, 0 });
	}
	if (mp_buttonStart->GetBtnIsClicked())
	{
		OutputDebugStringA("\nHO YOU DARE CLICK ME !?\n");
		ChangeScene("GameScene");
	}
}

void MainMenuScene::Release()
{
	//m_buttonStart.Release();
}
