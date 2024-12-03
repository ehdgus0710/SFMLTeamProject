#pragma once

#include "ReianaBaseState.h"

class ReianaIdleState : public ReianaBaseState
{
protected:
	int				count = 1;
	int				tossCount = 1;
	float			currentdelay = 0.f;
	float			delay = 2.f;

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
	ReianaIdleState(ReianaFsm* fsm);
	~ReianaIdleState();
	int GetCount() { return count; }
};

