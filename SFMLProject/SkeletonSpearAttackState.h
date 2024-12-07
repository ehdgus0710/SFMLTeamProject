#pragma once

#include "SkeletonSpearBaseState.h"

class HitBoxObject;

class SkeletonSpearAttackState : public SkeletonSpearBaseState
{
protected:
	HitBoxObject* attackBox;
	Rigidbody* rigidbody;
	DamegeInfo		damageInfo;

	float			attackMoveSpeed;
	float			horizontal;
	bool			isMoveDirectionLeft;
	bool			sequenceAttack;
	int				currentAttackCount;

private:
	void EvenetClear();
	void CreateEffect(GameObject* object);
	void StartMove();
	void EndMove();
public:

	void StartAttack();
	void NextAttack();
	void LastAttack();
	void EndAttack();
	void SequenceAttack();
	void OnCreateHitBox();
	void OnDestoryHitBox();
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	SkeletonSpearAttackState(SkeletonSpearFSM* fsm);
	~SkeletonSpearAttackState();
};