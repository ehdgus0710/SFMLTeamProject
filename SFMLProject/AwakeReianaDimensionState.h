#pragma once

#include "AwakeReianaBaseState.h"

class AwakeReianaDimensionState : public AwakeReianaBaseState
{
protected:
	float time = 1.5f;
	float currentTime = 0.f;

public:

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
	AwakeReianaDimensionState(AwakeReianaFsm* fsm);
	~AwakeReianaDimensionState();
};