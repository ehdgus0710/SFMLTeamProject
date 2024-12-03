#pragma once

#include "YggdrasilBaseState.h"

class YggdrasilIdleState : public YggdrasilBaseState
{
protected:
	bool changeOn;
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	YggdrasilIdleState(YggdrasilFSM* fsm);
	~YggdrasilIdleState() = default;
};

