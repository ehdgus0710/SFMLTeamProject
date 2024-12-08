#pragma once
#include "AnimationGameObject.h"
#include "AwakeReianaFsm.h"

class Camera;
class Rigidbody;
class Player;
class ReianaUIHub;

class AwakeReiana : public AnimationGameObject
{
protected:
	AwakeReianaFsm	fsm;
	DefaultStatus	currentStatus;
	Player* player;
	ReianaUIHub* reianaUIHub;

	bool			dead = false;
	bool			isHit = false;
	int				count;

	std::function<void(float, float)> changeHpAction;

public:
	void TakeDamage(const DamegeInfo& damage);
	void OnDead();

	AwakeReianaFsm& GetFSM() { return fsm; }
	Player* GetPlayer() { return player; }

	void SetReianaUIHub(ReianaUIHub* uiHub) { reianaUIHub = uiHub; }
	ReianaUIHub* GetReianaUIHub() { return reianaUIHub; }
public:
	bool IsHit() const { return isHit; }
	void SetHp(float hp) { currentStatus.hp = hp; }

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
	void SetCount(int con);
	int GetCount() { return count; }
public:
	AwakeReiana(const std::string& name = "AwakeReiana");
	virtual ~AwakeReiana();
	AwakeReiana& operator= (const AwakeReiana& other) = delete;
};