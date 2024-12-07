#include "stdafx.h"
#include "AwakeReianaAwakeState.h"
#include "Animator.h"
#include "Animation.h"

AwakeReianaAwakeState::AwakeReianaAwakeState(AwakeReianaFsm* fsm)
	:AwakeReianaBaseState(fsm, AwakeReianaStateType::Dead)
{
}

AwakeReianaAwakeState::~AwakeReianaAwakeState()
{
}

void AwakeReianaAwakeState::Enter()
{
	AwakeReianaBaseState::Enter();
	animator->ChangeAnimation("dead", false);
	awakeTiem = 1.f;
	awakeCurrentTime = 0.f;

}
void AwakeReianaAwakeState::Update(float deltaTime)
{
	AwakeReianaBaseState::Update(deltaTime);
	awakeCurrentTime += deltaTime;
	if (awakeTiem < awakeCurrentTime)
	{
		fsm->ChangeState(AwakeReianaStateType::Idle);
	}
}

