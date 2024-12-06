#pragma once

#include "BaseState.h"
#include "SkeletonSpear.h"
#include "SkeletonSpearFSM.h"

class Animator;

class SkeletonSpearBaseState : public BaseState<SkeletonSpearStateType>
{
protected:
	SkeletonSpear* skeletonSpear;
	SkeletonSpearFSM* fsm;
	Animator* animator;

	std::vector<std::string>			animationKeys;
	int									currentAnimationIndex;

	std::vector<std::function<void()>>	stateStartEvents;
	std::vector<std::function<void()>>	stateEndEvents;
public:
	virtual void SetChangeAnimationKey(int index);
	int GetAnimationIndex();

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	SkeletonSpearBaseState(SkeletonSpearFSM* fsm, SkeletonSpearStateType stateType);
	virtual ~SkeletonSpearBaseState();
};

