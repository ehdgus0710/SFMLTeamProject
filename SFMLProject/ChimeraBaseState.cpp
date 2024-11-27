#include "stdafx.h"
#include "ChimeraBaseState.h"

ChimeraBaseState::ChimeraBaseState(ChimeraFSM* fsm, ChimeraStateType stateType)
	: BaseState<ChimeraStateType>(stateType)
	, fsm(fsm)
	, chimera(fsm->GetChimera())
{
}

ChimeraBaseState::~ChimeraBaseState()
{
}

void ChimeraBaseState::Awake()
{
	animator = chimera->GetAnimator();
}

void ChimeraBaseState::Start()
{
}

void ChimeraBaseState::Enter()
{
	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void ChimeraBaseState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}

void ChimeraBaseState::Update(float deltaTime)
{
}

void ChimeraBaseState::FixedUpdate(float fixedDeltaTime)
{
}

void ChimeraBaseState::LateUpdate(float deltaTime)
{
}
