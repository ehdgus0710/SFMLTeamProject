#pragma once
#include "PlayerBaseState.h"
class PlayerSkill2State : public PlayerBaseState
{
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	PlayerSkill2State(PlayerFSM* fsm);
	~PlayerSkill2State();

};

