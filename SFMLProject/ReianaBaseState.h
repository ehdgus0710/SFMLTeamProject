#pragma once

#include "BaseState.h"
#include "Reiana.h"
#include "ReianaFsm.h"

class Animator;

class ReianaBaseState : public BaseState<ReianaStateType>
{
protected:
	Reiana* reiana;
	ReianaFsm* fsm;
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
	ReianaBaseState(ReianaFsm* fsm, ReianaStateType stateType);
	virtual ~ReianaBaseState();
};

