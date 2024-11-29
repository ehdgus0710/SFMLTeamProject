#pragma once
#include "PlayerBaseState.h"
class PlayerSkill1State : public PlayerBaseState
{
public:
	void OnThrowHead();
	void OnEndAniamtion();

public:
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	PlayerSkill1State(PlayerFSM* fsm);
	~PlayerSkill1State();

};

