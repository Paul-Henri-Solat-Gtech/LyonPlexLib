#include "pch.h"
#include "Projectile.h"


Projectile::Projectile(Scene* scene, XMFLOAT3 posStart, XMFLOAT3 posTarget, ProjectileType type, float lifeTime)
{
	mp_scene = scene;
	m_projectileType = type;
	m_lifetime = lifeTime;

	InitGameObj(mp_scene->GetEcsManager(), mp_scene); // a corriger
	m_projectileGameObject = this;
	InitProjectile(posStart, posTarget);
}

void Projectile::InitProjectile( XMFLOAT3 posStart, XMFLOAT3 posTarget)
{


	std::string projName = "newProjectile" + std::to_string(mp_scene->GetSceneGameObjects().size());
	//OutputDebugStringA(projName.c_str());
	//m_projectileGameObject = &mp_scene->CreateGameObject(projName);
	//m_projectileGameObject->SetTag(Tag::TAG_Projectile);
	//m_projectileGameObject->SetPosition(posStart);
	//m_projectileGameObject->SetScale({ 0.2,0.2,0.8 });
	//auto projScale = m_projectileGameObject->GetScale();
	//m_projectileGameObject->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ projScale.x / 2, projScale.y / 2, projScale.z / 2 })));

	//Init(projName, mp_scene->GetEcsManager(), scene);

	SetTag(Tag::TAG_Projectile);
	SetPosition(posStart);
	SetScale({ 0.2,0.2,0.8 });
	auto projScale = GetScale();
	AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ projScale.x / 2, projScale.y / 2, projScale.z / 2 })));


	switch (m_projectileType)
	{
	case Laser:
		LookAt(posTarget);
		break;
	case Rock:
		//Laube(posStart, posTarget);
		break;
	case ProjectileTypeCount:
		break;
	default:
		break;
	}

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

void Projectile::Laube(XMFLOAT3 posStart, XMFLOAT3 posTarget)
{
	if (!m_projectileGameObject)
		return;

	// Direction plate (XZ)
	XMFLOAT3 dir = {
		posTarget.x - posStart.x,
		0.f,
		posTarget.z - posStart.z
	};

	// Normalise la direction XZ
	float len = sqrt(dir.x * dir.x + dir.z * dir.z);
	if (len > 0.0001f)
	{
		dir.x /= len;
		dir.z /= len;
	}

	// Ajoute une composante Y pour former un arc (valeur ajustable)
	XMFLOAT3 lobbedDir = {
		dir.x,
		0.5f, // élévation (plus grand = plus en cloche)
		dir.z
	};

	// Normalize finale
	float lobLen = sqrt(lobbedDir.x * lobbedDir.x + lobbedDir.y * lobbedDir.y + lobbedDir.z * lobbedDir.z);
	lobbedDir.x /= lobLen;
	lobbedDir.y /= lobLen;
	lobbedDir.z /= lobLen;

	// Calcul d’un point LookAt à partir de la direction lobée
	XMFLOAT3 targetLookAt = {
		posStart.x + lobbedDir.x,
		posStart.y + lobbedDir.y,
		posStart.z + lobbedDir.z
	};

	m_projectileGameObject->LookAt(targetLookAt);
}
