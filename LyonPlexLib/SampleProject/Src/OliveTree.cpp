#include "pch.h"
#include "OliveTree.h"

OliveTree::OliveTree(ECSManager* ecsManager, Scene* scene, XMFLOAT3 position)
{
	static int treeNum = 1;
	m_treeNum = treeNum;

	InitOliveTreeGameObj(ecsManager, scene);

	mp_trunk = &scene->CreateGameObject("olive_trunk", 32, 4294967295);
	scene->SetParent(*mp_trunk, *this);

	mp_trunk->SetTag(TAG_Environment);
	mp_trunk->SetPosition({ 0,0,0 });
	mp_trunk->SetRotation({ 0,0,0,1 });
	mp_trunk->SetScale({ 1,1,1 });
	//mp_trunk->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 0.850000143,2,1 }, { 0,0.2164395,0,0.976296067 }, { 0.115241952,1.324885845,0.244909346 })));

	mp_leaves = &scene->CreateGameObject("olive_leaves", 33, 4294967295);
	scene->SetParent(*mp_leaves, *mp_trunk);

	mp_leaves->SetTag(TAG_Environment);
	mp_leaves->SetPosition({ 0.155318305,4.349291325,-0.093118094 }); // LOCAL POS
	mp_leaves->SetRotation({ 0,0,-0.034899499,0.999390841 });		  // LOCAL ROTA
	mp_leaves->SetScale({ 1,1,1 });
	//mp_leaves->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 2,2,4.5 }, { 0,0,0,1 }, { -0.192756951,0.626702487,0.129970118 }/*{0,0,0}*/)));


	mp_trunkCol = &scene->CreateGameObject("test 1", TYPE_3D_TRANSPARENT);
	scene->SetParent(*mp_trunkCol, *mp_trunk);

	mp_trunkCol->SetTag(TAG_Environment);
	mp_trunkCol->GetComponent<MeshComponent>()->alpha = 0.4;
	mp_trunkCol->SetTexture(TEXTURES::GRID);
	mp_trunkCol->SetPosition({ 0.115241952,1.324885845,0.244909346 });
	mp_trunkCol->SetScale({ 1.700000286,3,2 });
	mp_trunkCol->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB()));


	mp_leavesCol = &scene->CreateGameObject("test 2", TYPE_3D_TRANSPARENT);
	scene->SetParent(*mp_leavesCol, *mp_leaves);

	mp_leavesCol->SetTag(TAG_Environment);
	mp_leavesCol->GetComponent<MeshComponent>()->alpha = 0.4;
	mp_leavesCol->SetTexture(TEXTURES::GRID);
	mp_leavesCol->SetPosition({ -0.192756951,0.626702487,0.129970118 });
	mp_leavesCol->SetRotation({ 0,0,0,1 });
	mp_leavesCol->SetScale({ 4,4,9 });
	mp_leavesCol->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB()));

	SetPosition(position);
	SetScale({ 1,1,1 });

}

void OliveTree::OnUpdate(float deltatime)
{
	if (m_isCut)
	{
		switch (m_treeNum)
		{
		case 1:
			mp_leaves->SetPosition({ 0,0,0 });
			break;
		case 2:
			mp_leaves->SetPosition({ 0,0,0 });
			break;
		default:
			break;
		}
	}

}

//void OliveTree::SetPosition(XMFLOAT3 pos)
//{
//	GetComponent<TransformComponent>()->position = pos; GetComponent<TransformComponent>()->dirty = true;
//	//mp_trunkCol->GetComponent<TransformComponent>()->position = pos; mp_trunkCol->GetComponent<TransformComponent>()->dirty = true;
//	//mp_leavesCol->GetComponent<TransformComponent>()->position = pos; mp_leavesCol->GetComponent<TransformComponent>()->dirty = true;
//}

void OliveTree::SetScale(XMFLOAT3 scl)
{

	GetComponent<TransformComponent>()->scale = scl;
	GetComponent<TransformComponent>()->dirty = true;

	//mp_trunk->GetComponent<TransformComponent>()->scale = scl;
	//mp_trunk->GetComponent<TransformComponent>()->dirty = true;

	auto& colTrunk = std::get<OBBCollider>(mp_trunkCol->GetComponent<CollisionComponent>()->shape);

	colTrunk.halfSize.x = 1.700000286f * scl.x/* * scl.x*/ / 2;
	colTrunk.halfSize.y = 3 * scl.y /** scl.y*/ / 2;
	colTrunk.halfSize.z = 2 * scl.z /** scl.z*/ / 2;

	auto& colLeaves = std::get<OBBCollider>(mp_leavesCol->GetComponent<CollisionComponent>()->shape);

	colLeaves.halfSize.x = 2 * scl.x /** scl.x*/;
	colLeaves.halfSize.y = 2 * scl.y /** scl.y*/;
	colLeaves.halfSize.z = 4.5 * scl.z /** scl.z*/;


};