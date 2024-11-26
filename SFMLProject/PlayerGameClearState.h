#pragma once

#include "PlayerBaseState.h"

class PlayerGameClearState : public PlayerBaseState
{

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	PlayerGameClearState(PlayerFSM* fsm);
	~PlayerGameClearState();
};

