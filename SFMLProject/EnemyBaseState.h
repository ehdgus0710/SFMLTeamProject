#pragma once

#include "BaseState.h"
#include "Enemy.h"
#include "EnemyFSM.h"

class EnemyBaseState : public BaseState<EnemyStateType>
{
protected:
	Enemy*		enemy;
	EnemyFSM*	fsm;

	std::vector<std::function<void()>>	stateStartEvents;
	std::vector<std::function<void()>>	stateEndEvents;

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	EnemyBaseState(EnemyFSM* fsm, EnemyStateType stateType);
	virtual ~EnemyBaseState();
};

