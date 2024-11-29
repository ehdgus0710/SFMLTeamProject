#pragma once

#include "ReianaBaseState.h"

class ReianaThreeSwordState : public ReianaBaseState
{
protected:
	float delayTime;
	float currentDelay;

	bool fix;
public:
	void Awake() override;
	void Start() override;

	void CreateKnife();

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	ReianaThreeSwordState(ReianaFsm* fsm);
	~ReianaThreeSwordState();
};