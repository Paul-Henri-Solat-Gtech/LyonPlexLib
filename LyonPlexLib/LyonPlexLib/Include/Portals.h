#pragma once
class Portals : public GameObject
{
public:

	Portals(ECSManager* ecsManager, GameManager* gameManager, GameObject& gameObjectPlayer, Scene* scene);
	//~Portals();

	void OnUdpdate(float deltatime) override;


	GameObject& m_playerGm;
private:
	GameManager* mp_gameManager = nullptr;
	ECSManager* mp_ecs = nullptr;
	//GameObject& m_portalGm;

	float m_timer = 0;
	int m_capacity = 4;
};

