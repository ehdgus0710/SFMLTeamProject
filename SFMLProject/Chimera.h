#pragma once
#include "AnimationGameObject.h"
#include "ChimeraFSM.h"

class Camera;
class Rigidbody;

class Chimera : public AnimationGameObject
{
protected:
	ChimeraFSM	fsm;
	DefaultStatus	currentStatus;

	bool			isHit = false;

public:
	void TakeDamage();
	void AddItem(ItemType itemType);
	void Attack();
	void OnAttackEnd();


	ChimeraFSM& GetFSM() { return fsm; }
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
	Chimera(const std::string& name = "Chimera");
	virtual ~Chimera();
	Chimera& operator= (const Chimera& other) = delete;
};