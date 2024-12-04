#include "stdafx.h"
#include "AwakeReianaDeadState.h"
#include "Animator.h"
#include "Animation.h"

AwakeReianaDeadState::AwakeReianaDeadState(AwakeReianaFsm* fsm)
	:AwakeReianaBaseState(fsm, AwakeReianaStateType::Dead)
{
}

AwakeReianaDeadState::~AwakeReianaDeadState()
{
}

void AwakeReianaDeadState::Enter()
{
	AwakeReianaBaseState::Enter();
	animator->ChangeAnimation("dead", false);
}

