#pragma once

#include "ReianaBaseState.h"

class ReianaDeadState : public ReianaBaseState
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
	ReianaDeadState(ReianaFsm* fsm);
	~ReianaDeadState();
};