#include "stdafx.h"
#include "B_ReianaBaseState.h"

B_ReianaBaseState::B_ReianaBaseState(B_ReianaFsm* fsm, B_ReianaStateType stateType)
	: BaseState<B_ReianaStateType>(stateType)
	, fsm(fsm)
	, b_reiana(fsm->GetChimera())
{
}

B_ReianaBaseState::~B_ReianaBaseState()
{
}

void B_ReianaBaseState::Awake()
{
	animator = b_reiana->GetAnimator();
}

void B_ReianaBaseState::Start()
{
}

void B_ReianaBaseState::Enter()
{
	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void B_ReianaBaseState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}

void B_ReianaBaseState::Update(float deltaTime)
{
}

void B_ReianaBaseState::FixedUpdate(float fixedDeltaTime)
{
}

void B_ReianaBaseState::LateUpdate(float deltaTime)
{
}
