#include "pch.h"
#include "IntroScene.h"

void IntroScene::Start()
{
	RECT renderZone;
	GetClientRect(GetSceneManager()->GetGameManager()->GetRenderingManager().GetGraphicsDevice()->GetWindow(), &renderZone);
	UINT renderWidth = renderZone.right - renderZone.left;
	UINT renderHeight = renderZone.bottom - renderZone.top;

	CreateGameObject("Background", TYPE_2D, true);
	auto background = GetGameObjectByName("Background");
	background.SetMesh(MESHES::LOCAL_SQUARE);
	background.SetTexture(TEXTURES::lightLp);
	background.SetPosition({ (float)renderWidth / 2, (float)renderHeight / 2, 0 });
	background.SetScale({ (float)renderWidth, (float)renderHeight, 0 });
	//background.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	CreateGameObject("LogoLyonPlex", TYPE_2D, true);
	m_LyonplexLogo = GetGameObjectByName("LogoLyonPlex");
	m_LyonplexLogo.SetMesh(MESHES::LOCAL_SQUARE);
	m_LyonplexLogo.SetTexture(TEXTURES::LYONPLEXLOGO);
	m_LyonplexLogo.SetPosition({ (float)renderWidth / 2, (float)renderHeight / 2, 0 });
	m_LyonplexLogo.SetScale({ (float)renderWidth * 0.07f, (float)renderHeight * 0.07f, 0 });
	m_LyonplexLogo.GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

	m_sceneHasChanged = false;
	m_soundHasBeenPlayed = false;
	m_introTime = 4;

	// sounds
	//GetSceneManager()->GetGameManager()->GetSoundManager()->CreateSound("roar", L"../LyonPlexLib/Ressources/Roar.wav");
}

void IntroScene::Update(float deltatime)
{
	if (m_introTime <= 0 && !m_sceneHasChanged)
	{
		m_sceneHasChanged = true;
		ChangeScene("MainMenuScene");
	}
	else
	{
		m_introTime -= 1 * deltatime;

		auto logoScale = m_LyonplexLogo.GetScale();

		if (logoScale.x >= 200 && !m_soundHasBeenPlayed)
		{
			GetSceneManager()->GetGameManager()->GetSoundManager()->PlaySoundPlex("roar");
			m_soundHasBeenPlayed = true;
		}
		if (logoScale.x < 200)
		{
			m_LyonplexLogo.SetScale({ logoScale.x + 0.5f, logoScale.y + 0.5f, 0 });
		}

	}
}

void IntroScene::Release()
{
}