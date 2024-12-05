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
	animator->ChangeAnimation("awakenDarkDeadBody", false);
	Animation* animation = new Animation();
	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&AwakeReianaDeadState::OnDead, this), endFrame);
}

void AwakeReianaDeadState::OnDead()
{
	awakeReiana->SetActive(false);
}


