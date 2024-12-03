#include "stdafx.h"
#include "B_ReianaDeadState.h"
#include "Animator.h"
#include "Animation.h"

B_ReianaDeadState::B_ReianaDeadState(B_ReianaFsm* fsm)
	:B_ReianaBaseState(fsm, B_ReianaStateType::Dead)
{
}

B_ReianaDeadState::~B_ReianaDeadState()
{
}

void B_ReianaDeadState::Enter()
{
	animator->ChangeAnimation("dead", false);
}

