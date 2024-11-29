#pragma once
#include "AnimationGameObject.h"
#include "PlayerFSM.h"
#include "PlayerSaveData.h"

class Camera;
class Rigidbody;
class Head;
class GameObject;

class Player : public AnimationGameObject
{
protected:
	Head*		head;
	GameObject* gameObject;

	sf::Sprite	sprite;
	PlayerFSM	fsm;

	float		moveDirectionX;
	DefaultStatus	currentStatus;

	int				jumpCount;
	int				currentJumpCount;
	int				dashCount;
	int				currentDashCount;

	float			dashDelayTime;
	float			currentDashDelayTime;
	float			hitTime;
	float			currentHitTime;
	float			reloadTime;
	float			currentReloadTime;

	float			currentSkill1CoolTime;
	float			currentSkill2CoolTime;
	float			skill1CoolTime;
	float			skill2CoolTime;
	bool			isSkll1CoolTime;
	bool			isSkll2CoolTime;
	bool			isJump;
	bool			isHit;
	bool			isDead;
	bool			isReload;
	bool			isAttack;
	bool			isNoneHead;
public:
	void TakeDamage();
	void TakeDamage(float damage);
	void AddItem(ItemType itemType);
	void Attack();
	void OnAttackEnd();
	void OnDownJump();
	void OnThrowHead();

	void SetMoveDirection(float direction) { moveDirectionX = direction; }
	const float& GetMoveDirection() { return moveDirectionX; }

	PlayerFSM& GetFSM() { return fsm; }
public:
	void OnSkill1CoolTime();
	void OnSkill2CoolTime();

	void OnNoneHead() { isNoneHead = true; }
	bool IsNoneHead() { return isNoneHead; }

	bool IsHit() const { return isHit; }
	void SetIsJump(bool jump) { isJump = jump; }

	bool IsJump() const { return isJump; }
	float GetCurrentHP() const { return currentStatus.hp; }
	float GetSpeed() { return currentStatus.speed; }
	int GetJumpCount() { return jumpCount; }
	void SetCurrentJumpCount(int count) { currentJumpCount = count; }
	int GetCurrentJumpCount() { return currentJumpCount; }
	int GetDashCount() { return dashCount; }

	void SetHeadPosition(sf::Vector2f pos);
	sf::Vector2f GetHeadPosition();

	void OnDash() { --currentDashCount; }
	int GetCurrentDashCount() { return currentDashCount; }

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

