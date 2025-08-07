#pragma once

enum ProjectileType
{
	Laser,
	Rock,

	ProjectileTypeCount
};

class Projectile : public GameObject
{

public:
	Projectile(Scene* scene, XMFLOAT3 posStart, XMFLOAT3 posTarget, ProjectileType type = ProjectileType::Laser, float lifeTime = 3.f);

	void InitProjectile(XMFLOAT3 posStart, XMFLOAT3 posTarget);

	void OnUdpdate(float deltatime) override;

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

