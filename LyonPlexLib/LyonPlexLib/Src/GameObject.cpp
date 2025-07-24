#include "pch.h"
#include "GameObject.h"

void GameObject::Init(const std::string& name, ECSManager* ecsManager, Scene* scene)
{
	SetName(name);
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	mp_scene = scene;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// TYPE
	AddComponent<Type_3D>(new Type_3D());

	// MESH
	AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::NOTEXTURE));

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
}
void GameObject::InitGameObj(ECSManager* ecsManager, Scene* scene)
{
	SetName("");
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	mp_scene = scene;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// TYPE
	AddComponent<Type_3D>(new Type_3D());

	// MESH
	AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::NOTEXTURE));

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
}
void GameObject::Init(const std::string& name, ECSManager* ecsManager, Scene* scene, uint32_t meshId, uint32_t textureId)
{
	SetName(name);
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	mp_scene = scene;
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
void GameObject::Init(const std::string& name, ECSManager* ecsManager, Scene* scene, DimensionalType type, bool useMesh)
{
	SetName(name);
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	mp_scene = scene;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// TYPE
	if (type == TYPE_3D)
		AddComponent<Type_3D>(new Type_3D());
	if (type == TYPE_2D)
		AddComponent<Type_2D>(new Type_2D()); 
	if (type == TYPE_3D_TRANSPARENT)
		AddComponent<Type_3D_Transparent>(new Type_3D_Transparent());

	// MESH
	AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::NOTEXTURE));

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
}

void GameObject::Init(ECSManager* ecsManager, Scene* scene)
{
	SetName("");
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	mp_scene = scene;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// MESH
	AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::NOTEXTURE));

	// TYPE
	AddComponent<Type_3D>(new Type_3D());

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
}
