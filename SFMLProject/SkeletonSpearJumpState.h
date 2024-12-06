#pragma once

#include "SkeletonSpearBaseState.h"

class SkeletonSpearJumpState : public SkeletonSpearBaseState
{
protected:
	Rigidbody* rigidbody;
	float			horizontal;
	bool			isLeftRun;
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	SkeletonSpearJumpState(SkeletonSpearFSM* fsm);
	~SkeletonSpearJumpState();
};
