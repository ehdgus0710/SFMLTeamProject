#pragma once

#include "PlayerBaseState.h"

class PlayerBreakState : public PlayerBaseState
{
protected:
	Rigidbody*		rigidbody;
	float			horizontal;
	bool			isMoveDirectionLeft;

	float			breakTime;
	float			currentBreakTime;
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	PlayerBreakState(PlayerFSM* fsm);
	~PlayerBreakState();
};