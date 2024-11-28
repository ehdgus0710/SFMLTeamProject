#pragma once

#include "ReianaBaseState.h"

class ReianaDropPoisonState : public ReianaBaseState
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
	ReianaDropPoisonState(ReianaFsm* fsm);
	~ReianaDropPoisonState();
};