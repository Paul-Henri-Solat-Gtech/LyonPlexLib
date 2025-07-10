#pragma once

#include "StateMachine.h"


class Projectile
{
	StateMachine<Projectile> m_stateMachine;

	enum State
	{
		Idle,
		Move,
		Collide,
		/*Jump,
		Attack,
		Fall,*/

		Count
	};

	//int m_hp = 10;

	//float m_walkSpeed = 2.0f;
	//float m_runSpeed = 5.0f;
	float m_moveSpeed;
	//float m_jumpPower = 5.0f;
	//float m_invicibilityCooldown = 2.0f;

	bool m_hasCollided = false;

	float m_deltatime;

public:
	Projectile();
	void Init(GameObject gameObjectProjectile, GameObject gameObjectPlayer, GameManager* gameManager);

	void OnUdpdate(float deltatime);

	const char* GetStateName(State state) const;
	const char* GetCurrentStateName() const;

	GameObject m_playerGameObject;
	GameObject m_projectileGameObject;

	GameObject& GetPlayerGameObject() { return m_playerGameObject; };
	GameObject& GetGameObject() { return m_projectileGameObject; };
	bool GetHasCollided() { return m_hasCollided; };

	void SetMoveSpeed(float speedValue) { m_moveSpeed = speedValue; };
	//float GetRunSpeed() { return m_runSpeed; };
	//float GetWalkSpeed() { return m_walkSpeed; };
	float GetMoveSpeed() { return m_moveSpeed; };

	float GetDeltatime() { return m_deltatime; };

	//Test Animation
	//AnimationManager m_testAnimation;
	//bool m_attackFinished;
	//int m_slashAttackNb;

private:
	GameManager* mp_gameManager;

protected:
	friend class ProjectileAction_Idle;
	friend class ProjectileAction_Move;
};

