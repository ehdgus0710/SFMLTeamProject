#pragma once

#include "ReianaBaseState.h"

class ReianaAroundDimensionState : public ReianaBaseState
{
protected:
	sf::Vector2f leftPos{ -45.f,0.f };
	sf::Vector2f rigthPos{ 45.f,0.f };

	float delay;
	float currentDelay;
	int count;

	void CreateLeftDimension();
	void CreateRigthDimension();
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	ReianaAroundDimensionState(ReianaFsm* fsm);
	~ReianaAroundDimensionState();
};