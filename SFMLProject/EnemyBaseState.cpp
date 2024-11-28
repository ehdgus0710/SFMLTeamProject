#include "stdafx.h"
#include "EnemyBaseState.h"


EnemyBaseState::EnemyBaseState(EnemyFSM* fsm, EnemyStateType stateType)
	: BaseState<EnemyStateType>(stateType)
	, fsm(fsm)
	, enemy(fsm->GetEnemy())
{ 
}

EnemyBaseState::~EnemyBaseState()
{
}


void EnemyBaseState::Awake()
{
}

void EnemyBaseState::Start()
{
}

void EnemyBaseState::Enter()
{
	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void EnemyBaseState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}

void EnemyBaseState::Update(float deltaTime)
{
}

void EnemyBaseState::FixedUpdate(float fixedDeltaTime)
{
}

void EnemyBaseState::LateUpdate(float deltaTime)
{
}