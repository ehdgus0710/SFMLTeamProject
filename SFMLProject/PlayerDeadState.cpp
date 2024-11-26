#include "stdafx.h"
#include "PlayerDeadState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"

PlayerDeadState::PlayerDeadState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Dead)
{
}

void PlayerDeadState::Enter()
{
	PlayerBaseState::Enter();
}

void PlayerDeadState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerDeadState::Update(float deltaTime)
{
}

void PlayerDeadState::FixedUpdate(float fixedDeltaTime)
{
}