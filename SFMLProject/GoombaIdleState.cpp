#include "stdafx.h"
#include "GoombaIdleState.h"

GoombaIdleState::GoombaIdleState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Idle)
{
}

GoombaIdleState::~GoombaIdleState()
{
}

void GoombaIdleState::Awake()
{
}

void GoombaIdleState::Start()
{
}

void GoombaIdleState::Enter()
{
	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void GoombaIdleState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}

void GoombaIdleState::Update(float deltaTime)
{
}

void GoombaIdleState::FixedUpdate(float fixedDeltaTime)
{
}

void GoombaIdleState::LateUpdate(float deltaTime)
{
}