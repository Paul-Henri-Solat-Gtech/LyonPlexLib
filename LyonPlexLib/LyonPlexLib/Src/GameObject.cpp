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
	AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::NOTEXTURE));

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
	//GetComponent<TransformComponent>()->position = { 0, 0, 0 };
	//GetComponent<TransformComponent>()->dirty = true;
}
void GameObject::InitGameObj(ECSManager* ecsManager/*, std::vector<std::unique_ptr<GameObject>>& sceneGameObjects*/)
{
	SetName("");
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// TYPE
	AddComponent<Type_3D>(new Type_3D());

	// MESH
	AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::NOTEXTURE));

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
	//GetComponent<TransformComponent>()->position = { 0, 0, 0 };
	//GetComponent<TransformComponent>()->dirty = true;
	//sceneGameObjects.push_back(std::make_unique<GameObject>(*this));
}
void GameObject::Init(const std::string& name, ECSManager* ecsManager, uint32_t meshId, uint32_t textureId)
{
	SetName(name);
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// TYPE
	AddComponent<Type_3D>(new Type_3D());

	// MESH
	AddComponent<MeshComponent>(new MeshComponent(meshId, textureId));

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
	//GetComponent<TransformComponent>()->position = { 0, 0, 0 };
	//GetComponent<TransformComponent>()->dirty = true;
}
void GameObject::Init(const std::string& name, ECSManager* ecsManager,/* std::vector<std::unique_ptr<GameObject>>& sceneGameObjects,*/ DimensionalType type, bool useMesh)
{
	SetName(name);
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// TYPE
	if (type == TYPE_3D)
		AddComponent<Type_3D>(new Type_3D());
	if (type == TYPE_2D)
		AddComponent<Type_2D>(new Type_2D());

	// MESH
	AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::NOTEXTURE));

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
	//GetComponent<TransformComponent>()->position = { 0, 0, 0 };
	//GetComponent<TransformComponent>()->dirty = true;
	//sceneGameObjects.push_back(*this);
}
//void GameObject::Init(const std::string& name, ECSManager* ecsManager, DimensionalType type, bool useMesh)
//{
//	SetName(name);
//	SetTag(TAG_None);
//	mp_ecsManager = ecsManager;
//	m_entity = mp_ecsManager->CreateEntity();
//
//	//	Adding basics component(s) for any entity in scene & default parameters :
//
//	// MESH
//	if (useMesh) 
//	{
//		AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::GRID));
//	}
//
//	// TYPE
//	if (type == TYPE_2D)
//	{
//		AddComponent<Type_2D>(new Type_2D());
//	}
//	else
//	{
//		AddComponent<Type_3D>(new Type_3D());
//	}
//
//	//	TRANSFORM
//	AddComponent<TransformComponent>(new TransformComponent());
//	//GetComponent<TransformComponent>()->position = { 0, 0, 0 };
//	//GetComponent<TransformComponent>()->dirty = true;
//}

void GameObject::Init(ECSManager* ecsManager)
{
	SetName("");
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// MESH
	AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::NOTEXTURE));

	// TYPE
	AddComponent<Type_3D>(new Type_3D());

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
	//GetComponent<TransformComponent>()->position = { 0, 0, 0 };
	//GetComponent<TransformComponent>()->dirty = true;
}
