#pragma once

#include "AnimationGameObject.h"
#include "EnemyFSM.h"
#include "EnemySaveData.h"

class Enemy : public AnimationGameObject
{
protected:
	EnemyFSM*		fsm;
	sf::Vector2f	moveDirection;
	sf::Vector2f	hitDirection;
	DefaultStatus	currentStatus;
	EnemyStateType	currentState;
	EnemyType		enemyType;

	bool			isJumpDead;
	bool			isBulletDead;

	bool			isDead;

public:
	void TakeDamage(const DamegeInfo& damage);
	virtual void OnDead();

	const sf::Vector2f& GetMoveDirection() { return moveDirection; }
	void SetMoveDirection(const sf::Vector2f& direction) { moveDirection = direction; }

	void SetCurrentState(EnemyStateType state) { currentState = state; }

	void SetHitDirection(const sf::Vector2f& direction) { hitDirection = direction; }
	const sf::Vector2f& GetHitDirection() { return hitDirection; }

	void OnJumpDead() { isJumpDead = true; }
	bool IsJumpHitDead() { return isJumpDead; }
	void OnBulletDead() { isBulletDead = true; }
	bool IsBulletDead() { return isBulletDead; }

	EnemyFSM* GetFSM() { return fsm; }
	EnemyType GetEnemyType() { return enemyType; }
public:
	float GetSpeed() { return currentStatus.speed; }
	float GetHP() { return currentStatus.hp; }
	const DefaultStatus& GetCurrentStatus() { return currentStatus; }


public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	EnemySaveData GetEnemySaveData() const;
	virtual void LoadEnemySaveData(const EnemySaveData& data);
public:
	Enemy(EnemyType type, const std::string& name = "Enemy");
	virtual ~Enemy();
	Enemy& operator= (const Enemy& other) = delete;
};

