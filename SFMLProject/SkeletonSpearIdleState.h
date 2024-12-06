#pragma once
#include "SkeletonSpearBaseState.h"

class SkeletonSpearIdleState : public SkeletonSpearBaseState
{
protected:
	Rigidbody* rigidbody;
	float			horizontal;

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	SkeletonSpearIdleState(SkeletonSpearFSM* fsm);
	~SkeletonSpearIdleState();
};
