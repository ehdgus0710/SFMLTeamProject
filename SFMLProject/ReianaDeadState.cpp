#include "stdafx.h"
#include "ReianaDeadState.h"
#include "Animator.h"
#include "Animation.h"

ReianaDeadState::ReianaDeadState(ReianaFsm* fsm)
	:ReianaBaseState(fsm,ReianaStateType::Dead)
{
}

ReianaDeadState::~ReianaDeadState()
{
}

void ReianaDeadState::Enter()
{
	ReianaBaseState::Enter();
	animator->ChangeAnimation("dead", false);
}

