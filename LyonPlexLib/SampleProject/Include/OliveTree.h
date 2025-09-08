#pragma once
//#include "GameObject.h"

class OliveTree : public GameObject
{
public:
	OliveTree(ECSManager* ecsManager, Scene* scene, XMFLOAT3 position);
	//~OliveTree();

	void OnUdpdate(float deltatime) override;

	void SetScale(XMFLOAT3 scl);
	void SetPosition(XMFLOAT3 pos);

private:
	GameObject* mp_trunk = nullptr;
	GameObject* mp_leaves = nullptr;

	GameObject* mp_trunkCol = nullptr;
	GameObject* mp_leavesCol = nullptr;

	XMFLOAT3 m_trunkColidScale;
	XMFLOAT3 m_leavesColidScale;
};

