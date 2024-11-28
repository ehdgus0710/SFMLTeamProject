#pragma once
#include "PlayerBaseState.h"

class PlayerSkill1Sate : public PlayerBaseState
{
protected:
	Rigidbody*		rigidbody;
	float			horizontal;
	bool			isLeftRun;

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	PlayerSkill1Sate(PlayerFSM* fsm);
	~PlayerSkill1Sate();

};

