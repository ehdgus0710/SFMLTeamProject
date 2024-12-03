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
	Head*			head;
	PlayerFSM		fsm;
	DefaultStatus	currentStatus;
	SkullType		skullType;

	float			moveDirectionX;

	int				jumpCount;
	int				currentJumpCount;
	int				dashCount;
	int				currentDashCount;

	float			dashDelayTime;
	float			currentDashDelayTime;
	float			reloadTime;
	float			currentReloadTime;

	float			currentSkill1CoolTime;
	float			currentSkill2CoolTime;
	float			skill1CoolTime;
	float			skill2CoolTime;
	bool			isSkll1CoolTime;
	bool			isSkll2CoolTime;
	bool			isJump;

	bool			isDead;
	bool			isReload;
	bool			isAttack;
	bool			isNoneHead;

	std::function<void(float, float)> changeHpAction;
public:
	void TakeDamage(const DamegeInfo& damage);
	void AddItem(ItemType itemType);
	void Attack();
	void OnAttackEnd();
	void OnDownJump();
	void OnThrowHead();
	void OnGetHead();

	void SetMoveDirection(float direction) { moveDirectionX = direction; }
	const float& GetMoveDirection() { return moveDirectionX; }

	PlayerFSM& GetFSM() { return fsm; }
	SkullType GetSkullType() { return skullType; }
public:
	void OnSkill1CoolTime();
	void OnSkill2CoolTime();

	void OnNoneHead() { isNoneHead = true; }
	bool IsNoneHead() { return isNoneHead; }

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

	void AddHp(float hp);
	void SetMaxHp(float hp);

	const DefaultStatus& GetCurrentStatus() { return currentStatus; }
	void SetChangeHpAction(std::function<void(float, float)> action) { changeHpAction = action; }
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

