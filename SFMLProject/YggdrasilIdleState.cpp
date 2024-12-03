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
}

void YggdrasilIdleState::Enter()
{
	YggdrasilBaseState::Enter();
	if (yggdrasil->GetPhaseUp())
	{
		attackTime = 0.f;
		attackDelay = 5.f;
		choiceAttack = 0;
		yggdrasil->SetAnimeLeftHand("phase2HandLeftIdle", true);
		yggdrasil->SetAnimeRightHand("phase2HandRightIdle", true);
	}
	else
	{
		attackTime = 0.f;
		attackDelay = 2.5f;
		choiceAttack = 0;
		yggdrasil->SetAnimeLeftHand("phase1HandLeftIdle", true);
		yggdrasil->SetAnimeRightHand("phase1HandRightIdle", true);
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
	
	//if (attackTime > attackDelay)
	//{
	//	choiceAttack = Utils::RandomRange(1, 3);
	//	attackTime = 0;
	//}
	//if (choiceAttack == 1)
	//{
	//	fsm->ChangeState(YggdrasilStateType::FistAttack);
	//}
	//if (choiceAttack == 2)
	//{
	//	fsm->ChangeState(YggdrasilStateType::SweepAttack);
	//}
	//if (choiceAttack == 3)
	//{
	//	fsm->ChangeState(YggdrasilStateType::EnergyBallAttack);
	//}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad8))
	{
		fsm->ChangeState(YggdrasilStateType::YggdrasilSpecialAttack);
	}
}

void YggdrasilIdleState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilIdleState::YggdrasilIdleState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::Idle)
{
}
