#pragma once

#include "PlayerBaseState.h"

class PlayerAttackState : public PlayerBaseState
{
protected:
	Rigidbody*		rigidbody;
	float			horizontal;
	bool			isMoveDirectionLeft;
	bool			sequenceAttack;
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;

	void EndAttack();
	void SequenceAttack();
public:
	PlayerAttackState(PlayerFSM* fsm);
	~PlayerAttackState();
};