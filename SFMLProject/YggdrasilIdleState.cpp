#include "stdafx.h"
#include "YggdrasilIdleState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"
#include "Yggdrasil.h"
#include "Player.h"


void YggdrasilIdleState::Moves(float dt)
{

}

void YggdrasilIdleState::Awake()
{
	YggdrasilBaseState::Awake();
}

void YggdrasilIdleState::Start()
{
	YggdrasilBaseState::Start();
	changeOn = false;

	//yggdrasil = static_cast<Yggdrasil*>(SceneManager::GetInstance().GetCurrentScene()->FindGameObject("Yggdrasil", LayerType::Boss));

}

void YggdrasilIdleState::Enter()
{
	YggdrasilBaseState::Enter();

	attackTime = 0.f;
	attackDelay = 5.f;;
	choiceAttack = 0;

	if (yggdrasil->GetPhaseUp())
	{
		yggdrasil->SetAnimeLeftHand("phase2HandLeftIdle", true);
		yggdrasil->SetAnimeRightHand("phase2HandRightIdle", true);
		yggdrasil->SetAnimeBody("yggdrasilPhase2Body", false);
		yggdrasil->SetAnimeHead("yggdrasilPhase2Head", false);
		yggdrasil->SetAnimeMouth("yggdrasilPhase2Mouth", false);
		yggdrasil->GetCollider()->SetActive(true);

		hStartPos = yggdrasil->GetHeadPos();
		hEndPos = { yggdrasil->GetHeadPos().x,  yggdrasil->GetPosition().y + 10.f };
		bStartPos = yggdrasil->GetPosition();
		bEndPos = { yggdrasil->GetPosition().x, yggdrasil->GetPosition().y + 10.f };
		mStartPos = yggdrasil->GetMouthPos();
		mEndPos = { yggdrasil->GetMouthPos().x, yggdrasil->GetPosition().y + 10.f };
	}
	else
	{
		yggdrasil->SetAnimeLeftHand("phase1HandLeftIdle", true);
		yggdrasil->SetAnimeRightHand("phase1HandRightIdle", true);
		yggdrasil->SetAnimeBody("yggdrasilPhase1Body", false);
		yggdrasil->SetAnimeHead("yggdrasilPhase1Head", false);
		yggdrasil->SetAnimeMouth("yggdrasilPhase1Mouth", false);

		hStartPos = yggdrasil->GetHeadPos();
		hEndPos = { yggdrasil->GetHeadPos().x,  yggdrasil->GetPosition().y + 10.f };
		bStartPos = yggdrasil->GetPosition();
		bEndPos = { yggdrasil->GetPosition().x, yggdrasil->GetPosition().y + 10.f };
		mStartPos = yggdrasil->GetMouthPos();
		mEndPos = { yggdrasil->GetMouthPos().x, yggdrasil->GetPosition().y + 10.f };
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
			attackTime = 0.f;
		}
		if (choiceAttack == 2)
		{
			fsm->ChangeState(YggdrasilStateType::SweepAttack);
			attackTime = 0.f;
		}
		if (choiceAttack == 3)
		{
			fsm->ChangeState(YggdrasilStateType::EnergyBallAttack);
			attackTime = 0.f;
		}
	}
	else
	{
		if (attackTime > attackDelay)
		{
			choiceAttack = Utils::RandomRange(1, 4);
			attackTime = 0;
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
}

void YggdrasilIdleState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilIdleState::YggdrasilIdleState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::Idle)
{
}
