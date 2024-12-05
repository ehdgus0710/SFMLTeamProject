#include "stdafx.h"
#include "AwakeReianaBaseState.h"

AwakeReianaBaseState::AwakeReianaBaseState(AwakeReianaFsm* fsm, AwakeReianaStateType stateType)
	: BaseState<AwakeReianaStateType>(stateType)
	, fsm(fsm)
	, awakeReiana(fsm->GetChimera())
{
}

AwakeReianaBaseState::~AwakeReianaBaseState()
{
}

void AwakeReianaBaseState::Awake()
{
	animator = awakeReiana->GetAnimator();
}

void AwakeReianaBaseState::Start()
{
}

void AwakeReianaBaseState::Enter()
{
	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void AwakeReianaBaseState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}

void AwakeReianaBaseState::Update(float deltaTime)
{
}

void AwakeReianaBaseState::FixedUpdate(float fixedDeltaTime)
{
}

void AwakeReianaBaseState::LateUpdate(float deltaTime)
{
}
