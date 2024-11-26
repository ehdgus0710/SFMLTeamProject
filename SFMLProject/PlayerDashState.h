#pragma once
#include "PlayerBaseState.h"

class PlayerDashState : public PlayerBaseState
{
protected:
	Rigidbody*		rigidbody;
	float			horizontal;
	bool			isLeftRun;

	sf::Vector2f	dashEndPos;
	sf::Vector2f	dashStartPos;
	float			dashTime;
	float			currentTime;

	bool			extraDash;
	int				dashCount;
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	PlayerDashState(PlayerFSM* fsm);
	~PlayerDashState();

};

