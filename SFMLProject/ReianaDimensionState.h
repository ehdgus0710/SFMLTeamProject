#pragma once

#include "ReianaBaseState.h"

class ReianaDimensionState : public ReianaBaseState
{
protected:
	void CreateDimension();


public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	ReianaDimensionState(ReianaFsm* fsm);
	~ReianaDimensionState();
};