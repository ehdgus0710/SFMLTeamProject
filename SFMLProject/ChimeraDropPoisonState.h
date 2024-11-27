#pragma once

#include "ChimeraBaseState.h"

class ChimeraDropPoisonState : public ChimeraBaseState
{
protected:

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	ChimeraDropPoisonState(ChimeraFSM* fsm);
	~ChimeraDropPoisonState();
};