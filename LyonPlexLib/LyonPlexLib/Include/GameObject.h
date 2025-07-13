#pragma once

enum DimensionalType 
{
	TYPE_3D,
	TYPE_2D,

	TypeCount
};

enum Tag
{
	TAG_None,
	TAG_Enemy,
	TAG_Player,
	TAG_Object,
	TAG_Camera,
	TAG_Button,

	TAG_Floor,
	TAG_Environment,
	TAG_Stick,
	TAG_Rock,

	TagCount
};

class GameObject
{
public:
	void Init(const std::string& name, ECSManager* ecsManager);
	void Init(const std::string& name, ECSManager* ecsManager, uint32_t meshId, uint32_t textureId);
	void Init(const std::string& name, ECSManager* ecsManager, DimensionalType type, bool useMesh);

	void SetName(const std::string& name) { m_name = name; };
	const std::string& GetName() { return m_name; };
	void SetTag(Tag tag) { m_tag = tag; };
	Tag GetTag() { return m_tag; };

	// Components
	void SetPosition(XMFLOAT3 pos) { GetComponent<TransformComponent>()->position = pos; GetComponent<TransformComponent>()->dirty = true; };
	XMFLOAT3& GetPosition() { return GetComponent<TransformComponent>()->position; };
	void SetRotation(XMFLOAT4 rot) { GetComponent<TransformComponent>()->rotation = rot; GetComponent<TransformComponent>()->dirty = true;};
	XMFLOAT4& GetRotation() { return GetComponent<TransformComponent>()->rotation; };
	void SetScale(XMFLOAT3 scl) { GetComponent<TransformComponent>()->scale = scl; GetComponent<TransformComponent>()->dirty = true;};
	XMFLOAT3& GetScale() { return GetComponent<TransformComponent>()->scale; };
	void SetTexture(uint32_t textureId) { GetComponent<MeshComponent>()->materialID = textureId; };
	uint32_t& GetTexture() { return GetComponent<MeshComponent>()->materialID; };
	void SetMesh(uint32_t meshId) { GetComponent<MeshComponent>()->meshID = meshId; };
	uint32_t& GetMesh() { return GetComponent<MeshComponent>()->meshID; };

	bool IsColiding();
	bool IsColidingWith();
	//..

	Entity& GetEntity() { return m_entity; };
	template<typename T>
	void AddComponent(T* comp) { mp_ecsManager->AddComponent<T>(m_entity, comp); }
	template<typename T>
	T* GetComponent() const { return mp_ecsManager->GetComponent<T>(m_entity); }

private:
	ECSManager* mp_ecsManager;
	Entity m_entity;

	std::string m_name;
	Tag m_tag;
};

