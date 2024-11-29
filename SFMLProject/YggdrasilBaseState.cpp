#include "stdafx.h"
#include "YggdrasilBaseState.h"


YggdrasilBaseState::YggdrasilBaseState(YggdrasilFSM* fsm, YggdrasilStateType stateType)
	: BaseState<YggdrasilStateType>(stateType)
	, fsm(fsm)
	, reiana(fsm->GetChimera())
{
}

YggdrasilBaseState::~YggdrasilBaseState()
{
}

void YggdrasilBaseState::Awake()
{
	animator = Yggdrasil->GetAnimator();
}

void YggdrasilBaseState::Start()
{
}

void YggdrasilBaseState::Enter()
{
	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void YggdrasilBaseState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}

void YggdrasilBaseState::Update(float deltaTime)
{
}

void YggdrasilBaseState::FixedUpdate(float fixedDeltaTime)
{
}

void YggdrasilBaseState::LateUpdate(float deltaTime)
{
}
