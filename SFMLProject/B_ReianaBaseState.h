#pragma once

#include "BaseState.h"
#include "B_Reiana.h"
#include "B_ReianaFsm.h"

class Animator;

class B_ReianaBaseState : public BaseState<B_ReianaStateType>
{
protected:
	B_Reiana* b_reiana;
	B_ReianaFsm* fsm;
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
	B_ReianaBaseState(B_ReianaFsm* fsm, B_ReianaStateType stateType);
	virtual ~B_ReianaBaseState();
};

