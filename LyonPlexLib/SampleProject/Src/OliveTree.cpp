#include "pch.h"
#include "OliveTree.h"

OliveTree::OliveTree(ECSManager* ecsManager, Scene* scene, XMFLOAT3 position, int treeNum)
{
	m_treeNum = treeNum;

	InitOliveTreeGameObj(ecsManager, scene);

	mp_trunk = &scene->CreateGameObject("olive_trunk", MESHES::OLIVIER_1_TRONC);
	scene->SetParent(*mp_trunk, *this);

	mp_trunk->SetPosition({ 0,0,0 });
	mp_trunk->SetRotation({ 0,0,0,1 });
	mp_trunk->SetScale({ 1,1,1 });
	//mp_trunk->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 0.850000143,2,1 }, { 0,0.2164395,0,0.976296067 }, { 0.115241952,1.324885845,0.244909346 })));

	mp_leaves = &scene->CreateGameObject("olive_leaves", MESHES::OLIVIER_1_FEUILLES);
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
	mp_trunkCol->AddComponent<Tag_OliveTree>(new Tag_OliveTree);

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

	const uint32_t oliveId = mp_trunkCol->GetEntity().id;
	Scene* scenePtr = mp_scene;
	OliveTree* self = this;

	EventBus::instance().subscribe<CollisionEvent>([oliveId, scenePtr, self](CollisionEvent::Payload const& p)
		{
			if (p.a.id != oliveId && p.b.id != oliveId) return;

			Entity otherE = (p.a.id == oliveId) ? p.b : p.a;
			if (otherE.id == 0 || otherE.id == static_cast<uint32_t>(-1)) {
				OutputDebugStringA("Enemy collision: otherE id invalid -> ignore\n");
				return;
			}

			// get pointer (peut retourner nullptr si l'objet a étEdétruit)
			GameObject* otherGO = scenePtr->GetGameObjectByID(otherE);
			if (!otherGO) return; // évite deref null

			auto tag = otherGO->GetTag();

			if (tag == TAG_Environment)
				return;

			if (tag == TAG_ProjectilePlayer)
			{
				self->m_isCut = true;
			}
		});

}

void OliveTree::OnUpdate(float deltatime)
{
	if (m_isCut)
	{
		GameObject* cut_trunkCol = nullptr;
		switch (m_treeNum)
		{
		case 1:
			mp_leaves->SetPosition({ -25 / GetScale().x, -12 / GetScale().y, -15 / GetScale().z });
			//mp_leaves->SetTransformRotation({ 90,60,0 });
			mp_leaves->SetTransformRotation({ 180,0,0 });
			mp_leavesCol->SetPosition({ 0, 0.5, 0 });

			cut_trunkCol = &mp_scene->CreateGameHitbox();
			cut_trunkCol->SetPosition({ 49,-6.09082365,131 });
			cut_trunkCol->SetRotation({ 0,0,0,1 });
			cut_trunkCol->SetScale({ 7,6,9 });
			cut_trunkCol->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3.5,3,4.5 })));

			m_isCut = false;
			break;
		case 2:
			mp_leaves->SetPosition({ 0 / GetScale().x, -15 / GetScale().y, 55.f / GetScale().z });
			mp_leaves->SetTransformRotation({ 180,0,0 });
			mp_leavesCol->SetPosition({ 0, 0.5, 0 });

			cut_trunkCol = &mp_scene->CreateGameHitbox();
			cut_trunkCol->SetPosition({ -66.287994385,-1.48188591,-24.33288002 });
			cut_trunkCol->SetRotation({ 0,0,0,1 });
			cut_trunkCol->SetScale({ 16,8,10 });
			cut_trunkCol->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8,5.5,5 })));

			m_isCut = false;
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