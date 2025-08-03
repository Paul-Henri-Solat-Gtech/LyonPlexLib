#include "pch.h"
#include "Projectile.h"

void Projectile::Init(Scene* scene, XMFLOAT3 posStart, XMFLOAT3 posTarget, float lifeTime)
{
	mp_scene = scene;
	m_lifetime = lifeTime;

	std::string projName = "newProjectile" + std::to_string(mp_scene->GetSceneGameObjects().size());
	OutputDebugStringA(projName.c_str());
	m_projectileGameObject = &mp_scene->CreateGameObject(projName);
	m_projectileGameObject->SetTag(Tag::TAG_Projectile);
	m_projectileGameObject->SetPosition(posStart);
	m_projectileGameObject->SetScale({ 0.2,0.2,0.8 });
	auto projScale = m_projectileGameObject->GetScale();
	m_projectileGameObject->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ projScale.x / 2, projScale.y / 2, projScale.z / 2 })));

	m_projectileGameObject->LookAt(posTarget);

	OutputDebugStringA("\nINIT PROJECTILE REUSSI !\n");
}


void Projectile::OnUdpdate(float deltatime)
{
	if (!m_projectileGameObject)
		return;

	if (m_lifetime <= 0)
	{
		Destroy();
		return;
	}
	else
	{
		m_lifetime -= 1 * deltatime;
		m_projectileGameObject->MoveForward(deltatime * 30);
	}
}

void Projectile::Destroy()
{
	if (m_projectileGameObject)
	{
		mp_scene->DestroyGameObject(*m_projectileGameObject);
		m_projectileGameObject = nullptr;
	}
}
