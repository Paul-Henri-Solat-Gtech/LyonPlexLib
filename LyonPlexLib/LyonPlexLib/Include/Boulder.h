#pragma once
#include "GameObject.h"
#include "Utils.h"


class Boulder : public GameObject
{
public:

	Boulder(ECSManager* ecsManager, GameManager* gameManager, GameObject& gameObjectPlayer, Scene* scene, XMFLOAT2 posXZmin, XMFLOAT2 posXZmax);
	//~Boulder();

	void OnUpdate(float deltatime) override;

	void GetPushed(Utils::Vector3 dir);

	GameObject* GetColliderGameObject() { return mp_collider; }

	void SetScale(XMFLOAT3 scl);

	GameObject& m_playerGm;
private:
	GameManager* mp_gameManager = nullptr;
	ECSManager* mp_ecs = nullptr;

	GameObject* mp_collider = nullptr;

	XMFLOAT2 m_posXZmin = { 0,0 };
	XMFLOAT2 m_posXZmax = { 0,0 };

	Utils::Vector3 m_dir = { 0,0,0 };

	float m_slideDistance = 10;
	float m_slideDistLeft = 0;

	int m_weight; // ??
};

