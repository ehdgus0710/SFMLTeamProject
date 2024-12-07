#pragma once

#include "AwakeReianaBaseState.h"

class HitBoxObject;
class AwakenDropSide;
class AwakeReianaDropAttackState : public AwakeReianaBaseState
{
protected:
	HitBoxObject* hitBox;
	Rigidbody* rigidbody;
	sf::Vector2f startPosition;
	sf::Vector2f endPosition;
	sf::Vector2f moveDistance = { 0, 1000.f };
	sf::Vector2f waitStartPos = { 0, 700.f };
	sf::Vector2f waitEndPos;
	AwakenDropSide* awakenDropSide1;
	AwakenDropSide* awakenDropSide2;

	float landingTime = 1.5f;
	float currentLandingTime = 0.f;
	float waitTime = 0.5f;
	float currentWaitTime = 0.f;
	float dropTime = 0.3f;
	float currentDropTime = 0.f;
	float damage = 20.f;
	bool effect = false;
	bool action = false;
	bool attack = false;
	bool waitAnimation = false;
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
	AwakeReianaDropAttackState(AwakeReianaFsm* fsm);
	~AwakeReianaDropAttackState();
};