#pragma once
#include "SkeletonSpearBaseState.h"

class HitBoxObject;

class SkeletonSpearJumpAttackState : public SkeletonSpearBaseState
{
protected:
	Rigidbody* rigidbody;
	HitBoxObject* attackBox;
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
	SkeletonSpearJumpAttackState(SkeletonSpearFSM* fsm);
	~SkeletonSpearJumpAttackState();
};

