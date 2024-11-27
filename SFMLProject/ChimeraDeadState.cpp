#include "stdafx.h"
#include "ChimeraDeadState.h"

ChimeraDeadState::ChimeraDeadState(ChimeraFSM* fsm)
	:ChimeraBaseState(fsm,ChimeraStateType::Dead)
{
}

ChimeraDeadState::~ChimeraDeadState()
{
}

void ChimeraDeadState::Awake()
{
}

void ChimeraDeadState::Start()
{
}

void ChimeraDeadState::Enter()
{
}

void ChimeraDeadState::Exit()
{
}

void ChimeraDeadState::Update(float deltaTime)
{
}

void ChimeraDeadState::FixedUpdate(float fixedDeltaTime)
{
}

void ChimeraDeadState::LateUpdate(float deltaTime)
{
}
