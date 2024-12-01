#pragma once
#include "AnimationGameObject.h"
#include "ReianaFsm.h"

class Camera;
class Rigidbody;
class Player;

class Reiana : public AnimationGameObject
{
protected:
	ReianaFsm	fsm;
	DefaultStatus	currentStatus;
	Player*			player;
	bool			isHit = false;

public:
	void TakeDamage(float damage);
	void OnDead();
	void Attack();
	void OnAttackEnd();

	ReianaFsm& GetFSM() { return fsm; }
	Player* GetPlayer() { return player; }
public:
	bool IsHit() const { return isHit; }

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
public:
	Reiana(const std::string& name = "Reiana");
	virtual ~Reiana();
	Reiana& operator= (const Reiana& other) = delete;
};