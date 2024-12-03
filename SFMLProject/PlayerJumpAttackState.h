#pragma once
#include "PlayerBaseState.h"

class HitBoxObject;

class PlayerJumpAttackState : public PlayerBaseState
{
protected:
	Rigidbody*		rigidbody;
	HitBoxObject*	attackBox;
	DamegeInfo		damageInfo;
	float			horizontal;
	bool			sequenceAttack;

private:

	void CreateEffect(GameObject* object);
	void OnStartAttack();
	void OnEndAttack();
	void OnCreateHitBox();
	void OnDestoryHitBox();
	void ClearEvenet();
public:
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	PlayerJumpAttackState(PlayerFSM* fsm);
	~PlayerJumpAttackState();
};
