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
	AddComponent<Type_3D>(new Type_3D());

	// MESH
	AddComponent<MeshComponent>(new MeshComponent(2, 0));

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
	GetComponent<TransformComponent>()->position = { 0, 0, 0 };
}
void GameObject::Init(const std::string& name, ECSManager* ecsManager, DimensionalType type)
{
	SetName(name);
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// MESH
	AddComponent<MeshComponent>(new MeshComponent(2, 0));

	// TYPE
	if (type == TYPE_3D)
	{
		AddComponent<Type_3D>(new Type_3D());
	}
	if (type == TYPE_2D)
	{
		AddComponent<Type_2D>(new Type_2D());
	}
	else
	{
		AddComponent<Type_3D>(new Type_3D());
	}

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
	GetComponent<TransformComponent>()->position = { 0, 0, 0 };
}
