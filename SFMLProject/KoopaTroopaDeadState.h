#pragma once

#include "EnemyBaseState.h"
class KoopaTroopaDeadState : public EnemyBaseState
{
private:
	Rigidbody* rigidbody;
	sf::Vector2f hitDirection;

	float		rotationTime;
	float		currentRotationTime;
	float		currentTime;
	bool		isJumpDie;
	bool		isEndRotation;
	float		jumpDeadTime;

private:

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
	KoopaTroopaDeadState(EnemyFSM* fsm);
	~KoopaTroopaDeadState();
};

