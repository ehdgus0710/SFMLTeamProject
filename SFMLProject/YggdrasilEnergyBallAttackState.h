#pragma once

#include "YggdrasilBaseState.h"


class YggdrasilEnergyBallAttackState : public YggdrasilBaseState
{
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	YggdrasilEnergyBallAttackState(YggdrasilFSM* fsm);
	~YggdrasilEnergyBallAttackState() = default;
};

