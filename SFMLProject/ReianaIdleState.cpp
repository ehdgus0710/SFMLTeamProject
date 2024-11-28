#include "stdafx.h"
#include "ReianaIdleState.h"

ReianaIdleState::ReianaIdleState(ReianaFsm* fsm)
	: ReianaBaseState(fsm,ReianaStateType::Idle)
{
}

ReianaIdleState::~ReianaIdleState()
{
}
void ReianaIdleState::Awake()
{
}

void ReianaIdleState::Start()
{
}

void ReianaIdleState::Enter()
{
}

void ReianaIdleState::Exit()
{
}

void ReianaIdleState::Update(float deltaTime)
{
}

void ReianaIdleState::FixedUpdate(float fixedDeltaTime)
{
}

void ReianaIdleState::LateUpdate(float deltaTime)
{
}

