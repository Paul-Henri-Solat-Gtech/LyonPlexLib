#pragma once
class DevScene : public Scene
{
public:
	void Start() override;
	void Update(float deltatime) override;
	void Release() override;

private:
	GameObject m_lastPlacedGm;
	int m_newIdGM;
};

