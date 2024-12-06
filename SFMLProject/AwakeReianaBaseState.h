#pragma once

#include "BaseState.h"
#include "AwakeReiana.h"
#include "AwakeReianaFsm.h"

class Animator;

class AwakeReianaBaseState : public BaseState<AwakeReianaStateType>
{
protected:
	AwakeReiana* awakeReiana;
	AwakeReianaFsm* fsm;
	Animator* animator;

	std::vector<std::function<void()>>	stateStartEvents;
	std::vector<std::function<void()>>	stateEndEvents;

public:
	void changeState(float dt);

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	AwakeReianaBaseState(AwakeReianaFsm* fsm, AwakeReianaStateType stateType);
	virtual ~AwakeReianaBaseState();
};

