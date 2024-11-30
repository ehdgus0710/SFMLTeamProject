#include "stdafx.h"
#include "YggdrasilSweepAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"

void YggdrasilSweepAttackState::Enter()
{
}

void YggdrasilSweepAttackState::Exit()
{
}

void YggdrasilSweepAttackState::Update(float deltaTime)
{
}

void YggdrasilSweepAttackState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilSweepAttackState::YggdrasilSweepAttackState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::SweepAttack)
{
}
