#include "pch.h"
#include "MainMenuScene.h"

void MainMenuScene::Start()
{
	// Camera
	CreateGameObject("camera2", TYPE_3D, false);
	GetGameObjectByName("camera2").AddComponent<CameraComponent>(new CameraComponent());
	GetGameObjectByName("camera2").SetPosition({ 0, 0, 0.5f });

	// Buttons
	CreateGameObject("btnStart", TYPE_2D, true);
	GetGameObjectByName("btnStart").SetTexture(TEXTURES::start);
	GetGameObjectByName("btnStart").SetPosition({ 400, 500, 0 });
	GetGameObjectByName("btnStart").SetScale({ 400, 100, 0 });
	
	GetGameObjectByName("btnStart").GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	m_buttonStart.Init(GetGameObjectByName("btnStart"), mp_sceneManager->GetWindow());
}

void MainMenuScene::Update(float deltatime)
{
	if (InputManager::GetKeyIsReleased('A'))
	{
		ChangeScene("SampleScene2");
		return; // ! ne pas oublier
	}
	if (m_buttonStart.GetMouseOnBtn()) 
	{
		//OutputDebugStringA("\nDont touche me !\n");
		GetGameObjectByName("btnStart").SetScale({ 450, 150, 0 });
	}
	if (!m_buttonStart.GetMouseOnBtn())
	{
		//OutputDebugStringA("\nDont touche me !\n");
		GetGameObjectByName("btnStart").SetScale({ 400, 100, 0 });
	}
	if (m_buttonStart.GetBtnIsClicked())
	{
		OutputDebugStringA("\nHO YOU DARE CLICK ME !?\n");
		ChangeScene("GameScene");
	}
}

void MainMenuScene::Release()
{
	//m_buttonStart.Release();
}
