#pragma once

#include "PlayerBaseState.h"

class PlayerAttackState : public PlayerBaseState
{
protected:
	Rigidbody*		rigidbody;
	float			horizontal;
	bool			isMoveDirectionLeft;
	bool			sequenceAttack;
	int				currentAttackCount;
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;

	void StartAttack();
	void NextAttack();
	void EndAttack();
	void SequenceAttack();
public:
	PlayerAttackState(PlayerFSM* fsm);
	~PlayerAttackState();
};