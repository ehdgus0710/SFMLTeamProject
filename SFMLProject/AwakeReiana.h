#pragma once
#include "AnimationGameObject.h"
#include "AwakeReianaFsm.h"

class Camera;
class Rigidbody;
class Player;

class AwakeReiana : public AnimationGameObject
{
protected:
	AwakeReianaFsm	fsm;
	DefaultStatus	currentStatus;
	Player* player;
	bool			isHit = false;
	int				count;
public:
	void TakeDamage(const DamegeInfo& damage);
	void OnDead();

	AwakeReianaFsm& GetFSM() { return fsm; }
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
	void SetCount(int con);
	int GetCount() { return count; }
public:
	AwakeReiana(const std::string& name = "AwakeReiana");
	virtual ~AwakeReiana();
	AwakeReiana& operator= (const AwakeReiana& other) = delete;
};