#pragma once
#include "PlayerBaseState.h"

class PlayerDashState : public PlayerBaseState
{
protected:
	Rigidbody*		rigidbody;

	float			moveDirection;
	float			dashTime;
	float			currentTime;

	bool			isGround;
	bool			isExtraDash;

private:
	void StartDash();
	void CreateEffect();

public:
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	PlayerDashState(PlayerFSM* fsm);
	~PlayerDashState();

};

