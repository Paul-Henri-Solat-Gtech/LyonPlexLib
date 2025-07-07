// Collider.h
#pragma once
#include <DirectXMath.h>
using namespace DirectX;

enum class ColliderType {
    Sphere,
    AABB,
    OBB
};

struct SphereCollider {
    float    radius;
    XMFLOAT3 offset = { 0,0,0 };
};

struct AABBCollider {
    XMFLOAT3 halfSize;    // demi largeur, demi hauteur, demi profondeur
    XMFLOAT3 offset = { 0,0,0 };
};

struct OBBCollider {
    XMFLOAT3 halfSize;
    XMFLOAT3 offset = { 0,0,0 };
    XMFLOAT4 rotationQuat; // quaternion de l’orientation
};
