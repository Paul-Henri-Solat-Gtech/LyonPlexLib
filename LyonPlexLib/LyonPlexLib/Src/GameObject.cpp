#include "pch.h"
#include "GameObject.h"

void GameObject::Init(const std::string& name, ECSManager* ecsManager)
{
	SetName(name);
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :
	
	// TYPE
	AddComponent<Type_3D_LOC>(new Type_3D_LOC());

	// MESH
	AddComponent<MeshComponent>(new MeshComponent(2, 4));

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
	GetComponent<TransformComponent>()->position = { 0, 0, 0 };
	GetComponent<TransformComponent>()->dirty = true;
}
void GameObject::Init(const std::string& name, ECSManager* ecsManager, uint32_t meshId, uint32_t textureId)
{
	SetName(name);
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// TYPE
	AddComponent<Type_3D_LOC>(new Type_3D_LOC());

	// MESH
	AddComponent<MeshComponent>(new MeshComponent(meshId, textureId));

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
	GetComponent<TransformComponent>()->position = { 0, 0, 0 };
	GetComponent<TransformComponent>()->dirty = true;
}
void GameObject::Init(const std::string& name, ECSManager* ecsManager, DimensionalType type, bool useMesh)
{
	SetName(name);
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// MESH
	if (useMesh) 
	{
		AddComponent<MeshComponent>(new MeshComponent(2, 4));
	}

	// TYPE
	if (type == TYPE_2D)
	{
		AddComponent<Type_2D>(new Type_2D());
	}
	else
	{
		AddComponent<Type_3D_LOC>(new Type_3D_LOC());
	}

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
	GetComponent<TransformComponent>()->position = { 0, 0, 0 };
	GetComponent<TransformComponent>()->dirty = true;
}
