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
	float ryzerDistance = 320.f;


	float waitTime = 0.4f;
	float currentWaitTime = 0.f;
	float endTime = 1.5f;
	float attackTime = 1.0f;
	float currentAttackTime = 0.f;
	float damage = 20.f;

	bool attackFin = false;
	bool start = false;
	bool action = false;

private:
	void Attack(float deltaTime);
	void Wait(float deltaTime);
	void SetIdle();

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

