#pragma once
#include "PlayerBaseState.h"
class Rigidbody;

class PlayerFallingState : public PlayerBaseState
{
protected:
	Rigidbody* rigidbody;
	float horizontal;
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	PlayerFallingState(PlayerFSM* fsm);
	~PlayerFallingState();
};


