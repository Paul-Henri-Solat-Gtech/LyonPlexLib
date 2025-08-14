#pragma once
#include "GameObject.h"
#include "Utils.h"


class Boulder : public GameObject
{
public:

	Boulder(ECSManager* ecsManager, GameManager* gameManager, GameObject& gameObjectPlayer, Scene* scene);
	//~Boulder();

	void OnUdpdate(float deltatime) override;

	void GetPushed(Utils::Vector3 dir);

	GameObject& m_playerGm;
private:
	GameManager* mp_gameManager = nullptr;
	ECSManager* mp_ecs = nullptr;

Utils::Vector3 m_dir = { 0,0,0 };

	float m_slideDistance = 10;
	float m_slideDistLeft = 0;

	int m_weight; // ??
};

