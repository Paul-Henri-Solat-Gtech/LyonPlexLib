#pragma once
class MainMenuScene : public Scene
{
public:
	void Start() override;
	void Update(float deltatime) override;
	void Release() override;

private:

	Button* mp_buttonStart;
	Button* mp_buttonArene;
	Button* mp_buttonQuit;
	bool m_sceneHasChanged, m_btnStartSelected, m_btnArenaSelected;
};

