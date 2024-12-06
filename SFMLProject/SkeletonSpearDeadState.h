#pragma once

#include "SkeletonSpearBaseState.h"

class SkeletonSpearDeadState : public SkeletonSpearBaseState
{
public:
	// void Awake() override;
	// void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	SkeletonSpearDeadState(SkeletonSpearFSM* fsm);
	~SkeletonSpearDeadState() = default;
};