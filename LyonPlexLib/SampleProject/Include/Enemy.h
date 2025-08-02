#pragma once

#include "StateMachine.h"
#include "Utils.h"
#include "Projectile.h"

enum EnemyType
{
	Crabe,
	Golem,

	EnemyTypeCount
};

class Enemy : public GameObject
{
	StateMachine<Enemy> m_stateMachine;

	enum State
	{
		Idle,
		Move,
		Shoot,
		Flee,
		Roam,

		Count
	};

public:
	
	Enemy(ECSManager* ecsManager, GameManager* gameManager, GameObject& gameObjectPlayer, Scene* scene, EnemyType type);

	void Init(GameManager* gameManager);
	void OnUdpdate(float deltatime) override;

	void SetStateMachine();

	const char* GetStateName(State state) const;
	const char* GetCurrentStateName() const;
	float GetDeltatime() { return m_deltatime; };

	void TakeDamage();

	void CreateProjectile(XMFLOAT3 posStart, XMFLOAT3 posTarget, float lifeTime = 3.f);

	void SetMoveSpeed(float speedValue) { m_moveSpeed = speedValue; };
	
	float GetMoveSpeed() { return m_moveSpeed; };

	Utils::Vector3 m_distanceBetweenEnnemyPlayer;

private:
	GameManager* mp_gameManager = nullptr;
	GameObject& m_playerGm;
	float m_deltatime;

	int m_life;
	float m_moveSpeed = 2.f;

	bool m_initialized = false;
	EnemyType m_type;

	Projectile m_newProjectile;
	GameObject* m_newProjectileGm = nullptr;

protected:
	friend class EnnemyAction_Idle;
	friend class EnnemyAction_Move;
	friend class EnnemyAction_Shoot;
	friend class EnnemyAction_Flee;
	friend class EnnemyAction_Roam;
};

