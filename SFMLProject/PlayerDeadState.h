#pragma once

#include "PlayerBaseState.h"

class PlayerDeadState : public PlayerBaseState
{
public:
	// void Awake() override;
	// void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	PlayerDeadState(PlayerFSM* fsm);
	~PlayerDeadState() = default;
};