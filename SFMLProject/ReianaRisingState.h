#pragma once

#include "ReianaBaseState.h"

class RisingReady;
class Rising;

class ReianaRisingState : public ReianaBaseState
{
public:
	Rising* rising;
	RisingReady* risingReady;

	sf::Vector2f risingPos{ 45.f ,0.f };

	float RisingDelat = 0.05f;
	float CurrentRisingDelat;
	int count;
	
	float startDelay = 1.f;
	float startCurrentDelay;
	float endDelay = 1.f;
	float endCurrentDelay;
protected:
public:
	void Awake() override;
	void Start() override;

	void CreateRising();

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	ReianaRisingState(ReianaFsm* fsm);
	~ReianaRisingState();
};