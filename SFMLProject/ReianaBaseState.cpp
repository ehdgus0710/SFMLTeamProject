#include "stdafx.h"
#include "ReianaBaseState.h"

ReianaBaseState::ReianaBaseState(ReianaFsm* fsm, ReianaStateType stateType)
	: BaseState<ReianaStateType>(stateType)
	, fsm(fsm)
	, reiana(fsm->GetChimera())
{
}

ReianaBaseState::~ReianaBaseState()
{
}

void ReianaBaseState::Awake()
{
	animator = reiana->GetAnimator();
}

void ReianaBaseState::Start()
{
}

void ReianaBaseState::Enter()
{
	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void ReianaBaseState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}

void ReianaBaseState::Update(float deltaTime)
{
}

void ReianaBaseState::FixedUpdate(float fixedDeltaTime)
{
}

void ReianaBaseState::LateUpdate(float deltaTime)
{
}
