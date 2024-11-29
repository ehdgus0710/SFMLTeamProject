#pragma once
#include "BaseState.h"
#include "YggdrasilFSM.h"

class YggdrasilBaseState : public BaseState<YggdrasilStateType>
{
protected:
	Yggdrasil* reiana;
	YggdrasilFSM* fsm;
	Animator* animator;

	std::vector<std::function<void()>>	stateStartEvents;
	std::vector<std::function<void()>>	stateEndEvents;

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	YggdrasilBaseState(YggdrasilFSM* fsm, YggdrasilStateType stateType);
	virtual ~YggdrasilBaseState();
};

