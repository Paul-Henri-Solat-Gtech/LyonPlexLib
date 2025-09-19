#include "pch.h"
#include "CollisionSystem.h"
#include "ECSManager.h"

#undef max
#undef min

//inline bool HasAny(ComponentMask mask, uint64_t flags) { return (mask & flags) != 0; }
//inline bool HasAll(ComponentMask mask, uint64_t flags) { return (mask & flags) == flags; }
//inline bool Has(ComponentMask mask, uint64_t flags) { return HasAll(mask, flags); }
//
//constexpr ComponentMask mask_TAG_Player = 1ULL << Tag_Player::StaticTypeID;
//constexpr ComponentMask mask_TAG_Object = 1ULL << Tag_Object::StaticTypeID;
//constexpr ComponentMask mask_TAG_World = 1ULL << Tag_World::StaticTypeID;
//constexpr ComponentMask mask_TAG_Enemy = 1ULL << Tag_Enemy::StaticTypeID;
//constexpr ComponentMask mask_TAG_Projectile = 1ULL << Tag_Projectile::StaticTypeID;
//constexpr ComponentMask mask_TAG_Boulder = 1ULL << Tag_Boulder::StaticTypeID;
//constexpr ComponentMask mask_TAG_OliveTree = 1ULL << Tag_OliveTree::StaticTypeID;
//constexpr ComponentMask mask_TAG_HealingRock = 1ULL << Tag_HealingRock::StaticTypeID;
//
//constexpr ComponentMask allTags =
//mask_TAG_World
//| mask_TAG_Enemy
//| mask_TAG_Projectile
//| mask_TAG_Object
//| mask_TAG_Boulder
//| mask_TAG_OliveTree
//| mask_TAG_HealingRock;

bool CollisionSystem::Init(ECSManager* ecs)
{
	m_ECS = ecs;
	return false;
}
//// en haut du fichier CollisionSystem.cpp (includes si n馗essaire)
//#include <cstdint> // pour UINT32_MAX
//#include <cassert>

// helper minimal : calcule la position "monde" en remontant les parents
// Hypoth鑚e : on ne prend en compte QUE la translation (addition des positions).
static XMFLOAT3 GetWorldPosition(Entity e, ECSManager* ecs)
{
	XMFLOAT3 worldPos{ 0.f, 0.f, 0.f };

	TransformComponent* t = ecs->GetComponent<TransformComponent>(e);
	if (!t) return worldPos;

	// accumulateur : on additionne les positions locales en remontant les parents
	XMFLOAT3 accum = t->position;

	// remonter la cha絜e de parents
	Entity curParent = t->parent;
	// s馗urit・: limite de profondeur pour 騅iter boucle infinie
	const int MAX_PARENT_DEPTH = 64;
	int depth = 0;
	while (curParent.id != UINT32_MAX && depth < MAX_PARENT_DEPTH)
	{
		TransformComponent* tp = ecs->GetComponent<TransformComponent>(curParent);
		if (!tp) break;
		// On additionne simplement la translation du parent
		accum.x *= tp->scale.x;
		accum.y *= tp->scale.y;
		accum.z *= tp->scale.z;


		accum.x += tp->position.x /** tp->scale.x*/;
		accum.y += tp->position.y /** tp->scale.y*/; // ATTENTION
		accum.z += tp->position.z /** tp->scale.z*/;

		// passe au parent du parent
		curParent = tp->parent;
		++depth;
	}

	// si on a atteint la profondeur max, tu peux ajouter un assert/log si tu veux
	// assert(depth < MAX_PARENT_DEPTH && "Parent chain too deep or cyclic!");

	return accum;
}

void CollisionSystem::Update()
{
	// collecte entities avec Transform + Collision
	ComponentMask mask = (1ULL << Transform_ID) | (1ULL << Collision_ID);
	ComponentMask excludeMask = mask_TAG_Object | mask_TAG_World | mask_TAG_Boulder;
	std::vector<Entity> ents;
	m_ECS->ForEach(mask, excludeMask, [&](Entity e) { ents.push_back(e); });

	//std::unordered_map<ComponentMask, XMMATRIX> emptyMap;
	//const std::unordered_map<ComponentMask, XMMATRIX>& worldMatrices =
	//    (m_TransformSystem) ? m_TransformSystem->GetWorldMatrix() : emptyMap;

	//double globalStart = Utils::getTimeSeconds();
	//double sumPairs = 0.0;
	//std::vector<double> pairDurations;

	for (size_t i = 0; i < ents.size(); ++i) {
		for (size_t j = i + 1; j < ents.size(); ++j) {
			//double t0 = Utils::getTimeSeconds();
			TryPair(ents[i], ents[j]);
			//double t1 = Utils::getTimeSeconds();
			//double d = t1 - t0;
			//pairDurations.push_back(d);
			//sumPairs += d;
		}
	}
	//double globalEnd = Utils::getTimeSeconds();

	//// log hors boucle
	//for (auto d : pairDurations) {
	//    // si tu veux détailler, mais faire ça après la mesure
	//    Utils::log("Chrono : " + std::to_string(d) + "\n");
	//}
	//Utils::log("ChronoGLOBAL : " + std::to_string(globalEnd - globalStart)
	//    + " - sumPairs : " + std::to_string(sumPairs)
	//    + " - entsToTest : " + std::to_string(ents.size()) + "\n");
}

void CollisionSystem::TryPair(Entity a, Entity b/*, const std::unordered_map<uint32_t, XMMATRIX>& worldMatrices*/)
{
	ComponentMask mask_A = m_ECS->GetComponentMask(a);
	ComponentMask mask_B = m_ECS->GetComponentMask(b);


	if (!HasAny(mask_A, mask_TAG_Player | mask_TAG_Projectile | mask_TAG_Enemy | mask_TAG_OliveTree | mask_TAG_HealingRock)) return;
	if (!HasAny(mask_B, mask_TAG_Player | mask_TAG_Projectile | mask_TAG_Enemy | mask_TAG_OliveTree | mask_TAG_HealingRock)) return;


	if (Has(mask_A, mask_TAG_Player))
	{
		if (!HasAny(mask_B, mask_TAG_Projectile | mask_TAG_HealingRock))
			return;
	}
	else if (Has(mask_B, mask_TAG_Player))
	{
		if (!HasAny(mask_A, mask_TAG_Projectile | mask_TAG_HealingRock))
			return;
	}

	if (Has(mask_A, mask_TAG_Enemy))
	{
		if (!Has(mask_B, mask_TAG_Projectile))
			return;
	}
	else if (Has(mask_B, mask_TAG_Enemy))
	{
		if (!Has(mask_A, mask_TAG_Projectile))
			return;
	}

	if (Has(mask_A, mask_TAG_OliveTree))
	{
		if (!Has(mask_B, mask_TAG_Projectile))
			return;
	}
	else if (Has(mask_B, mask_TAG_OliveTree))
	{
		if (!Has(mask_A, mask_TAG_Projectile))
			return;
	}

	auto* ta = m_ECS->GetComponent<TransformComponent>(a);
	auto* tb = m_ECS->GetComponent<TransformComponent>(b);
	auto* ca = m_ECS->GetComponent<CollisionComponent>(a);
	auto* cb = m_ECS->GetComponent<CollisionComponent>(b);
	if (!ta || !tb || !ca || !cb) return;

	//XMMATRIX wa = XMMatrixIdentity(), wb = XMMatrixIdentity();
	//auto ita = worldMatrices.find(a.id);
	//if (ita != worldMatrices.end()) wa = ita->second;
	//else {
	//	// fallback: compose local (scale * rot * trans) - identique ・TransformSystem
	//	XMVECTOR pos = XMLoadFloat3(&ta->position);
	//	XMVECTOR rot = XMLoadFloat4(&ta->rotation);
	//	XMVECTOR scl = XMLoadFloat3(&ta->scale);
	//	wa = XMMatrixScalingFromVector(scl) * XMMatrixRotationQuaternion(rot) * XMMatrixTranslationFromVector(pos);
	//	if (ta->parent.id != UINT32_MAX) {
	//		// si parent pas dans worldMatrices, on laisse identity (vu comme approximation)
	//	}
	//}
	//auto itb = worldMatrices.find(b.id);
	//if (itb != worldMatrices.end()) wb = itb->second;
	//else {
	//	XMVECTOR pos = XMLoadFloat3(&tb->position);
	//	XMVECTOR rot = XMLoadFloat4(&tb->rotation);
	//	XMVECTOR scl = XMLoadFloat3(&tb->scale);
	//	wb = XMMatrixScalingFromVector(scl) * XMMatrixRotationQuaternion(rot) * XMMatrixTranslationFromVector(pos);
	//}

	//// extraire position monde (translation)
	//XMFLOAT3 pa, pb;
	//{
	//	XMVECTOR tA = wa.r[3];
	//	XMVECTOR tB = wb.r[3];
	//	XMStoreFloat3(&pa, tA);
	//	XMStoreFloat3(&pb, tB);
	//}

	//// extraire scale monde : longueur des axes de la matrice (rows)
	//XMFLOAT3 scaleA, scaleB;
	//{
	//	float sx, sy, sz;
	//	sx = XMVectorGetX(XMVector3Length(wa.r[0]));
	//	sy = XMVectorGetX(XMVector3Length(wa.r[1]));
	//	sz = XMVectorGetX(XMVector3Length(wa.r[2]));
	//	scaleA = { sx, sy, sz };

	//	sx = XMVectorGetX(XMVector3Length(wb.r[0]));
	//	sy = XMVectorGetX(XMVector3Length(wb.r[1]));
	//	sz = XMVectorGetX(XMVector3Length(wb.r[2]));
	//	scaleB = { sx, sy, sz };
	//}

	//// extraire rotation monde en quaternion (normaliser axes puis construire matrice rotation)
	//XMFLOAT4 rotA, rotB;
	//{
	//	// A
	//	XMVECTOR ax = wa.r[0], ay = wa.r[1], az = wa.r[2];
	//	float lx = XMVectorGetX(XMVector3Length(ax)); if (lx == 0.f) lx = 1.f;
	//	float ly = XMVectorGetX(XMVector3Length(ay)); if (ly == 0.f) ly = 1.f;
	//	float lz = XMVectorGetX(XMVector3Length(az)); if (lz == 0.f) lz = 1.f;
	//	XMVECTOR nx = ax / lx;
	//	XMVECTOR ny = ay / ly;
	//	XMVECTOR nz = az / lz;
	//	nx = XMVectorSetW(nx, 0.f); ny = XMVectorSetW(ny, 0.f); nz = XMVectorSetW(nz, 0.f);
	//	XMMATRIX rotMatA(nx, ny, nz, XMVectorSet(0, 0, 0, 1));
	//	XMVECTOR qA = XMQuaternionRotationMatrix(rotMatA);
	//	XMStoreFloat4(&rotA, qA);

	//	// B
	//	ax = wb.r[0]; ay = wb.r[1]; az = wb.r[2];
	//	lx = XMVectorGetX(XMVector3Length(ax)); if (lx == 0.f) lx = 1.f;
	//	ly = XMVectorGetX(XMVector3Length(ay)); if (ly == 0.f) ly = 1.f;
	//	lz = XMVectorGetX(XMVector3Length(az)); if (lz == 0.f) lz = 1.f;
	//	nx = ax / lx; ny = ay / ly; nz = az / lz;
	//	nx = XMVectorSetW(nx, 0.f); ny = XMVectorSetW(ny, 0.f); nz = XMVectorSetW(nz, 0.f);
	//	XMMATRIX rotMatB(nx, ny, nz, XMVectorSet(0, 0, 0, 1));
	//	XMVECTOR qB = XMQuaternionRotationMatrix(rotMatB);
	//	XMStoreFloat4(&rotB, qB);
	//}

	//XMFLOAT3 pa{ ta->position.x, ta->position.y, ta->position.z };
	//XMFLOAT3 pb{ tb->position.x, tb->position.y, tb->position.z };
	XMFLOAT3 pa = GetWorldPosition(a, m_ECS);
	XMFLOAT3 pb = GetWorldPosition(b, m_ECS);

	bool hit = false;

	/*if (ca->shapeType == ColliderType::Sphere && cb->shapeType == ColliderType::Sphere) {
		SphereCollider sa = std::get<SphereCollider>(ca->shape);
		SphereCollider sb = std::get<SphereCollider>(cb->shape);
		float sca = std::max({ fabs(scaleA.x), fabs(scaleA.y), fabs(scaleA.z) });
		float scb = std::max({ fabs(scaleB.x), fabs(scaleB.y), fabs(scaleB.z) });
		sa.radius *= sca;
		sb.radius *= scb;
		hit = SphereVsSphere(pa, sa, pb, sb);
	}
	else if (ca->shapeType == ColliderType::AABB && cb->shapeType == ColliderType::AABB) {
		AABBCollider aa = std::get<AABBCollider>(ca->shape);
		AABBCollider ab = std::get<AABBCollider>(cb->shape);
		aa.halfSize.x *= fabs(scaleA.x); aa.halfSize.y *= fabs(scaleA.y); aa.halfSize.z *= fabs(scaleA.z);
		ab.halfSize.x *= fabs(scaleB.x); ab.halfSize.y *= fabs(scaleB.y); ab.halfSize.z *= fabs(scaleB.z);
		hit = AabbVsAabb(pa, aa, pb, ab);
	}
	else if (ca->shapeType == ColliderType::Sphere && cb->shapeType == ColliderType::AABB) {
		SphereCollider sa = std::get<SphereCollider>(ca->shape);
		AABBCollider ab = std::get<AABBCollider>(cb->shape);
		float sca = std::max({ fabs(scaleA.x), fabs(scaleA.y), fabs(scaleA.z) });
		sa.radius *= sca;
		ab.halfSize.x *= fabs(scaleB.x); ab.halfSize.y *= fabs(scaleB.y); ab.halfSize.z *= fabs(scaleB.z);
		hit = SphereVsAabb(pa, sa, pb, ab);
	}
	else if (ca->shapeType == ColliderType::AABB && cb->shapeType == ColliderType::Sphere) {
		AABBCollider aa = std::get<AABBCollider>(ca->shape);
		SphereCollider sb = std::get<SphereCollider>(cb->shape);
		aa.halfSize.x *= fabs(scaleA.x); aa.halfSize.y *= fabs(scaleA.y); aa.halfSize.z *= fabs(scaleA.z);
		float scb = std::max({ fabs(scaleB.x), fabs(scaleB.y), fabs(scaleB.z) });
		sb.radius *= scb;
		hit = SphereVsAabb(pb, sb, pa, aa);
	}
	else if (ca->shapeType == ColliderType::OBB && cb->shapeType == ColliderType::OBB) {
		OBBCollider oa = std::get<OBBCollider>(ca->shape);
		OBBCollider ob = std::get<OBBCollider>(cb->shape);
		oa.orientation = rotA;
		ob.orientation = rotB;
		oa.halfSize.x *= fabs(scaleA.x); oa.halfSize.y *= fabs(scaleA.y); oa.halfSize.z *= fabs(scaleA.z);
		ob.halfSize.x *= fabs(scaleB.x); ob.halfSize.y *= fabs(scaleB.y); ob.halfSize.z *= fabs(scaleB.z);
		hit = ObbVsObb(pa, oa, pb, ob);
	}
	else if (ca->shapeType == ColliderType::Sphere && cb->shapeType == ColliderType::OBB) {
		SphereCollider sa = std::get<SphereCollider>(ca->shape);
		OBBCollider ob = std::get<OBBCollider>(cb->shape);
		float sca = std::max({ fabs(scaleA.x), fabs(scaleA.y), fabs(scaleA.z) });
		sa.radius *= sca;
		ob.orientation = rotB;
		ob.halfSize.x *= fabs(scaleB.x); ob.halfSize.y *= fabs(scaleB.y); ob.halfSize.z *= fabs(scaleB.z);
		hit = SphereVsObb(pa, sa, pb, ob);
	}
	else if (ca->shapeType == ColliderType::OBB && cb->shapeType == ColliderType::Sphere) {
		OBBCollider oa = std::get<OBBCollider>(ca->shape);
		SphereCollider sb = std::get<SphereCollider>(cb->shape);
		oa.orientation = rotA;
		oa.halfSize.x *= fabs(scaleA.x); oa.halfSize.y *= fabs(scaleA.y); oa.halfSize.z *= fabs(scaleA.z);
		float scb = std::max({ fabs(scaleB.x), fabs(scaleB.y), fabs(scaleB.z) });
		sb.radius *= scb;
		hit = SphereVsObb(pb, sb, pa, oa);
	}
	else if (ca->shapeType == ColliderType::AABB && cb->shapeType == ColliderType::OBB) {
		AABBCollider aa = std::get<AABBCollider>(ca->shape);
		OBBCollider ob = std::get<OBBCollider>(cb->shape);
		aa.halfSize.x *= fabs(scaleA.x); aa.halfSize.y *= fabs(scaleA.y); aa.halfSize.z *= fabs(scaleA.z);
		ob.orientation = rotB;
		ob.halfSize.x *= fabs(scaleB.x); ob.halfSize.y *= fabs(scaleB.y); ob.halfSize.z *= fabs(scaleB.z);
		hit = ObbVsAabb(pa, aa, pb, ob);
	}
	else if (ca->shapeType == ColliderType::OBB && cb->shapeType == ColliderType::AABB) {
		OBBCollider oa = std::get<OBBCollider>(ca->shape);
		AABBCollider ab = std::get<AABBCollider>(cb->shape);
		oa.orientation = rotA;
		oa.halfSize.x *= fabs(scaleA.x); oa.halfSize.y *= fabs(scaleA.y); oa.halfSize.z *= fabs(scaleA.z);
		ab.halfSize.x *= fabs(scaleB.x); ab.halfSize.y *= fabs(scaleB.y); ab.halfSize.z *= fabs(scaleB.z);
		hit = ObbVsAabb(pb, ab, pa, oa);
	}*/


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
		hit = ObbVsAabb(pa, std::get<AABBCollider>(ca->shape), pb,
			std::get<OBBCollider>(cb->shape));
	}
	else if (ca->shapeType == ColliderType::OBB && cb->shapeType == ColliderType::AABB) {
		std::get<OBBCollider>(ca->shape).orientation = ta->rotation;
		hit = ObbVsAabb(pb, std::get<AABBCollider>(cb->shape), pa,
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
bool CollisionSystem::ObbVsObb(XMFLOAT3 p1, OBBCollider b1, XMFLOAT3 p2, OBBCollider b2)
{

	// 3 axes locaux de chaque bo羡e
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

	// vecteur distance projet・sur A[]
	XMVECTOR tvec = C2 - C1;
	float t[3] = {
		XMVectorGetX(XMVector3Dot(tvec, A[0])),
		XMVectorGetX(XMVector3Dot(tvec, A[1])),
		XMVectorGetX(XMVector3Dot(tvec, A[2]))
	};

	// 1・ : axes A0, A1, A2
	for (int i = 0; i < 3; ++i) {
		float ra = (&b1.halfSize.x)[i];
		float rb = b2.halfSize.x * AbsR[i][0]
			+ b2.halfSize.y * AbsR[i][1]
			+ b2.halfSize.z * AbsR[i][2];
		if (std::abs(t[i]) > ra + rb) return false;
	}
	// 4・ : axes B0, B1, B2
	for (int j = 0; j < 3; ++j) {
		float ra = b1.halfSize.x * AbsR[0][j]
			+ b1.halfSize.y * AbsR[1][j]
			+ b1.halfSize.z * AbsR[2][j];
		float tj = std::abs(XMVectorGetX(XMVector3Dot(tvec, B[j])));
		float rb = (&b2.halfSize.x)[j];
		if (tj > ra + rb) return false;
	}
	// 7・5 : A_i ﾗ B_j
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
// 4) Sphere vs OBB (on ram鈩e le centre sph鑽e en espace local OBB)
bool CollisionSystem::SphereVsObb(XMFLOAT3 ps, SphereCollider s,
	XMFLOAT3 p, OBBCollider b)
{
	// centre sph鑽e en monde
	XMVECTOR C = XMLoadFloat3(&ps) + XMLoadFloat3(&s.offset);
	// inverser la rotation de l'OBB
	XMVECTOR invQ = XMQuaternionInverse(XMLoadFloat4(&b.orientation));

	//// GARDER OU ENLEVER ?
	//XMVECTOR qb = XMLoadFloat4(&b.orientation);
	//qb = XMQuaternionNormalize(qb);
	//XMVECTOR invQ = XMQuaternionInverse(qb);

	// centre sph鑽e en espace local OBB
	XMVECTOR localC = XMVector3Rotate(C - XMLoadFloat3(&p), invQ);
	XMFLOAT3 lc;
	XMStoreFloat3(&lc, localC);

	// clamp sur la bo羡e align馥 aux axes
	float cx = std::max(-b.halfSize.x, std::min(lc.x, b.halfSize.x));
	float cy = std::max(-b.halfSize.y, std::min(lc.y, b.halfSize.y));
	float cz = std::max(-b.halfSize.z, std::min(lc.z, b.halfSize.z));

	float dx = lc.x - cx, dy = lc.y - cy, dz = lc.z - cz;
	return dx * dx + dy * dy + dz * dz <= s.radius * s.radius;
}

// 5) OBB vs AABB (on applique SAT en traitant l但ABB comme OBB non orient馥)
bool CollisionSystem::ObbVsAabb(XMFLOAT3 paabb, AABBCollider a,
	XMFLOAT3 pobb, OBBCollider b)
{
	// transformer l但ABB en OBB : orientation = identity, offset = a.offset
	OBBCollider boxA;
	boxA.halfSize = a.halfSize;
	boxA.offset = a.offset;
	boxA.orientation = { 0, 0, 0, 1 };
	// et appeler directement ObbVsObb avec centres 馗hang駸 si besoin
	return ObbVsObb(pobb, b, paabb, boxA);
}
