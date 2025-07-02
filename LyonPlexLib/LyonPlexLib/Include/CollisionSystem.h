//// CollisionSystem.h
//#pragma once
//#include "EventBus.h"
//#include "ISystem.h"
////#include "Components.h"
//
//class CollisionSystem : public ISystem {
//public:
//    CollisionSystem(EventBus& bus, ECSManager& m_ecs) : m_bus(bus), m_ecs(ecs) {}
//    void Update(ECSManager& ecs, float dt) override;
//private:
//    EventBus& m_bus;
//    //ECSManager& m_ecs;
//};





// CollisionSystem.h
#pragma once
#include "Components.h"
#include "EventBus.h"
#include "Events.h"

class ECSManager;

class CollisionSystem {
public:
    CollisionSystem(ECSManager* ecs) : mECS(ecs) {}
    void Update();
private:
    ECSManager* mECS;

    void TryPair(Entity a, Entity b);

    bool SphereVsSphere(XMFLOAT3 p1, SphereCollider c1, XMFLOAT3 p2, SphereCollider c2);
    

    bool AabbVsAabb(XMFLOAT3 p1, AABBCollider b1, XMFLOAT3 p2, AABBCollider b2);
    

    bool SphereVsAabb(XMFLOAT3 pc, SphereCollider s, XMFLOAT3 pa, AABBCollider a);
    
};