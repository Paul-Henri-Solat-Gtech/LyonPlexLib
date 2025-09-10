#include "pch.h"
#include "Boulder.h"

Boulder::Boulder(ECSManager* ecsManager, GameManager* gameManager, GameObject& gameObjectPlayer, Scene* scene, XMFLOAT2 posXZmin, XMFLOAT2 posXZmax) : m_playerGm(gameObjectPlayer), m_weight(0)
{
	InitGameObj(ecsManager, scene);
	mp_gameManager = gameManager;
	mp_ecs = ecsManager;

	m_posXZmin = posXZmin;
	m_posXZmax = posXZmax;

	SetMesh(MESHES::ROCKLM1);
	AddComponent<Tag_Boulder>(new Tag_Boulder());

	//AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.01, 0.6, 0.7 }, { 0, 0,0,1 }, { -0.1, 0.05, -0.01 })));

	mp_collider = &scene->CreateGameObject("boulderCol", TYPE_3D_TRANSPARENT);
	scene->SetParent(*mp_collider, *this);

	mp_collider->SetTag(TAG_Environment);
	mp_collider->GetComponent<MeshComponent>()->alpha = 0.4;
	mp_collider->SetTexture(TEXTURES::GRID);
	//mp_collider->SetPosition({ -0.1,0.05,-0.01 });
	mp_collider->SetPosition({0,0,0 });
	mp_collider->SetScale({ 2.02,1.2,1.4 });
	//mp_collider->SetScale({ 4.04,1.2,1.4 });
	mp_collider->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB()));
}

void Boulder::OnUpdate(float deltatime)
{

	if (m_slideDistLeft > 0.2)
	{
		float dist = Utils::lerp(0, m_slideDistLeft, 0.05);
		MoveInDirection({ m_dir.x, m_dir.y, m_dir.z }, dist);

		m_slideDistLeft -= dist;
	}

	if (GetPosition().x < m_posXZmin.x)	GetPosition().x = m_posXZmin.x;
	if (GetPosition().x > m_posXZmax.x)	GetPosition().x = m_posXZmax.x;
	if (GetPosition().z < m_posXZmin.y)	GetPosition().z = m_posXZmin.y;
	if (GetPosition().z > m_posXZmax.y)	GetPosition().z = m_posXZmax.y;

}

void Boulder::GetPushed(Utils::Vector3 dir)
{
	m_dir = dir;
	m_slideDistLeft = m_slideDistance;
}


void Boulder::SetScale(XMFLOAT3 scl)
{
	//auto col = std::get<OBBCollider>(GetComponent<CollisionComponent>()->shape);
	//col.halfSize.x = 1.01 * scl.x* scl.x*2;
	//col.halfSize.y = 0.6 * scl.y * scl.y*2;
	//col.halfSize.z = 0.7 * scl.z* scl.z*2;

	//col.offset.x = -0.1 * scl.x * scl.x*2;
	//col.offset.y = 0.05 * scl.y * scl.y*2;
	auto& col = std::get<OBBCollider>(mp_collider->GetComponent<CollisionComponent>()->shape);
	col.halfSize.x = 1.01 * scl.x ;
	col.halfSize.y = 0.6 * scl.y ;
	col.halfSize.z = 0.7 * scl.z ;

	//col.offset.x = -0.1 * scl.x * scl.x * 4;
	//col.offset.y = 0.05 * scl.y * scl.y * 4;

	GetComponent<TransformComponent>()->scale = scl;
	GetComponent<TransformComponent>()->dirty = true;
};