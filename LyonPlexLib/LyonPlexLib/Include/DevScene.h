#pragma once
class DevScene : public Scene
{
public:
	void Start() override;
	void Update(float deltatime) override;
	void Release() override;

private:
	std::string m_lastPlacedGmName;
	int m_newIdGM;
};

