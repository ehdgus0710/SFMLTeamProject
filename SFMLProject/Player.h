#pragma once
#include "GameObject.h"
#include "PlayerFSM.h"
#include "PlayerSaveData.h"

class Camera;
class Rigidbody;

class Player : public GameObject
{
protected:
	sf::Sprite	sprite;
	PlayerFSM	fsm;
	Camera*		mainCamera;

	sf::Vector2f	moveDirection;
	DefaultStatus	currentStatus;

	sf::Color		effectColor;
	sf::Color		defaultColor;

	float			hitTime;
	float			currentHitTime;
	float			reloadTime;
	float			currentReloadTime;

	float			currentStarState;
	float			starStateTime;

	bool			isJump;
	bool			isHit;
	bool			isDead;
	bool			isFlipX;

	bool			isReload;
	bool			isAttack;
	bool			isStarState;
	bool			isRun;

	int				currentColorIndex;
	float			colorChangeTime;
	float			currentColorTime;

	sf::Color		starStateChangeColors[4];

public:
	void TakeDamage();
	void OnFlipX();
	bool IsFlipX() { return isFlipX; }
	void AddHp() { ++currentStatus.hp; }
	void AddItem(ItemType itemType);
	void TakeUpgrade();
	void Attack();
	void OnAttackEnd();

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	const sf::Vector2f& GetMoveDirection() { return moveDirection; }

	PlayerFSM& GetFSM() { return fsm; }
public:
	void CreateAnimator() override;

	bool IsRun() { return isRun; }
	bool IsHit() const { return isHit; }
	bool IsStarState() { return isStarState; }
	void SetIsJump(bool jump) { isJump = jump; }
	int GetCurrentHP() const { return currentStatus.hp; }
	float GetSpeed() { return currentStatus.speed + (isRun ? 300.f : 0.f); }

	void SetHp(int hp) { currentStatus.hp = hp; }
	void ChangeSmallMario();
	void ChangeMario(int hp);
	void OnStarState();

public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;

	PlayerSaveData GetPlayerSaveData() const;
	void LoadData(const PlayerSaveData& data);
public:
	Player(const std::string& name = "Player");
	virtual ~Player();
	Player& operator= (const Player& other) = delete;
};

