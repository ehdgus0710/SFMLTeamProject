#include "stdafx.h"
#include "KoopaTroopaGroggyState.h"
#include "Animator.h"
#include "Rigidbody.h"

KoopaTroopaGroggyState::KoopaTroopaGroggyState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Groggy)
	, currentGroggyTime(0.f)
	, groggyTime(2.f)
{
}

KoopaTroopaGroggyState::~KoopaTroopaGroggyState()
{
}


void KoopaTroopaGroggyState::Awake()
{
}

void KoopaTroopaGroggyState::Start()
{
}
void KoopaTroopaGroggyState::Enter()
{
	enemy->SetCurrentState(stateType);
	enemy->GetAnimator()->ChangeAnimation("koopaTroopaGroggy", true);
	enemy->GetAnimator()->SetPlaying(false);
	currentGroggyTime = 0.f;
	enemy->GetRigidbody()->ResetVelocity();

	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void KoopaTroopaGroggyState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}
void KoopaTroopaGroggyState::Update(float deltaTime)
{
	currentGroggyTime += deltaTime;

	if (!isPlayAnimation && currentGroggyTime >= 1.f)
	{
		enemy->GetAnimator()->SetPlaying(true);
		isPlayAnimation = true;
	}

	if (currentGroggyTime >= 2.f)
	{
		fsm->ChangeState(EnemyStateType::Scout);
	}
}

void KoopaTroopaGroggyState::FixedUpdate(float fixedDeltaTime)
{
}

void KoopaTroopaGroggyState::LateUpdate(float deltaTime)
{
}