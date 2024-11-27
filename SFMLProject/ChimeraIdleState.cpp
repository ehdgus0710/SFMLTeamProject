#include "stdafx.h"
#include "ChimeraIdleState.h"

ChimeraIdleState::ChimeraIdleState(ChimeraFSM* fsm)
	: ChimeraBaseState(fsm,ChimeraStateType::Idle)
{
}

ChimeraIdleState::~ChimeraIdleState()
{
}
void ChimeraIdleState::Awake()
{
}

void ChimeraIdleState::Start()
{
}

void ChimeraIdleState::Enter()
{
}

void ChimeraIdleState::Exit()
{
}

void ChimeraIdleState::Update(float deltaTime)
{
}

void ChimeraIdleState::FixedUpdate(float fixedDeltaTime)
{
}

void ChimeraIdleState::LateUpdate(float deltaTime)
{
}

