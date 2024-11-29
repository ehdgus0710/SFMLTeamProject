#include "stdafx.h"
#include "ReianaIdleState.h"
#include "Animator.h"

ReianaIdleState::ReianaIdleState(ReianaFsm* fsm)
	: ReianaBaseState(fsm,ReianaStateType::Idle)
{
}

ReianaIdleState::~ReianaIdleState()
{
}
void ReianaIdleState::Awake()
{
	ReianaBaseState::Awake();
}

void ReianaIdleState::Start()
{
	ReianaBaseState::Start();
}

void ReianaIdleState::Enter()
{
	ReianaBaseState::Enter();
	if (!reiana->IsFlipX())
		reiana->OnFlipX();
	animator->ChangeAnimation("idle", true);
}

void ReianaIdleState::Exit()
{
	ReianaBaseState::Exit();

}

void ReianaIdleState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);

}

void ReianaIdleState::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void ReianaIdleState::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);

}

