#pragma once
#include "EnemyBaseState.h"

class KoopaIdleState : public EnemyBaseState
{
private:
	Rigidbody*	rigidbody;
	float		attackWaitTime;
	float		currentAttackWaitTime;

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
public:
	KoopaIdleState(EnemyFSM* fsm);
	~KoopaIdleState();
};

