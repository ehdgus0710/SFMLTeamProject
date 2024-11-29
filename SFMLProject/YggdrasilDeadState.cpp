#include "stdafx.h"
#include "YggdrasilDeadState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"

void YggdrasilDeadState::Enter()
{
}

void YggdrasilDeadState::Exit()
{
}

void YggdrasilDeadState::Update(float deltaTime)
{
}

void YggdrasilDeadState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilDeadState::YggdrasilDeadState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::Dead)
{
}
