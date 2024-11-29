#pragma once
#include "YggdrasilBaseState.h"


class YggdrasilDeadState : public YggdrasilBaseState
{
public:
	// void Awake() override;
	// void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	YggdrasilDeadState(YggdrasilFSM* fsm);
	~YggdrasilDeadState() = default;
};

