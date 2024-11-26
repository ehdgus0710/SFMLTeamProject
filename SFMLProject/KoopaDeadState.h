#pragma once

#include "EnemyBaseState.h"
class Koopa;

class KoopaDeadState : public EnemyBaseState
{
private:
	Rigidbody*	rigidbody;
	Koopa*		koopa;

	float		rotationTime;
	float		currentRotationTime;


	float		currentOffTime;
	float		offScaffoldingTime;
	float		currentTime;
	bool		isStartEvent;
	bool		isLabberDie;
	bool		isHitDie;
	bool		isEndRotation;
	int			currentIndex;


private:
	void EndDead();
	void LabberDie();
	void HitDie(float deltaTime);

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	KoopaDeadState(EnemyFSM* fsm);
	~KoopaDeadState();
};

