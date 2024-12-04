#pragma once

#include "AwakeReianaBaseState.h"

class HitBoxObject;

class AwakeReianaGroundAttackState : public AwakeReianaBaseState
{
protected:
	HitBoxObject* hitBox;

	sf::Vector2f startPosition;
	sf::Vector2f endPosition;

	sf::Vector2f moveDistance = { 1500.f, 0.f };


	float waitTime = 0.6f;
	float currentWaitTime = 0.f;
	float endTime = 1.f;
	float attackTime = 1.5f;
	float currentAttackTime = 0.f;
	float damage = 20.f;

	bool start = false;
	bool action = false;

private:
	void Attack(float deltaTime);
	void Wait(float deltaTime);

	void ChangeReady2Animation();
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
	void OnCreateHitBox();
	void OnDestoryHitBox();
public:
	AwakeReianaGroundAttackState(AwakeReianaFsm* fsm);
	~AwakeReianaGroundAttackState();
};

