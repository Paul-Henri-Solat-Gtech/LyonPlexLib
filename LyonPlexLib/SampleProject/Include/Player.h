#pragma once
#include "StateMachine.h"
class Enemy;

class Player
{
	StateMachine<Player> m_stateMachine;

	enum State
	{
		Idle,
		Move,
		Jump,
		Attack,
		Fall,
		PickUp,

		Count
	};


public:
	Player();
	void Init(GameObject gameObject, GameManager* gameManager, Scene* scene, GameObject& cameraGO);
	
	void OnUdpdate(float deltatime);

	void ApplyMovementAndCollisions(float dt);

	void Movement();

	const char* GetStateName(State state) const;
	const char* GetCurrentStateName() const;

	GameObject m_playerGameObject;
	GameObject m_playerArm;

	GameObject& GetGameObject() { return m_playerGameObject; };
	void SetPlayerArm(GameObject& armGm) { m_playerArm = armGm; };
	GameObject& GetPlayerArm() { return m_playerArm; };
	bool GetHasCollided() { return m_hasCollided; };

	void SetMoveSpeed(float speedValue) { m_moveSpeed = speedValue; };
	float GetRunSpeed() { return m_runSpeed; };
	float GetWalkSpeed() { return m_walkSpeed; };
	float GetMoveSpeed() { return m_moveSpeed; };

	float GetDeltatime() { return m_deltatime; };

	GameObject* m_closestObject = nullptr;
	GameObject* mp_cameraGO = nullptr;

	Enemy* m_closestEnemy = nullptr;

	//Test Animation
	AnimationManager m_testAnimation;
	bool m_attackFinished;
	int m_slashAttackNb;

	int m_hp = 10;

	float m_walkSpeed = 25.0f;
	float m_runSpeed = 35.0f;
	float m_moveSpeed;

	float m_jumpPower = 25.f;
	float m_jumpTime = 0.15f;
	float m_jumpPosY = 0.0f;
	float m_jumpProgress = 0.0f;
	float m_fallProgress = 0.0f;

	DirectX::XMFLOAT3 m_velocity = { 0.0f, 0.0f, 0.0f };

	// variables de collision
	int   stuckFrames = 0;         // compte les frames ou le joueur est bloqu dans un objet
	XMVECTOR lastPushNormal = {};  // normale du dernier MTV

	float m_invicibilityCooldown = 2.0f;

	bool m_hasCollided = false;
	bool m_isPickingUp = false;
	bool m_isFalling = false;
	bool m_isOnGround = false;

	int m_currIdleMesh = TEXTURES::ARMS;

	std::vector<Entity> m_objectsCollidingWithPlayer;

	float m_deltatime;
	GameManager* mp_gameManager;
	Scene* mp_scene = nullptr;

private:

protected:
	friend class PlayerAction_Idle;
	friend class PlayerAction_Move;
	friend class PlayerAction_Jump;
	friend class PlayerAction_Attack;
};

