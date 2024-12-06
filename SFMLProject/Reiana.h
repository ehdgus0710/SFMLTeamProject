#pragma once
#include "AnimationGameObject.h"
#include "ReianaFsm.h"

class Camera;
class Rigidbody;
class Player;
class ReianaUIHub;

class Reiana : public AnimationGameObject
{
protected:
	ReianaFsm		fsm;
	DefaultStatus	currentStatus;
	Player*			player;
	ReianaUIHub*	reianaUIHub;
	bool			isHit = false;
	int				count;

	std::function<void(float, float)> changeHpAction;
public:
	void TakeDamage(const DamegeInfo& damage);
	void OnDead();

	ReianaFsm& GetFSM() { return fsm; }
	Player* GetPlayer() { return player; }
public:
	bool IsHit() const { return isHit; }

	void SetHp(float hp) { currentStatus.hp = hp; }
	float GetHp() { return currentStatus.hp; }

	void SetChangeHpAction(std::function<void(float, float)> action) { changeHpAction = action; }
	void SetReianaUIHub(ReianaUIHub* uiHub) { reianaUIHub = uiHub; }
	ReianaUIHub* GetReianaUIHub() { return reianaUIHub; }

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
	Reiana(const std::string& name = "Reiana");
	virtual ~Reiana();
	Reiana& operator= (const Reiana& other) = delete;
};