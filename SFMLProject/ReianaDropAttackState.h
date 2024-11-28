#pragma once

#include "ReianaBaseState.h"

class ReianaDropAttackState : public ReianaBaseState
{
protected:
	Rigidbody* rigidbody;
	sf::Vector2f startPosition;
	sf::Vector2f endPosition;
	sf::Vector2f moveDistance = { 0, 1000.f };

	float waitTime = 0.5f;
	float currentWaitTime = 0.f;
	float dropTime = 0.5f;
	float currentDropTime = 0.f;
	float damage = 20.f;

	bool action = false;
public:
	void Wait(float deltaTime);
	void Drop(float deltaTime);

	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	ReianaDropAttackState(ReianaFsm* fsm);
	~ReianaDropAttackState();
};