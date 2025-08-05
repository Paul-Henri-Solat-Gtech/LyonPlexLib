#pragma once


enum ProjectileType
{
	Laser,
	Rock,

	ProjectileTypeCount
};

class Projectile
{

public:
	void Init(Scene* scene, XMFLOAT3 posStart, XMFLOAT3 posTarget, ProjectileType type = ProjectileType::Laser, float lifeTime = 3.f);

	void OnUdpdate(float deltatime);

	void Destroy();

	void Laube(XMFLOAT3 posStart, XMFLOAT3 posTarget);

	//GameObject& GetPlayerGameObject() { return m_gmTarget; };
	GameObject* GetGameObject() { return m_projectileGameObject; };

private:
	Scene* mp_scene;

	//GameObject& m_gmTarget;
	GameObject* m_projectileGameObject = nullptr;

	ProjectileType m_projectileType;

	float m_speed, m_lifetime;
	int m_damage;
};

