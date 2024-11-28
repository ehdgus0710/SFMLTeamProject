#include "stdafx.h"
#include "ReianaDeadState.h"

ReianaDeadState::ReianaDeadState(ReianaFsm* fsm)
	:ReianaBaseState(fsm,ReianaStateType::Dead)
{
}

ReianaDeadState::~ReianaDeadState()
{
}

void ReianaDeadState::Awake()
{
}

void ReianaDeadState::Start()
{
}

void ReianaDeadState::Enter()
{
}

void ReianaDeadState::Exit()
{
}

void ReianaDeadState::Update(float deltaTime)
{
}

void ReianaDeadState::FixedUpdate(float fixedDeltaTime)
{
}

void ReianaDeadState::LateUpdate(float deltaTime)
{
}
