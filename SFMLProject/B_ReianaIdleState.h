#pragma once

#include "B_ReianaBaseState.h"

class Reiana;

class B_ReianaIdleState : public B_ReianaBaseState
{
protected:
	Reiana* reiana;

	int				count = 1;
	float			currentdelay = 0.f;
	float			delay = 1.f;
	
	float			startDelay = 2.f;
	float			currentStartdelay = 0.f;

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
	B_ReianaIdleState(B_ReianaFsm* fsm);
	~B_ReianaIdleState();
};

