#pragma once
#include "Player.h"

class HealingRock : public GameObject
{
public:
	HealingRock(Scene* scene, GameObject& playerGm, XMFLOAT3 pos, float lifetime);

	void OnUpdate(float deltatime) override;
	void Destroy();

private:
	float m_lifetime = 10;
	GameObject& m_playerGm;
};

