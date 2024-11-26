#include "stdafx.h"
#include "KoopaTroopaMoveState.h"
#include "Animator.h"
#include "Rigidbody.h"


KoopaTroopaMoveState::KoopaTroopaMoveState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Move)
	, rigidbody(nullptr)
	, speed(700.f)
{
}

KoopaTroopaMoveState::~KoopaTroopaMoveState()
{
}

void KoopaTroopaMoveState::Awake()
{
	rigidbody = enemy->GetRigidbody();
}

void KoopaTroopaMoveState::Start()
{
}

void KoopaTroopaMoveState::Enter()
{
	enemy->SetCurrentState(stateType);
	enemy->GetAnimator()->ChangeAnimation("koopaTroopaMove", true);
	moveDirection = enemy->GetMoveDirection();
	rigidbody->SetVelocity({ moveDirection.x * speed , rigidbody->GetCurrentVelocity().y });
}

void KoopaTroopaMoveState::Exit()
{
}

void KoopaTroopaMoveState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ moveDirection.x * speed , rigidbody->GetCurrentVelocity().y });
}