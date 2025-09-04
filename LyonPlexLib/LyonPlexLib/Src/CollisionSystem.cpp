#include "pch.h"
#include "CollisionSystem.h"
#include "ECSManager.h"

#undef max
#undef min


bool CollisionSystem::Init(ECSManager* ecs)
{
	m_ECS = ecs;
	return false;
}

void CollisionSystem::Update()
{
	// collecte entities avec Transform + Collision
	auto mask = (1ULL << Transform_ID) | (1ULL << Collision_ID);
	std::vector<Entity> ents;
	m_ECS->ForEach(mask, [&](Entity e) { ents.push_back(e); });

	for (size_t i = 0; i < ents.size(); ++i)
	{
		for (size_t j = i + 1; j < ents.size(); ++j)
		{
			TryPair(ents[i], ents[j]);
		}
	}
}

void CollisionSystem::TryPair(Entity a, Entity b)
{
	if (m_ECS->GetComponent<Tag_World>(a) != nullptr && m_ECS->GetComponent<Tag_World>(b) != nullptr) // ne calcul pas les collisions entre les objets immobiles du monde
		return;

	auto* ta = m_ECS->GetComponent<TransformComponent>(a);
	auto* tb = m_ECS->GetComponent<TransformComponent>(b);
	auto* ca = m_ECS->GetComponent<CollisionComponent>(a);
	auto* cb = m_ECS->GetComponent<CollisionComponent>(b);

	XMFLOAT3 pa{ ta->position.x, ta->position.y, ta->position.z };
	XMFLOAT3 pb{ tb->position.x, tb->position.y, tb->position.z };

	bool hit = false;
	if (ca->shapeType == ColliderType::Sphere && cb->shapeType == ColliderType::Sphere) {
		hit = SphereVsSphere(pa, std::get<SphereCollider>(ca->shape),
			pb, std::get<SphereCollider>(cb->shape));
	}
	else if (ca->shapeType == ColliderType::AABB && cb->shapeType == ColliderType::AABB) {
		hit = AabbVsAabb(pa, std::get<AABBCollider>(ca->shape),
			pb, std::get<AABBCollider>(cb->shape));
	}
	else if (ca->shapeType == ColliderType::Sphere && cb->shapeType == ColliderType::AABB) {
		hit = SphereVsAabb(pa, std::get<SphereCollider>(ca->shape),
			pb, std::get<AABBCollider>(cb->shape));
	}
	else if (ca->shapeType == ColliderType::AABB && cb->shapeType == ColliderType::Sphere) {
		hit = SphereVsAabb(pb, std::get<SphereCollider>(cb->shape),
			pa, std::get<AABBCollider>(ca->shape));
	}
	// OBB
	else if (ca->shapeType == ColliderType::OBB && cb->shapeType == ColliderType::OBB) {
		std::get<OBBCollider>(ca->shape).orientation = ta->rotation;
		std::get<OBBCollider>(cb->shape).orientation = tb->rotation;
		hit = ObbVsObb(pa, std::get<OBBCollider>(ca->shape),
			pb, std::get<OBBCollider>(cb->shape));
	}
	else if (ca->shapeType == ColliderType::Sphere && cb->shapeType == ColliderType::OBB) {
		std::get<OBBCollider>(cb->shape).orientation = tb->rotation;
		hit = SphereVsObb(pa, std::get<SphereCollider>(ca->shape),
			pb, std::get<OBBCollider>(cb->shape));
	}
	else if (ca->shapeType == ColliderType::OBB && cb->shapeType == ColliderType::Sphere) {
		std::get<OBBCollider>(ca->shape).orientation = ta->rotation;
		hit = SphereVsObb(pb, std::get<SphereCollider>(cb->shape),
			pa, std::get<OBBCollider>(ca->shape));
	}
	else if (ca->shapeType == ColliderType::AABB && cb->shapeType == ColliderType::OBB) {
		std::get<OBBCollider>(cb->shape).orientation = tb->rotation;
		hit = ObbVsAabb( pa,std::get<AABBCollider>(ca->shape), pb,
			std::get<OBBCollider>(cb->shape));
	}
	else if (ca->shapeType == ColliderType::OBB && cb->shapeType == ColliderType::AABB) {
		std::get<OBBCollider>(ca->shape).orientation = ta->rotation;
		hit = ObbVsAabb( pb,std::get<AABBCollider>(cb->shape), pa,
			std::get<OBBCollider>(ca->shape));
	}

	if (hit)
	{
		CollisionEvent::Payload p{ a,b };
		EventBus::instance().publish<CollisionEvent>(p);
	}
}

bool CollisionSystem::SphereVsSphere(XMFLOAT3 p1, SphereCollider c1, XMFLOAT3 p2, SphereCollider c2)
{
	XMFLOAT3 d{ p2.x - p1.x - c1.offset.x + c2.offset.x,
			   p2.y - p1.y - c1.offset.y + c2.offset.y,
			   p2.z - p1.z - c1.offset.z + c2.offset.z };
	float dist2 = d.x * d.x + d.y * d.y + d.z * d.z;
	float r = c1.radius + c2.radius;
	return dist2 <= r * r;
}

bool CollisionSystem::AabbVsAabb(XMFLOAT3 p1, AABBCollider b1, XMFLOAT3 p2, AABBCollider b2)
{
	return
		std::abs(p1.x + b1.offset.x - (p2.x + b2.offset.x)) <= (b1.halfSize.x + b2.halfSize.x)
		&& std::abs(p1.y + b1.offset.y - (p2.y + b2.offset.y)) <= (b1.halfSize.y + b2.halfSize.y)
		&& std::abs(p1.z + b1.offset.z - (p2.z + b2.offset.z)) <= (b1.halfSize.z + b2.halfSize.z);
}

bool CollisionSystem::SphereVsAabb(XMFLOAT3 pc, SphereCollider s, XMFLOAT3 pa, AABBCollider a)
{
	float cx = pc.x + s.offset.x, cy = pc.y + s.offset.y, cz = pc.z + s.offset.z;
	float ax = pa.x + a.offset.x, ay = pa.y + a.offset.y, az = pa.z + a.offset.z;

	float nx = std::max(ax - a.halfSize.x, std::min(cx, ax + a.halfSize.x));
	float ny = std::max(ay - a.halfSize.y, std::min(cy, ay + a.halfSize.y));
	float nz = std::max(az - a.halfSize.z, std::min(cz, az + a.halfSize.z));

	float dx = cx - nx, dy = cy - ny, dz = cz - nz;

	return dx * dx + dy * dy + dz * dz <= s.radius * s.radius;
}
// 3) OBB vs OBB (SAT, sans m128_f32)
bool CollisionSystem::ObbVsObb(XMFLOAT3 p1, OBBCollider b1,	XMFLOAT3 p2, OBBCollider b2)
{

	// 3 axes locaux de chaque boîte
	XMMATRIX R1 = XMMatrixRotationQuaternion(XMLoadFloat4(&b1.orientation));
	XMMATRIX R2 = XMMatrixRotationQuaternion(XMLoadFloat4(&b2.orientation));
	XMVECTOR A[3] = { R1.r[0], R1.r[1], R1.r[2] };
	XMVECTOR B[3] = { R2.r[0], R2.r[1], R2.r[2] };

	// centres en espace monde
	XMVECTOR C1 = XMLoadFloat3(&p1) +
		XMVector3Rotate(XMLoadFloat3(&b1.offset), XMLoadFloat4(&b1.orientation));
	XMVECTOR C2 = XMLoadFloat3(&p2) +
		XMVector3Rotate(XMLoadFloat3(&b2.offset), XMLoadFloat4(&b2.orientation));

	// matrice des dot products et valeurs absolues (+epsilon)
	float R_[3][3], AbsR[3][3];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			R_[i][j] = XMVectorGetX(XMVector3Dot(A[i], B[j]));
			AbsR[i][j] = std::abs(R_[i][j]) + 1e-6f;
		}
	}

	// vecteur distance projeté sur A[]
	XMVECTOR tvec = C2 - C1;
	float t[3] = {
		XMVectorGetX(XMVector3Dot(tvec, A[0])),
		XMVectorGetX(XMVector3Dot(tvec, A[1])),
		XMVectorGetX(XMVector3Dot(tvec, A[2]))
	};

	// 1–3 : axes A0, A1, A2
	for (int i = 0; i < 3; ++i) {
		float ra = (&b1.halfSize.x)[i];
		float rb = b2.halfSize.x * AbsR[i][0]
			+ b2.halfSize.y * AbsR[i][1]
			+ b2.halfSize.z * AbsR[i][2];
		if (std::abs(t[i]) > ra + rb) return false;
	}
	// 4–6 : axes B0, B1, B2
	for (int j = 0; j < 3; ++j) {
		float ra = b1.halfSize.x * AbsR[0][j]
			+ b1.halfSize.y * AbsR[1][j]
			+ b1.halfSize.z * AbsR[2][j];
		float tj = std::abs(XMVectorGetX(XMVector3Dot(tvec, B[j])));
		float rb = (&b2.halfSize.x)[j];
		if (tj > ra + rb) return false;
	}
	// 7–15 : A_i × B_j
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			float ra = (&b1.halfSize.x)[(i + 1) % 3] * AbsR[(i + 2) % 3][j]
				+ (&b1.halfSize.x)[(i + 2) % 3] * AbsR[(i + 1) % 3][j];
			float rb = (&b2.halfSize.x)[(j + 1) % 3] * AbsR[i][(j + 2) % 3]
				+ (&b2.halfSize.x)[(j + 2) % 3] * AbsR[i][(j + 1) % 3];
			float tij = std::abs(
				t[(i + 2) % 3] * R_[(i + 1) % 3][j] - t[(i + 1) % 3] * R_[(i + 2) % 3][j]
			);
			if (tij > ra + rb) return false;
		}
	}

	return true;
}
// 4) Sphere vs OBB (on ramène le centre sphère en espace local OBB)
bool CollisionSystem::SphereVsObb(XMFLOAT3 ps, SphereCollider s,
	XMFLOAT3 p, OBBCollider b)
{
	// centre sphère en monde
	XMVECTOR C = XMLoadFloat3(&ps) + XMLoadFloat3(&s.offset);
	// inverser la rotation de l'OBB
	XMVECTOR invQ = XMQuaternionInverse(XMLoadFloat4(&b.orientation));

	//// GARDER OU ENLEVER ?
	//XMVECTOR qb = XMLoadFloat4(&b.orientation);
	//qb = XMQuaternionNormalize(qb);
	//XMVECTOR invQ = XMQuaternionInverse(qb);

	// centre sphère en espace local OBB
	XMVECTOR localC = XMVector3Rotate(C - XMLoadFloat3(&p), invQ);
	XMFLOAT3 lc;
	XMStoreFloat3(&lc, localC);

	// clamp sur la boîte alignée aux axes
	float cx = std::max(-b.halfSize.x, std::min(lc.x, b.halfSize.x));
	float cy = std::max(-b.halfSize.y, std::min(lc.y, b.halfSize.y));
	float cz = std::max(-b.halfSize.z, std::min(lc.z, b.halfSize.z));

	float dx = lc.x - cx, dy = lc.y - cy, dz = lc.z - cz;
	return dx * dx + dy * dy + dz * dz <= s.radius * s.radius;
}

// 5) OBB vs AABB (on applique SAT en traitant l’AABB comme OBB non orientée)
bool CollisionSystem::ObbVsAabb(XMFLOAT3 paabb, AABBCollider a,
	XMFLOAT3 pobb, OBBCollider b)
{
	// transformer l’AABB en OBB : orientation = identity, offset = a.offset
	OBBCollider boxA;
	boxA.halfSize = a.halfSize;
	boxA.offset = a.offset;
	boxA.orientation = { 0, 0, 0, 1 };
	// et appeler directement ObbVsObb avec centres échangés si besoin
	return ObbVsObb(pobb, b, paabb, boxA);
}
