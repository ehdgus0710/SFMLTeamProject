#include "stdafx.h"
#include "YggdrasilIdleState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"
#include "Yggdrasil.h"
#include "Player.h"

void YggdrasilIdleState::Awake()
{
	YggdrasilBaseState::Awake();
}

void YggdrasilIdleState::Start()
{
	YggdrasilBaseState::Start();
	changeOn = false;
	attackTime = 0.f;
}

void YggdrasilIdleState::Enter()
{
	YggdrasilBaseState::Enter();
	if (yggdrasil->GetPhaseUp())
	{
		attackTime = 0.f;
		attackDelay = 2.5f;
		choiceAttack = 0;
		yggdrasil->SetAnimeLeftHand("phase2HandLeftIdle", true);
		yggdrasil->SetAnimeRightHand("phase2HandRightIdle", true);
		yggdrasil->SetAnimeBody("yggdrasilPhase2Body", false);
		yggdrasil->SetAnimeHead("yggdrasilPhase2Head", false);
		yggdrasil->SetAnimeMouth("yggdrasilPhase2Mouth", false);
	}
	else
	{
		attackTime = 0.f;
		attackDelay = 5.f;;
		choiceAttack = 0;
		yggdrasil->SetAnimeLeftHand("phase1HandLeftIdle", true);
		yggdrasil->SetAnimeRightHand("phase1HandRightIdle", true);
		yggdrasil->SetAnimeBody("yggdrasilPhase1Body", false);
		yggdrasil->SetAnimeHead("yggdrasilPhase1Head", false);
		yggdrasil->SetAnimeMouth("yggdrasilPhase1Mouth", false);
	}
}

void YggdrasilIdleState::Exit()
{
}

void YggdrasilIdleState::Update(float deltaTime)
{
	attackTime += deltaTime;

	if (yggdrasil->GetPhaseUp() && !changeOn)
	{
		Enter();
		changeOn = true;
	}

	if (!yggdrasil->GetPhaseUp())
	{
		if (attackTime > attackDelay)
		{
			choiceAttack = Utils::RandomRange(1, 3);
			attackTime = 0;
		}
		if (choiceAttack == 1)
		{
			fsm->ChangeState(YggdrasilStateType::FistAttack);
		}
		if (choiceAttack == 2)
		{
			fsm->ChangeState(YggdrasilStateType::SweepAttack);
		}
		if (choiceAttack == 3)
		{
			fsm->ChangeState(YggdrasilStateType::EnergyBallAttack);
		}
	}
	else
	{
		if (attackTime > attackDelay)
		{
			choiceAttack = Utils::RandomRange(1, 4);
			attackTime = 0;
		}
		if (choiceAttack == 1)
		{
			fsm->ChangeState(YggdrasilStateType::FistAttack);
		}
		else if (choiceAttack == 2)
		{
			fsm->ChangeState(YggdrasilStateType::SweepAttack);
		}
		else if (choiceAttack == 3)
		{
			fsm->ChangeState(YggdrasilStateType::EnergyBallAttack);
		}
		else if (choiceAttack == 4)
		{
			fsm->ChangeState(YggdrasilStateType::YggdrasilSpecialAttack);
		}
	}
}

void YggdrasilIdleState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilIdleState::YggdrasilIdleState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::Idle)
{
}
