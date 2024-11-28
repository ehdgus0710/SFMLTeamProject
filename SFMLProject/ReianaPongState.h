#pragma once

#include "ReianaBaseState.h"

class ReianaPongState : public ReianaBaseState
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
	ReianaPongState(ReianaFsm* fsm);
	~ReianaPongState();
};