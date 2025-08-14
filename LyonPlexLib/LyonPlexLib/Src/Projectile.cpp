#include "pch.h"
#include "Projectile.h"


Projectile::Projectile(Scene* scene, XMFLOAT3 posStart, XMFLOAT3 posTarget, ProjectileType type, float lifeTime)
{
	mp_scene = scene;
	m_projectileType = type;
	m_lifetime = lifeTime;

	InitGameObj(mp_scene->GetEcsManager(), mp_scene); // a corriger
	InitProjectile(posStart, posTarget);
}

void Projectile::InitProjectile( XMFLOAT3 posStart, XMFLOAT3 posTarget)
{
	AddComponent<Tag_Projectile>(new Tag_Projectile());

	SetPosition(posStart);
	SetScale({ 0.2,0.2,0.8 });
	auto projScale = GetScale();
	AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ projScale.x / 2, projScale.y / 2, projScale.z / 2 })));
	m_speed = 30;
	m_damage = 1;

	// rotation projectile
	XMFLOAT3 dir = { posTarget.x - posStart.x, posTarget.y - posStart.y, posTarget.z - posStart.z };
	XMVECTOR dirV = XMLoadFloat3(&dir);
	dirV = XMVector3Normalize(dirV);

	// Build a look-to matrix then invert to get a world matrix for the projectile
	XMVECTOR eye = XMLoadFloat3(&posStart);
	XMMATRIX view = XMMatrixLookToLH(eye, dirV, XMVectorSet(0.f, 1.f, 0.f, 0.f));
	XMMATRIX world = XMMatrixInverse(nullptr, view);

	// quaternion from world matrix
	XMVECTOR quat = XMQuaternionRotationMatrix(world);
	XMFLOAT4 qf; XMStoreFloat4(&qf, quat);
	SetRotation(qf);
	//--

	switch (m_projectileType)
	{
	case Laser:
		SetTag(Tag::TAG_Projectile);
		SetTexture(TEXTURES::NOTEXTURE);
		m_speed = 30;
		m_damage = 1;
		break;
	case Rock:
		SetTag(Tag::TAG_Projectile);
		break;
	case AirSlash:
		SetTag(Tag::TAG_ProjectilePlayer);
		SetTexture(TEXTURES::WATER_NORMAL);
		SetScale({ 2,0.1,0.8 });
		m_speed = 70;
		m_damage = 1;
		break;
	default:
		break;
	}

	//OutputDebugStringA("\nINIT PROJECTILE REUSSI !\n");
}



void Projectile::OnUdpdate(float deltatime)
{
	//if (!m_projectileGameObject)
	//	return;

	if (m_lifetime <= 0)
	{
		Destroy();
		return;
	}
	else
	{
		m_lifetime -= 1 * deltatime;
		//m_projectileGameObject->MoveForward(deltatime * m_speed);
		MoveForward(deltatime * m_speed);
	}

	switch (m_projectileType)
	{
	case Laser:

		break;
	case Rock:

		break;
	case AirSlash:
		//AddRotation({ 0,1,0 });
		break;
	default:
		break;
	}
}

void Projectile::Destroy()
{
	//if (m_projectileGameObject)
	//{

	//	m_projectileGameObject = nullptr;
	//}
	mp_scene->DestroyGameObject(*this);
}

void Projectile::Laube(XMFLOAT3 posStart, XMFLOAT3 posTarget)
{
	//if (!m_projectileGameObject)
	//	return;

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

	LookAt(targetLookAt);
}
