#include "stdafx.h"
#include "KoopaIdleState.h"
#include "Rigidbody.h"
#include "Animation.h"
#include "Animator.h"

KoopaIdleState::KoopaIdleState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Idle)
	, rigidbody(nullptr)
	, attackWaitTime(2.f)
	,currentAttackWaitTime(0.f)
{
}

KoopaIdleState::~KoopaIdleState()
{
}

void KoopaIdleState::Awake()
{
	rigidbody = enemy->GetRigidbody();
}

void KoopaIdleState::Start()
{
}

void KoopaIdleState::Enter()
{
	enemy->GetAnimator()->ChangeAnimation("koopaIdle", true);
	currentAttackWaitTime = 0.f;

	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void KoopaIdleState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}

void KoopaIdleState::Update(float deltaTime)
{
	currentAttackWaitTime += deltaTime;

	if (currentAttackWaitTime > attackWaitTime)
	{
		fsm->ChangeState(EnemyStateType::Attack);
		currentAttackWaitTime = 0.f;
	}
}
