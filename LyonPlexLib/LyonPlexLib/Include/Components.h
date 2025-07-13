#pragma once

#include "Colliders.h"
#include <variant>

using ComponentMask = uint64_t; // assume up to 64 component types


enum ComponentID
{
	// Comopnents
	Transform_ID,
	Camera_ID,
	Mesh_ID,
	Texture_ID,
	Collision_ID,
	Light_ID,


	// Types (3D, 2D, UI)
	Type_3D_ID,
	Type_3D_Transparent_ID,
	Type_2D5_ID,
	Type_2D_ID,
	Type_UI_ID,

	Tag_Player_ID,
	Tag_Enemy_ID,
	Tag_Object_ID,

	TotalComponentsCount
};


struct Component {
	virtual ~Component() = default;
	ComponentMask mask;
	uint32_t typeID;
};


struct TransformComponent : public Component {
	static constexpr uint32_t StaticTypeID = Transform_ID;

	XMFLOAT3 position = { 0.0f, 0.0f, 0.0f };
	XMFLOAT4 rotation = { 0.0f, 0.0f, 0.0f, 1.0f }; // quaternion
	XMFLOAT3 scale = { 1.0f, 1.0f, 1.0f };

	Entity    parent = { UINT32_MAX };
	bool      dirty = true;

	TransformComponent() {
		mask = 1ULL << StaticTypeID;
		typeID = StaticTypeID;
	}

	inline void AddRotation(float deltaPitchDeg, float deltaYawDeg, float deltaRollDeg)
	{
		// 1) Convertir l'increment d'angles en radians
		float p = XMConvertToRadians(deltaPitchDeg);
		float y = XMConvertToRadians(deltaYawDeg);
		float r = XMConvertToRadians(deltaRollDeg);

		// 2) Construire le quaternion de l'increment de rotation
		//    (equivalent a "tourner p autour de X, puis y autour de Y, puis r autour de Z")
		XMVECTOR incQv = XMQuaternionRotationRollPitchYaw(p, y, r);

		// 3) Charger le quaternion actuel (x,y,z,w) dans un XMVECTOR
		XMVECTOR curQv = XMLoadFloat4(&rotation);

		// 4) Composer les deux quaternions : newQ = incQ * curQ
		//    (l'ordre importe : ici on applique incQ **avant** la rotation actuelle,
		//     ce qui correspond a un repere local).
		XMVECTOR newQv = XMQuaternionMultiply(incQv, curQv);

		// 5) Normaliser (eviter la derive numerique)
		newQv = XMQuaternionNormalize(newQv);

		// 6) Stocker de retour dans le composant
		XMStoreFloat4(&rotation, newQv);

		// 7) Marquer comme dirty pour que le TransformSystem recalcule la matrice monde
		dirty = true;
	}

	inline void SetRotation(float pitchDeg, float yawDeg, float rollDeg)
	{
		float p = XMConvertToRadians(pitchDeg);
		float y = XMConvertToRadians(yawDeg);
		float r = XMConvertToRadians(rollDeg);
		XMVECTOR qv = XMQuaternionRotationRollPitchYaw(p, y, r);
		XMStoreFloat4(&rotation, qv);
		dirty = true;
	}
};

// Contient tout ce dont le CameraSystem a besoin pour calculer la view/proj.
struct CameraComponent : public Component {
	static constexpr uint32_t StaticTypeID = Camera_ID; // Choisissez un ID libre (> 3 dans votre exemple)

	// Position et vecteurs de base
	XMFLOAT3 position = { 0.0f, 0.0f, -1.0f }; // camera placee 1 unites en -Z
	XMFLOAT3 forward = { 0.0f, 0.0f,  1.0f };
	XMFLOAT3 up = { 0.0f, 1.0f,  0.0f };
	XMFLOAT3 right = { 1.0f, 0.0f,  0.0f };

	// Matrices stockees en float4x4 (transpose si HLSL attend column‐major)
	XMFLOAT4X4 viewMatrix = {};
	XMFLOAT4X4 projectionMatrix = {};

	// Parametres de projection
	float fovDegrees = 90.0f;
	float aspectRatio = 16.0f / 9.0f;
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;

	// Flag “dirty” si position/orientation/projection a change
	bool viewDirty = true;
	bool projectionDirty = true;

	// Vitesse et sensibilite souris
	float cameraSpeed = 0.2f;
	float mouseSensitivity = 0.005f;
	bool  rotating = false;

	// Pour stocker la position precedente de la souris
	POINT prevMousePos = { 0, 0 };

	CameraComponent() {
		mask = (1ULL << StaticTypeID);
		typeID = StaticTypeID;
	}
};


struct MeshComponent : public Component
{
	static constexpr uint32_t StaticTypeID = Mesh_ID;
	uint32_t meshID;
	uint32_t materialID;
	float alpha = 1;

	MeshComponent(uint32_t meshID_, uint32_t materialID_ = UINT32_MAX)
	{
		mask = 1ULL << StaticTypeID;
		typeID = StaticTypeID;
		meshID = meshID_;
		materialID = materialID_;
	}
};


struct CollisionComponent : public Component
{
	static constexpr uint32_t StaticTypeID = Collision_ID;

	ColliderType shapeType;
	std::variant<SphereCollider, AABBCollider, OBBCollider> shape;

	static CollisionComponent MakeSphere(float radius, XMFLOAT3 offset = { 0,0,0 })
	{
		CollisionComponent c;
		c.shapeType = ColliderType::Sphere;
		c.shape = SphereCollider{ radius, offset };
		return c;
	}
	static CollisionComponent MakeAABB(XMFLOAT3 halfSize, XMFLOAT3 offset = { 0,0,0 })
	{
		CollisionComponent c;
		c.shapeType = ColliderType::AABB;
		c.shape = AABBCollider{ halfSize, offset };
		return c;
	}
	// etc...

	CollisionComponent()
	{
		mask = 1ULL << StaticTypeID;
		typeID = StaticTypeID;
	}
};


struct LightComponent : public Component
{
	static constexpr uint32_t StaticTypeID = Light_ID;


	DirectX::XMFLOAT3		color = { 1,1,1 };
	float					intensity = 1.0f;

	// Directional light only : //
	DirectX::XMFLOAT3		direction = { 0,-1,0 };

	// Point light only :		//
	DirectX::XMFLOAT3		position = { 0,0,0 };
	float					range = 10.0f;

	enum Type : uint32_t { Directional = 0, Point = 1 } type = Directional;

	LightComponent(uint32_t _type)
	{
		mask = 1ULL << StaticTypeID;
		typeID = StaticTypeID;

		(_type == 0) ? type = Type::Directional : type = Type::Point;
	}
};












struct Type_3D : public Component
{
	static constexpr uint32_t StaticTypeID = Type_3D_ID;

	Type_3D()
	{
		mask = 1ULL << StaticTypeID;
		typeID = StaticTypeID;
	}
};

struct Type_3D_Transparent : public Component
{
	static constexpr uint32_t StaticTypeID = Type_3D_Transparent_ID;

	Type_3D_Transparent()
	{
		mask = 1ULL << StaticTypeID;
		typeID = StaticTypeID;
	}
};

struct Type_2D5 : public Component
{
	static constexpr uint32_t StaticTypeID = Type_2D5_ID;
	Type_2D5() {
		mask = 1ULL << StaticTypeID;
		typeID = StaticTypeID;
	}
};

struct Type_2D : public Component
{
	static constexpr uint32_t StaticTypeID = Type_2D_ID;

	Type_2D()
	{
		mask = 1ULL << StaticTypeID;
		typeID = StaticTypeID;
	}
};


struct Tag_Player : public Component
{
	static constexpr uint32_t StaticTypeID = Tag_Player_ID;

	Tag_Player()
	{
		mask = 1ULL << StaticTypeID;
		typeID = StaticTypeID;
	}
};


struct Tag_Enemy : public Component
{
	static constexpr uint32_t StaticTypeID = Tag_Enemy_ID;

	Tag_Enemy()
	{
		mask = 1ULL << StaticTypeID;
		typeID = StaticTypeID;
	}
};


struct Tag_Object : public Component
{
	static constexpr uint32_t StaticTypeID = Tag_Object_ID;

	Tag_Object()
	{
		mask = 1ULL << StaticTypeID;
		typeID = StaticTypeID;
	}
};


