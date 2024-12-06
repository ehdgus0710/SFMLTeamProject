#pragma once
#include "AnimationGameObject.h"
#include "B_ReianaFsm.h"

class Camera;
class Rigidbody;
class Player;
class Reiana;

class B_Reiana : public AnimationGameObject
{
protected:
	B_Reiana* b_reiana;
	B_ReianaFsm	fsm;
	DefaultStatus	currentStatus;
	Player* player;
	bool			isHit = false;
public:
	void TakeDamage(float damage);
	void OnDead();

	B_ReianaFsm& GetFSM() { return fsm; }
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
	B_Reiana(const std::string& name = "B_Reiana");
	virtual ~B_Reiana();
	B_Reiana& operator= (const B_Reiana& other) = delete;
};