#include "stdafx.h"
#include "GoombaScoutState.h"
#include "Rigidbody.h"
#include "Animator.h"

GoombaScoutState::GoombaScoutState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Scout)
	, rigidbody(nullptr)
	, speed(300.f)
{
}

GoombaScoutState::~GoombaScoutState()
{
}

void GoombaScoutState::Awake()
{
	rigidbody = enemy->GetRigidbody();
}

void GoombaScoutState::Start()
{
}

void GoombaScoutState::Enter()
{
	enemy->GetAnimator()->ChangeAnimation("goombaMove", true);
	moveDirection = enemy->GetMoveDirection();
	enemy->SetMoveDirection(moveDirection);
	speed = enemy->GetSpeed();


	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void GoombaScoutState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}

	rigidbody->SetVelocity({ 0.f, rigidbody->GetCurrentVelocity().y });
}

void GoombaScoutState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ moveDirection.x * speed , rigidbody->GetCurrentVelocity().y });
}
