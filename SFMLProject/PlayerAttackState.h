#pragma once

#include "PlayerBaseState.h"

class HitBoxObject;

class PlayerAttackState : public PlayerBaseState
{
protected:
	HitBoxObject*	attackBox;
	Rigidbody*		rigidbody;
	DamegeInfo		damageInfo;

	float			attackMoveSpeed;
	float			horizontal;
	bool			isMoveDirectionLeft;
	bool			sequenceAttack;
	int				currentAttackCount;

private:
	void ClearEndAttackEvenet();
	void CreateEffect(GameObject* object);
	void StartMove();
	void EndMove();

	void SetAnimationEvent();
	void ClearAttackEvent();
public:

	void StartAttack();
	void NextAttack();
	void EndAttack();
	void SequenceAttack();
	void OnCreateHitBox();
	void OnDestoryHitBox();

	void SetChangeAnimationKey(int index) override;
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	PlayerAttackState(PlayerFSM* fsm);
	~PlayerAttackState();
};