#include "stdafx.h"
#include "KoopaTroopaIdleState.h"


KoopaTroopaIdleState::KoopaTroopaIdleState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Idle)
{
}

KoopaTroopaIdleState::~KoopaTroopaIdleState()
{
}

void KoopaTroopaIdleState::Awake()
{
}

void KoopaTroopaIdleState::Start()
{
}

void KoopaTroopaIdleState::Enter()
{
	enemy->SetCurrentState(stateType);
}

void KoopaTroopaIdleState::Exit()
{
}

void KoopaTroopaIdleState::Update(float deltaTime)
{
}

void KoopaTroopaIdleState::FixedUpdate(float fixedDeltaTime)
{
}

void KoopaTroopaIdleState::LateUpdate(float deltaTime)
{
}