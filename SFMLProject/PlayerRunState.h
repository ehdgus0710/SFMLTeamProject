#pragma once

#include "PlayerBaseState.h"

class PlayerRunState : public PlayerBaseState
{
protected:
	Rigidbody*		rigidbody;
	float			horizontal;
	bool			isLeftRun;

protected:
	void InputMove();
	void InputJump();

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	PlayerRunState(PlayerFSM* fsm);
	~PlayerRunState();
};
