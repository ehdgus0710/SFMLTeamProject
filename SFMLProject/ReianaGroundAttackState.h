#pragma once

#include "ReianaBaseState.h"

class ReianaGroundAttackState : public ReianaBaseState
{
protected:
	sf::Vector2f startPosition;
	sf::Vector2f endPosition;

	sf::Vector2f moveDistance = { 1500.f, 0.f };


	float waitTime = 0.5f;
	float currentWaitTime = 0.f;
	float attackTime = 0.5f;
	float currentAttackTime = 0.f;
	float damage = 20.f;

	bool action = false;

private:
	void Attack(float deltaTime);
	void Wait(float deltaTime);

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	ReianaGroundAttackState(ReianaFsm* fsm);
	~ReianaGroundAttackState();
};

