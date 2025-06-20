#pragma once
class DevScene : public Scene
{
public:
	void Start() override;
	void Update(float deltatime) override;
	void Release() override;

private:
	int m_newIdGM;

	std::string m_lastPlacedGmName;
	XMFLOAT3 m_lastPlacedGmPos;
};

