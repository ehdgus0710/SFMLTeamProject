#pragma once
#include "SkeletonSpearBaseState.h"

class SkeletonSpearRunState : public SkeletonSpearBaseState
{
protected:
	Rigidbody* rigidbody;
	float			horizontal;
	bool			isLeftRun;

protected:
	void InputMove();
	void InputJump();

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	SkeletonSpearRunState(SkeletonSpearFSM* fsm);
	~SkeletonSpearRunState();
};

