#pragma once

#include "BaseState.h"
#include "Chimera.h"
#include "ChimeraFSM.h"

class Animator;

class ChimeraBaseState : public BaseState<ChimeraStateType>
{
protected:
	Chimera* chimera;
	ChimeraFSM* fsm;
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
	ChimeraBaseState(ChimeraFSM* fsm, ChimeraStateType stateType);
	virtual ~ChimeraBaseState();
};

