#pragma once

#include "BaseState.h"
#include "Player.h"
#include "PlayerFSM.h"

class Animator;

class PlayerBaseState : public BaseState<PlayerStateType>
{
protected:
	Player*		player;
	PlayerFSM*	fsm;
	Animator*	animator;

	std::vector<std::string>			animationKeys;
	int									currentAnimationIndex;

	std::vector<std::function<void()>>	stateStartEvents;
	std::vector<std::function<void()>>	stateEndEvents;
public:
	virtual void SetChangeAnimationKey(int index);

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;

public:
	PlayerBaseState(PlayerFSM* fsm, PlayerStateType stateType);
	virtual ~PlayerBaseState();
};

