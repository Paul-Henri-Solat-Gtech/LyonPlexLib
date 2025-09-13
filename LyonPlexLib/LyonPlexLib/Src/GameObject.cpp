#include "GameObject.h"
#include "GameObject.h"
#include "GameObject.h"
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
	//AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::NOTEXTURE));
	AddComponent<MeshComponent>(new MeshComponent((MESHES::LOCAL_CUBE)));
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
	AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE));

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
}
void GameObject::InitOliveTreeGameObj(ECSManager* ecsManager, Scene* scene)
{
	static int treeCount = 1;
	std::string name = "OliveTree" + std::to_string(treeCount++);
	Utils::log("\nOlive tree created : " + name + "\n");
	SetName(name);
	SetTag(TAG_Environment);
	mp_ecsManager = ecsManager;
	mp_scene = scene;
	m_entity = mp_ecsManager->CreateEntity();

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());

	// Tag monde (collisions)
	AddComponent<Tag_World>(new Tag_World);
}
void GameObject::InitPlayerGameObj(ECSManager* ecsManager, Scene* scene)
{
	SetName("Player");
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	mp_scene = scene;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// TYPE
	AddComponent<Type_3D>(new Type_3D());

	// MESH
	AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE));

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

	// Tag monde (collisions)
	AddComponent<Tag_World>(new Tag_World);
}
void GameObject::InitWater(ECSManager* ecsManager, Scene* scene, int waterNum)
{
	SetName("");
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	mp_scene = scene;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// TYPE
	AddComponent<WaveComponent>(new WaveComponent(waterNum));

	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());
}
void GameObject::InitHitbox(const std::string& name, ECSManager* ecsManager, Scene* scene)
{
	SetName(name);
	SetTag(TAG_Environment);
	mp_ecsManager = ecsManager;
	mp_scene = scene;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// TYPE
	//AddComponent<Type_3D>(new Type_3D());
	AddComponent<Type_3D_Transparent>(new Type_3D_Transparent());

	// MESH
	//AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::GRID));
	//AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::TEMPLE));
	//GetComponent<MeshComponent>()->alpha = 0.5;
	
	//	TRANSFORM
	AddComponent<TransformComponent>(new TransformComponent());

	// Tag monde (collisions)
	AddComponent<Tag_World>(new Tag_World);
}
void GameObject::InitWater(const std::string& gameObjectName, ECSManager* ecsManager, Scene* scene, int waterNum)
{
	SetName(gameObjectName);
	SetTag(TAG_None);
	mp_ecsManager = ecsManager;
	mp_scene = scene;
	m_entity = mp_ecsManager->CreateEntity();

	//	Adding basics component(s) for any entity in scene & default parameters :

	// TYPE
	//AddComponent<Type_3D>(new Type_3D());
	AddComponent<WaveComponent>(new WaveComponent(waterNum));
	//AddComponent<WaveComponent>(new WaveComponent(TEXTURES::WATER_NORMAL, TEXTURES::CUBE_MAP));

	// MESH
	//AddComponent<MeshComponent>(new MeshComponent(meshId, textureId));

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

void GameObject::LookAt(GameObject gmToLookAt)
{
	LookAt(gmToLookAt.GetPosition());
}
void GameObject::LookAt(XMFLOAT3 posToLookAt)
{
	// Récupère positions
	XMFLOAT3 eyePos = GetPosition();
	XMFLOAT3 targetPos = posToLookAt;

	// Direction projetée sur XZ
	float dx = targetPos.x - eyePos.x;
	float dz = targetPos.z - eyePos.z;

	// Si la cible est quasiment au même endroit horizontalement, on ne change pas l'orientation
	if (fabsf(dx) < 1e-6f && fabsf(dz) < 1e-6f)
		return;

	// Calcul du yaw (rotation autour de Y)
	// note: atan2f(dx, dz) => angle depuis +Z vers le vecteur (dx, dz)
	float yaw = atan2f(dx, dz);

	// Crée un quaternion pour une rotation autour de l'axe Y
	XMVECTOR axis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR quatVec = XMQuaternionRotationAxis(axis, yaw);

	// Stocke en XMFLOAT4 et applique
	XMFLOAT4 quat;
	XMStoreFloat4(&quat, quatVec);
	SetRotation(quat);
}

void GameObject::MoveForward(float distance)
{
	// 1) Récupère la rotation courante (quaternion)
	XMFLOAT4 rot = GetRotation();
	XMVECTOR quat = XMLoadFloat4(&rot);

	// 2) Forward local = (0,0,1)
	XMVECTOR localForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	// 3) Rotate ce forward par le quaternion -> vecteur direction global
	XMVECTOR worldForward = XMVector3Rotate(localForward, quat);

	// 4) Charge en composantes flotantes
	XMFLOAT3 dir;
	XMStoreFloat3(&dir, worldForward);

	// 5) Mets à jour la position
	XMFLOAT3 pos = GetPosition();
	pos.x += dir.x * distance;
	pos.y += dir.y * distance;   // si tu veux rester au sol, ignore pos.y
	pos.z += dir.z * distance;
	SetPosition(pos);
}

void GameObject::MoveBackward(float distance)
{
	// 1) Récupère la rotation courante (quaternion)
	XMFLOAT4 rot = GetRotation();
	XMVECTOR quat = XMLoadFloat4(&rot);

	// 2) Forward local = (0,0,1)
	XMVECTOR localForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	// 3) Rotate ce forward par le quaternion -> vecteur direction global
	XMVECTOR worldForward = XMVector3Rotate(localForward, quat);

	// 4) Charge en composantes flotantes
	XMFLOAT3 dir;
	XMStoreFloat3(&dir, worldForward);

	// 5) Mets à jour la position
	XMFLOAT3 pos = GetPosition();
	pos.x -= dir.x * distance;
	pos.y -= dir.y * distance;   // si tu veux rester au sol, ignore pos.y
	pos.z -= dir.z * distance;
	SetPosition(pos);
}

void GameObject::MoveInDirection(const XMFLOAT3& direction, float distance)
{
	// charge la direction
	XMVECTOR dirV = XMLoadFloat3(&direction);

	// sécurité : vecteur nul ?
	XMVECTOR lenV = XMVector3Length(dirV);
	float len = XMVectorGetX(lenV);
	if (len < 1e-6f) return; // pas de mouvement si direction nulle

	// Ignorer deplacement en Y
	dirV = XMVectorSetY(dirV, 0.0f);
	if (XMVectorGetX(XMVector3Length(dirV)) < 1e-6f) return;

	// normalise
	XMVECTOR dirNorm = XMVector3Normalize(dirV);

	// si tu veux rester au sol -> ignore la composante Y avant normalisation :
	// dirV = XMVectorSetY(dirV, 0.0f);
	// if (XMVectorGetX(XMVector3Length(dirV)) < 1e-6f) return;
	// dirNorm = XMVector3Normalize(dirV);

	// position courante
	XMFLOAT3 pos = GetPosition();
	XMVECTOR posV = XMLoadFloat3(&pos);

	// nouvelle position = pos + dirNorm * distance
	posV = XMVectorAdd(posV, XMVectorScale(dirNorm, distance));
	XMStoreFloat3(&pos, posV);
	SetPosition(pos);
}

XMVECTOR GameObject::MoveInDirection_NextPos(const XMFLOAT3& direction, float distance)
{
	// charge la direction
	XMVECTOR dirV = XMLoadFloat3(&direction);

	// sécurité : vecteur nul ?
	XMVECTOR lenV = XMVector3Length(dirV);
	float len = XMVectorGetX(lenV);
	if (len < 1e-6f) return { 0,0,0 }; // pas de mouvement si direction nulle

	// Ignorer deplacement en Y
	dirV = XMVectorSetY(dirV, 0.0f);
	if (XMVectorGetX(XMVector3Length(dirV)) < 1e-6f) return{ 0,0,0 };

	// normalise
	XMVECTOR dirNorm = XMVector3Normalize(dirV);

	// si tu veux rester au sol -> ignore la composante Y avant normalisation :
	// dirV = XMVectorSetY(dirV, 0.0f);
	// if (XMVectorGetX(XMVector3Length(dirV)) < 1e-6f) return;
	// dirNorm = XMVector3Normalize(dirV);

	// position courante
	XMFLOAT3 pos = GetPosition();
	XMVECTOR lastPosV = XMLoadFloat3(&pos);
	XMVECTOR newPosV = XMLoadFloat3(&pos);

	// nouvelle position = pos + dirNorm * distance
	newPosV = XMVectorAdd(newPosV, XMVectorScale(dirNorm, distance));
	XMVECTOR dist = newPosV - lastPosV;
	return  newPosV;
}
