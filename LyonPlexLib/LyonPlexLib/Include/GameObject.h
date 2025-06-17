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

	TagCount
};

class GameObject
{
public:
	void Init(const std::string& name, ECSManager* ecsManager);
	void Init(const std::string& name, ECSManager* ecsManager, DimensionalType type);

	void SetName(const std::string& name) { m_name = name; };
	const std::string& GetName() { return m_name; };
	void SetTag(Tag tag) { m_tag = tag; };
	Tag GetTag() { return m_tag; };

	// Components
	void SetPosition(XMFLOAT3 pos) { GetComponent<TransformComponent>()->position = pos; };
	XMFLOAT3 GetPosition() { return GetComponent<TransformComponent>()->position; };
	void SetRotation(XMFLOAT4 rot) { GetComponent<TransformComponent>()->rotation = rot; };
	XMFLOAT4 GetRotation() { return GetComponent<TransformComponent>()->rotation; };
	void SetScale(XMFLOAT3 scl) { GetComponent<TransformComponent>()->scale = scl; };
	XMFLOAT3 GetScale() { return GetComponent<TransformComponent>()->scale; };

	bool IsColiding();
	bool IsColidingWith();
	//..

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

