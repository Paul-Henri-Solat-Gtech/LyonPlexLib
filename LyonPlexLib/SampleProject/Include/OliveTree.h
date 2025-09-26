#pragma once
//#include "GameObject.h"

class OliveTree : public GameObject
{
public:
	OliveTree(ECSManager* ecsManager, Scene* scene, XMFLOAT3 position, int treeNum);
	//~OliveTree();

	void OnUpdate(float deltatime) override;

	void SetScale(XMFLOAT3 scl);
	//void SetPosition(XMFLOAT3 pos);

private:
	GameObject* mp_trunk = nullptr;
	GameObject* mp_leaves = nullptr;

	GameObject* mp_trunkCol = nullptr;
	GameObject* mp_leavesCol = nullptr;

	GameObject* cut_trunkCol = nullptr;

	XMFLOAT3 m_trunkColidScale;
	XMFLOAT3 m_leavesColidScale;

	bool m_isCut = false, m_endCut1 = false, m_endCut2 = false;
	int m_treeNum = 0, phase = 1;

	bool xOK = false, yOK = false, zOK = false, rotOK = false;
	float rotationDeg = 0.0f;
	int degCount = 0;
	XMFLOAT3 startPos = { 0,0,0 };
	float timer = 0.0f;

	bool treeSound = false;
};

