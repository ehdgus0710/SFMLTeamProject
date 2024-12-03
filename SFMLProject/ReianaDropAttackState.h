#pragma once

#include "ReianaBaseState.h"

class HitBoxObject;

class ReianaDropAttackState : public ReianaBaseState
{
protected:
	HitBoxObject* hitBox;
	Rigidbody* rigidbody;
	sf::Vector2f startPosition;
	sf::Vector2f endPosition;
	sf::Vector2f moveDistance = { 0, 1000.f };
	sf::Vector2f waitStartPos = { 0, 800.f };
	sf::Vector2f waitEndPos;

	float landingTime = 0.5f;
	float currentLandingTime = 0.f;
	float waitTime = 0.5f;
	float currentWaitTime = 0.f;
	float dropTime = 0.5f;
	float currentDropTime = 0.f;
	float damage = 20.f;
	bool effect = false;
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
	void OnCreateHitBox();
	void OnDestoryHitBox();
public:
	ReianaDropAttackState(ReianaFsm* fsm);
	~ReianaDropAttackState();
};