#pragma once

#include "SkeletonSpearBaseState.h"
class Rigidbody;

class SkeletonSpearFallingState : public SkeletonSpearBaseState
{
protected:
	Rigidbody* rigidbody;
	float horizontal;
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	SkeletonSpearFallingState(SkeletonSpearFSM* fsm);
	~SkeletonSpearFallingState();
};
