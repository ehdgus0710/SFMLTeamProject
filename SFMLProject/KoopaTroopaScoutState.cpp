#include "stdafx.h"
#include "KoopaTroopaScoutState.h"
#include "Rigidbody.h"
#include "Animator.h"

KoopaTroopaScoutState::KoopaTroopaScoutState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Scout)
	, rigidbody(nullptr)
	, speed(100.f)
{
}

KoopaTroopaScoutState::~KoopaTroopaScoutState()
{
}

void KoopaTroopaScoutState::Awake()
{
	rigidbody = enemy->GetRigidbody();
}

void KoopaTroopaScoutState::Start()
{
}

void KoopaTroopaScoutState::Enter()
{
	
	enemy->SetCurrentState(stateType);
	enemy->GetAnimator()->ChangeAnimation("koopaTroopaScout", true);
	moveDirection = enemy->GetMoveDirection();
	
	if (moveDirection.x < 0.f && enemy->IsFlipX())
		enemy->OnFlipX();
	else if (moveDirection.x > 0.f && !enemy->IsFlipX())
		enemy->OnFlipX();

	speed = enemy->GetSpeed();
	rigidbody->SetVelocity({ moveDirection.x * speed , rigidbody->GetCurrentVelocity().y });


	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void KoopaTroopaScoutState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}

	rigidbody->SetVelocity({ 0.f, rigidbody->GetCurrentVelocity().y });
}

void KoopaTroopaScoutState::FixedUpdate(float fixedDeltaTime)
{
}
