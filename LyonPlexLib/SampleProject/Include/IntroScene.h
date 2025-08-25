#pragma once
class IntroScene : public Scene
{
public:
	void Start() override;
	void Update(float deltatime) override;
	void Release() override;

private:

	GameObject m_LyonplexLogo;
	float m_introTime;
	bool m_sceneHasChanged, m_soundHasBeenPlayed;
};
