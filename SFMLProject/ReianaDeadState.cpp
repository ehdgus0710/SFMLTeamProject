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
	if (!onDead)
	{
		SoundManger::GetInstance().PlaySfx("Leiana_Dead", false);
		onDead = true;
	}
	animator->ChangeAnimation("awakenReady", false);
}

