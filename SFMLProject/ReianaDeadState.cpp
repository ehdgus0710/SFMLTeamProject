#include "stdafx.h"
#include "ReianaDeadState.h"
#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "Rigidbody.h"

ReianaDeadState::ReianaDeadState(ReianaFsm* fsm)
	:ReianaBaseState(fsm,ReianaStateType::Dead)
{
}

ReianaDeadState::~ReianaDeadState()
{
}

void ReianaDeadState::OnChangeDeadAnimation()
{
	animator->ChangeAnimation("reianaDead", false);
	reiana->GetRigidbody()->SetActive(false);
}

void ReianaDeadState::Enter()
{
	ReianaBaseState::Enter();

	SoundManger::GetInstance().PlaySfx("Leiana_Dead", false);
	reiana->GetCollider()->SetActive(false);
	onDead = true;

	animator->ChangeAnimation("awakenReady", false);
	animator->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&ReianaDeadState::OnChangeDeadAnimation, this), animator->GetCurrentAnimation()->GetEndFrameCount());
}

