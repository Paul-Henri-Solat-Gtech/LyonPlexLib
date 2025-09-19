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
	auto projScale = GetScale();
	
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
	{
		SetTag(Tag::TAG_Projectile);
		SetTexture(TEXTURES::BTN_QUIT);
		SetScale({ 0.2f, 0.2f, 0.8f });
		projScale = GetScale();

		AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ projScale.x / 2, projScale.y / 2, projScale.z / 2 })));
		m_speed = 30;
		m_damage = 1;
		break;
	}
	case Rock:
	{
		SetTag(Tag::TAG_Projectile);
		SetTexture(TEXTURES::PIERRE);
		SetScale({ 2,2,2 });
		projScale = GetScale();
		
		int r = RandNumber(2);
		switch (r)
		{
		case 0:
			SetMesh(MESHES::ROCKBIG);
			AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ projScale.x * 3 / 2, projScale.y * 5/ 2, projScale.z * 3 / 2 })));
			break;
		case 1:
			SetMesh(MESHES::ROCKMedium);
			AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ projScale.x * 3 / 2, projScale.y * 2 / 2, projScale.z * 2 / 2 })));
			break;
		case 2:
			SetMesh(MESHES::ROCKLM2);
			AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ projScale.x * 2 / 2, projScale.y * 1 / 2, projScale.z * 1.5f / 2 })));
			break;
		}

		Laube(posStart, posTarget);
		break;
	}
	case BigRock:
	{
		SetTag(Tag::TAG_Projectile);
		SetTexture(TEXTURES::PIERRE);
		SetScale({ 8,8,8 });
		projScale = GetScale();

		int r = RandNumber(2);
		switch (r)
		{
		case 0:
			SetMesh(MESHES::ROCKBIG);
			AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ projScale.x * 3 / 2, projScale.y * 5 / 2, projScale.z * 3 / 2 })));
			break;
		case 1:
			SetMesh(MESHES::ROCKMedium);
			AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ projScale.x * 3 / 2, projScale.y * 2 / 2, projScale.z * 2 / 2 })));
			break;
		case 2:
			SetMesh(MESHES::ROCKLM2);
			AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ projScale.x * 2 / 2, projScale.y * 1 / 2, projScale.z * 1.5f / 2 })));
			break;
		}

		Laube(posStart, posTarget);
		break;
	}
	case AirSlash:
	{
		SetTag(Tag::TAG_ProjectilePlayer);
		SetTexture(TEXTURES::EAU);
		SetScale({ 2,0.1,0.8 });
		projScale = GetScale();

		AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ projScale.x / 2, projScale.y / 2, projScale.z / 2 })));
		m_speed = 70;
		m_damage = 1;
		break;
	}
	default:
		break;
	}

	//OutputDebugStringA("\nINIT PROJECTILE REUSSI !\n");
}



void Projectile::OnUpdate(float deltatime)
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
	case BigRock:
	{
		// integration simple Euler pour laube
		m_laubeVelocity.y -= m_laubeGravity * deltatime;

		XMFLOAT3 pos = GetPosition();
		pos.x += m_laubeVelocity.x * deltatime;
		pos.y += m_laubeVelocity.y * deltatime;
		pos.z += m_laubeVelocity.z * deltatime;
		SetPosition(pos);

		// mise a jour rotation pour suivre la vitesse si non nulle
		XMVECTOR velV = XMLoadFloat3(&m_laubeVelocity);
		float len = XMVectorGetX(XMVector3Length(velV));
		if (len > 0.001f)
		{
			XMVECTOR dirV = XMVector3Normalize(velV);
			XMVECTOR eye = XMLoadFloat3(&pos);
			XMMATRIX view = XMMatrixLookToLH(eye, dirV, XMVectorSet(0.f, 1.f, 0.f, 0.f));
			XMMATRIX world = XMMatrixInverse(nullptr, view);
			XMVECTOR quat = XMQuaternionRotationMatrix(world);
			XMFLOAT4 q; XMStoreFloat4(&q, quat);
			SetRotation(q);
		}
		break;
	}
	case AirSlash:
		//AddRotation({ 0,1,0 });
		break;
	default:
		break;
	}
}

void Projectile::Destroy()
{
	mp_scene->DestroyGameObject(*this);
}

void Projectile::Laube(XMFLOAT3 posStart, XMFLOAT3 posTarget)
{
	// displacement
	XMFLOAT3 d = { posTarget.x - posStart.x, posTarget.y - posStart.y, posTarget.z - posStart.z };
	float dxz = sqrtf(d.x * d.x + d.z * d.z);

	const float g = m_laubeGravity;
	const float s = m_speed;
	const float s2 = s * s;

	if (dxz < 0.0001f)
	{
		// quasi vertical, fallback: tirer vers la cible
		XMFLOAT3 dir = { 0.f, (d.y > 0.f ? 1.f : -1.f), 0.f };
		m_laubeVelocity = { dir.x * s, dir.y * s, dir.z * s };
	}
	else
	{
		// discriminant de la solution balistique
		float inside = s2 * s2 - g * (g * dxz * dxz + 2.f * d.y * s2);

		if (inside < 0.f)
		{
			// pas de solution physique: fallback visuel (inclinaison fixe)
			XMFLOAT3 dir = { d.x / dxz, 0.5f, d.z / dxz };
			XMVECTOR dv = XMLoadFloat3(&dir);
			dv = XMVector3Normalize(dv);
			XMFLOAT3 dirN; 
			XMStoreFloat3(&dirN, dv);
			m_laubeVelocity = { dirN.x * s, dirN.y * s, dirN.z * s };
		}
		else
		{
			float sqrtv = sqrtf(inside);
			// ici on prend l'arc haut; pour arc bas remplacer +sqrtv par -sqrtv
			float angle = atanf((s2 + sqrtv) / (g * dxz));
			float cosA = cosf(angle);
			float sinA = sinf(angle);
			float vxz = s * cosA;
			XMFLOAT3 dirXZ = { d.x / dxz, 0.f, d.z / dxz };
			m_laubeVelocity.x = dirXZ.x * vxz;
			m_laubeVelocity.y = s * sinA;
			m_laubeVelocity.z = dirXZ.z * vxz;
		}
	}

	// orientation initiale pour regarder dans la direction de la vitesse
	XMFLOAT3 lookAt = { posStart.x + m_laubeVelocity.x, posStart.y + m_laubeVelocity.y, posStart.z + m_laubeVelocity.z };
	LookAt(lookAt);
}

//de 0 a max
int Projectile::RandNumber(int max)
{
	int r = rand() % (max + 1);
	return r;
}
