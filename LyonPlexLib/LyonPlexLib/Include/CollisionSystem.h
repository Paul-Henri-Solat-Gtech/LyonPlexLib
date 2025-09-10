// CollisionSystem.h
#pragma once
#include "Components.h"
#include "EventBus.h"
#include "Events.h"
#include "TransformSystem.h"

class ECSManager;

class CollisionSystem {
public:
    //CollisionSystem();
    bool Init(ECSManager* ecs);
    void SetTransformSystem(TransformSystem* ts) { m_TransformSystem = ts; }
    void Update();
private:
    ECSManager* m_ECS;
    TransformSystem* m_TransformSystem = nullptr;

    void TryPair(Entity a, Entity b/*, const std::unordered_map<uint32_t, XMMATRIX>& worldMatrices*/);

    bool SphereVsSphere(XMFLOAT3 p1, SphereCollider c1, XMFLOAT3 p2, SphereCollider c2);
    

    bool AabbVsAabb(XMFLOAT3 p1, AABBCollider b1, XMFLOAT3 p2, AABBCollider b2);
    

    bool SphereVsAabb(XMFLOAT3 pc, SphereCollider s, XMFLOAT3 pa, AABBCollider a);

    bool ObbVsObb(XMFLOAT3 p1, OBBCollider b1, XMFLOAT3 p2, OBBCollider b2);

    bool SphereVsObb(XMFLOAT3 ps, SphereCollider s, XMFLOAT3 p, OBBCollider b);

    bool ObbVsAabb(XMFLOAT3 paabb, AABBCollider a, XMFLOAT3 pobb, OBBCollider b);
    
};