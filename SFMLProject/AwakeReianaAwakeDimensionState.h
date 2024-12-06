#pragma once

#include "AwakeReianaBaseState.h"

class HitBoxObject;

class AwakeReianaAwakeDimensionState : public AwakeReianaBaseState
{
protected:
	HitBoxObject* hitBox;

	float delay = 0.5f;
	float currentDelay = 0.f;
	float attackDelay = 0.3f;
	float currentAttackDelay = 0.f;
	float animationDelay = 0.5f;
	float currentAnimationDelay = 0.f;

	int endFrame;

	float leftPosition = 100.f;
	float rightPosition = 100.f;

	bool move = false;
	bool action = false;
	bool rush1 = false;
	bool rush2 = false;
	bool rush3 = false;
	bool playerPosCheck = false;
	bool animation = false;
	bool checkFilp = false;
public:
	void Attack(float deltaTime);
	void Wait(float deltaTime);
	void MoveSet();
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
	AwakeReianaAwakeDimensionState(AwakeReianaFsm* fsm);
	~AwakeReianaAwakeDimensionState();
};