#pragma once
#include "EnemyBaseState.h"

class Rigidbody;

class GoombaScoutState : public EnemyBaseState
{
protected:
	Rigidbody*		rigidbody;
	sf::Vector2f	moveDirection;
	float			speed;

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;

	void FixedUpdate(float fixedDeltaTime) override;
public:
	GoombaScoutState(EnemyFSM* fsm);
	~GoombaScoutState();
};

