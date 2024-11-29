#pragma once

#include "PlayerBaseState.h"

class HitBoxObject;

class PlayerAttackState : public PlayerBaseState
{
protected:
	HitBoxObject*	attackBox;
	Rigidbody*		rigidbody;
	float			horizontal;
	bool			isMoveDirectionLeft;
	bool			sequenceAttack;
	int				currentAttackCount;

private:
	void EvenetClear();

public:

	void StartAttack();
	void NextAttack();
	void EndAttack();
	void SequenceAttack();
	void OnCreateHitBox();
	void OnDestoryHitBox();
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	PlayerAttackState(PlayerFSM* fsm);
	~PlayerAttackState();
};