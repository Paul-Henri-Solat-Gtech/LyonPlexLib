#pragma once


enum ProjectileType
{
	Laser,
	Rock,

	projectileTypeCount
};

class Projectile
{

public:
	void Init(Scene* scene, XMFLOAT3 posStart, XMFLOAT3 posTarget, float lifeTime = 3.f);

	void OnUdpdate(float deltatime);

	void Destroy();

	//GameObject& GetPlayerGameObject() { return m_gmTarget; };
	GameObject* GetGameObject() { return m_projectileGameObject; };

private:
	Scene* mp_scene;

	//GameObject& m_gmTarget;
	GameObject* m_projectileGameObject = nullptr;

	float m_speed, m_lifetime;
	int m_damage;
};

