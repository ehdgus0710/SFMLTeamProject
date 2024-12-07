#pragma once

#include "AwakeReianaBaseState.h"

class AwakeReianaIdleState : public AwakeReianaBaseState
{
protected:
	int				count = 1;
	int				tossCount = 1;
	float			currentdelay = 0.f;
	float			delay = 1.f;
	float			currentStartDelay = 0.f;
	float			startDelay = 1.f;
	
	bool			start = false;
	bool			dash = false;
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
	void changeState(float dt);
public:
	AwakeReianaIdleState(AwakeReianaFsm* fsm);
	~AwakeReianaIdleState();
	int GetCount() { return count; }
};

