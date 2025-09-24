#pragma once
#include "StateMachine.h"
#include "Projectile.h"

class Enemy;

class Player : public GameObject
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
		SpecialAttack,

		Count
	};


public:
	Player();
	void Init(ECSManager* ecsManager, GameManager* gameManager, Scene* scene, GameObject& cameraGO);
	
	void OnUpdate(float deltatime) override;

	void ApplyMovementAndCollisions(float dt);

	void Movement();

	const char* GetStateName(State state) const;
	const char* GetCurrentStateName() const;

	XMFLOAT3 GetWorldForwardFromGO(GameObject* go);

	void CreateProjectile(XMFLOAT3 posStart, XMFLOAT3 posTarget, float lifeTime);

	void HpUpdate();
	void DeathManager();
	void InvincibilityManager(float deltatime);
	void KnockeBackManager(float deltatime);
	void ApplyKnockback(const XMFLOAT3& sourcePos, float strength, float upward);

	GameObject m_playerGameObject;
	GameObject m_playerArm;

	GameObject m_playerHeart1, m_playerHeart2, m_playerHeart3, m_gameOver, m_weaponPlaceholder, m_selectedWeapon;

	GameObject& GetGameObject() { return m_playerGameObject; };
	void SetPlayerArm(GameObject& armGm) { m_playerArm = armGm; };
	GameObject& GetPlayerArm() { return m_playerArm; };
	bool GetHasCollided() { return m_hasCollided; };

	void SetMoveSpeed(float speedValue) { m_moveSpeed = speedValue; };
	float GetRunSpeed() { return m_runSpeed; };
	void SetRunSpeed(float speedValue) { m_runSpeed = speedValue; };
	float GetWalkSpeed() { return m_walkSpeed; };
	void SetWalkSpeed(float speedValue) { m_walkSpeed = speedValue; };
	float GetMoveSpeed() { return m_moveSpeed; };

	float GetDeltatime() { return m_deltatime; };

	bool IsAlive() { if (m_hp > 0) { return true; } else { return false; } };

	GameObject* m_closestObject = nullptr;
	GameObject* mp_cameraGO = nullptr;

	GameObject m_AOEboundingBox;

	Enemy* m_closestEnemy = nullptr;

	//Test Animation
	AnimationManager m_testAnimation;
	bool m_attackFinished;
	int m_slashAttackNb;

	int m_hp = 6;

	float m_walkSpeed = 15.0f;
	float m_runSpeed = 25.0f;
	float m_moveSpeed;

	float m_jumpPower = 30;// 10.f;
	float m_jumpTime = 0.15f;
	float m_jumpPosY = 0.0f;
	float m_jumpProgress = 0.0f;
	float m_fallProgress = 0.0f;

	float m_invincibilityTime = 1.0f;
	float m_invincibilityTimeCooldown = 0;
	bool m_isInvincible = false;

	DirectX::XMFLOAT3 m_velocity = { 0.0f, 0.0f, 0.0f };

	// variables de collision
	int   stuckFrames = 0;         // compte les frames ou le joueur est bloqu dans un objet
	XMVECTOR lastPushNormal = {};  // normale du dernier MTV

	float m_invicibilityCooldown = 2.0f;

	bool m_hasCollided = false;
	bool m_isPickingUp = false;
	bool m_isFalling = false;
	bool m_isOnGround = false;
	int m_coyoteFrames = 0; // initialise ÅE0
	static constexpr int COYOTE_MAX_FRAMES = 4; // ajustez le feeling (2-6)

	int m_currIdleMesh = TEXTURES::ARMS;

	std::vector<Entity> m_objectsCollidingWithPlayer;

	float m_deltatime;
	GameManager* mp_gameManager;
	Scene* mp_scene = nullptr;

	//knockback
	//XMFLOAT3 m_knockbackDir = { 0,0,0 };
	//float m_knockbackDist = 0;
	//float m_knockbackSpeed = 20.0f;
	struct KnockbackState
	{
		XMFLOAT3 dir;    // direction horizontale
		float speed;     // vitesse horizontale
		float distLeft;  // distance restante
		float upward;    // vitesse verticale temporaire
		bool active;
	};
	KnockbackState m_knockback;

private:

	std::vector<Projectile>m_projectileList;
	UINT m_renderWidth, m_renderHeight;

protected:
	friend class PlayerAction_Idle;
	friend class PlayerAction_Move;
	friend class PlayerAction_Jump;
	friend class PlayerAction_Attack;
	friend class PlayerAction_SpecialAttack;
};

