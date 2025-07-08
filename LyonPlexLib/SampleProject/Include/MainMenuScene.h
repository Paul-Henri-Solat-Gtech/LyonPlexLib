#pragma once
class MainMenuScene : public Scene
{
public:
	void Start() override;
	void Update(float deltatime) override;
	void Release() override;

private:

	Button m_buttonStart;

};

