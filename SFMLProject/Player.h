#pragma once
#include "AnimationGameObject.h"
#include "PlayerFSM.h"
#include "PlayerSaveData.h"

class Camera;
class Rigidbody;

class Player : public AnimationGameObject
{
protected:
	sf::Sprite	sprite;
	PlayerFSM	fsm;

	sf::Vector2f	moveDirection;
	DefaultStatus	currentStatus;

	int				jumpCount;
	int				currentJumpCount;

	float			hitTime;
	float			currentHitTime;
	float			reloadTime;
	float			currentReloadTime;

	bool			isJump;
	bool			isHit;
	bool			isDead;

	bool			isReload;
	bool			isAttack;

public:
	void TakeDamage();
	void AddItem(ItemType itemType);
	void Attack();
	void OnAttackEnd();

	const sf::Vector2f& GetMoveDirection() { return moveDirection; }

	PlayerFSM& GetFSM() { return fsm; }
public:
	bool IsHit() const { return isHit; }
	void SetIsJump(bool jump) { isJump = jump; }

	bool IsJump() const { return isJump; }
	float GetCurrentHP() const { return currentStatus.hp; }
	float GetSpeed() { return currentStatus.speed; }
	int GetJumpCount() { return jumpCount; }
	void SetCurrentJumpCount(int count) { currentJumpCount = count; }
	int GetCurrentJumpCount() { return currentJumpCount; }

	void SetHp(float hp) { currentStatus.hp = hp; }
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

	PlayerSaveData GetPlayerSaveData() const;
	void LoadData(const PlayerSaveData& data);
public:
	Player(const std::string& name = "Player");
	virtual ~Player();
	Player& operator= (const Player& other) = delete;
};

