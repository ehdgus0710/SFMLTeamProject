#pragma once
#include "PlayerBaseState.h"

class PlayerDashState : public PlayerBaseState
{
protected:
	Rigidbody*		rigidbody;

	sf::Vector2f	dashEndPos;
	sf::Vector2f	dashStartPos;
	float			dashTime;
	float			currentTime;

	bool			isExtraDash;

private:
	void StartDash();

public:
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
public:
	PlayerDashState(PlayerFSM* fsm);
	~PlayerDashState();

};

