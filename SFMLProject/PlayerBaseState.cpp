#include "stdafx.h"
#include "PlayerBaseState.h"

PlayerBaseState::PlayerBaseState(PlayerFSM* fsm, PlayerStateType stateType)
	: BaseState<PlayerStateType>(stateType)
	, fsm(fsm)
	, player(fsm->GetPlayer())
{
}

PlayerBaseState::~PlayerBaseState()
{
}

void PlayerBaseState::Awake()
{

}

void PlayerBaseState::Start()
{
}

void PlayerBaseState::Enter()
{
	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void PlayerBaseState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}

void PlayerBaseState::Update(float deltaTime)
{
}

void PlayerBaseState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerBaseState::LateUpdate(float deltaTime)
{
}
