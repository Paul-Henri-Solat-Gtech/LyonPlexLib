#include "pch.h"
#include "CollisionSystem.h"
#include "ECSManager.h"

#undef max
#undef min

//#include "CollisionSystem.h"
//
////#include "Components.h"
//
//void CollisionSystem::Update(ECSManager& ecs, float dt)
//{
//    // recuperer les entites avec CollisionComponent et TransformComponent
//    ComponentMask mask = (1ULL << CollisionComponent::StaticTypeID)
//        | (1ULL << TransformComponent::StaticTypeID);
//    ecs.ForEach(mask, [&](Entity a) {
//        auto* ca = ecs.GetComponent<CollisionComponent>(a);
//        auto* ta = ecs.GetComponent<TransformComponent>(a);
//        // ensuite boucle imbriquee sur b > a pour ne pas repasser deux fois
//        ecs.ForEach(mask, [&](Entity b) {
//            if (b.id <= a.id) return;
//            auto* cb = ecs.GetComponent<CollisionComponent>(b);
//            auto* tb = ecs.GetComponent<TransformComponent>(b);
//            // simple sphere?sphere
//            float dist2 = XMVectorGetX(XMVector3LengthSq(XMLoadFloat3(&ta->position)
//                - XMLoadFloat3(&tb->position)));
//            float rsum2 = (ca->radius + cb->radius) * (ca->radius + cb->radius);
//            if (dist2 <= rsum2) {
//                // on publie l’evenement
//                CollisionEvent::Payload p{ a, b };
//                _bus.publish<CollisionEvent>(p);
//            }
//            });
//        });
//}
//
//
//bool CollisionSystem::IntersectAABB(CollisionComponent const& A, CollisionComponent const& B)
//{
//    return
//        std::abs(A.center.x - B.center.x) <= (A.halfSize.x + B.halfSize.x) &&
//        std::abs(A.center.y - B.center.y) <= (A.halfSize.y + B.halfSize.y) &&
//        std::abs(A.center.z - B.center.z) <= (A.halfSize.z + B.halfSize.z);
//}

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
    // plus tard : OBB…

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