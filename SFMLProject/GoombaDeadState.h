#pragma once
#include "EnemyBaseState.h"

class Rigidbody;

class GoombaDeadState : public EnemyBaseState
{
private:
	Rigidbody*		 rigidbody;
	sf::Vector2f hitDirection;

	float		rotationTime;
	float		currentRotationTime;
	float		currentTime;
	bool		isJumpDie;
	bool		isEndRotation;
	float		jumpDeadTime;

public:
	void IsJumpDie(float deltaTime);
	void IsHitDie(float deltaTime);

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	GoombaDeadState(EnemyFSM* fsm);
	~GoombaDeadState();
};

