#pragma once

#include "GameObject.h"
#include "EnemyFSM.h"
#include "EnemySaveData.h"

class Enemy : public GameObject
{
protected:
	sf::Sprite		sprite;

	EnemyFSM*		fsm;
	sf::Vector2f	moveDirection;
	sf::Vector2f	hitDirection;
	DefaultStatus	currentStatus;
	EnemyStateType	currentState;
	EnemyType		enemyType;

	bool			isJumpDead;
	bool			isBulletDead;

	bool			isDead;
	bool			isFlipX;

public:
	void TakeDamage();
	virtual void OnDead();
	void OnFlipX();
	bool IsFlipX() { return isFlipX; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	const sf::Vector2f& GetMoveDirection() { return moveDirection; }
	void SetMoveDirection(const sf::Vector2f& direction) { moveDirection = direction; }

	void SetCurrentState(EnemyStateType state) { currentState = state; }
	const DefaultStatus& GetCurrentStatus() { return currentStatus; }

	void SetHitDirection(const sf::Vector2f& direction) { hitDirection = direction; }
	const sf::Vector2f& GetHitDirection() { return hitDirection; }

	void OnJumpDead() { isJumpDead = true; }
	bool IsJumpHitDead() { return isJumpDead; }
	void OnBulletDead() { isBulletDead = true; }
	bool IsBulletDead() { return isBulletDead; }

	int GetHP() { return currentStatus.hp; }
	EnemyFSM* GetFSM() { return fsm; }

	EnemyType GetEnemyType() { return enemyType; }
public:
	void CreateAnimator() override;
	float GetSpeed() { return currentStatus.speed; }


public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;


	EnemySaveData GetEnemySaveData() const;
	virtual void LoadEnemySaveData(const EnemySaveData& data);
public:
	Enemy(EnemyType type, const std::string& name = "Enemy");
	virtual ~Enemy();
	Enemy& operator= (const Enemy& other) = delete;
};

