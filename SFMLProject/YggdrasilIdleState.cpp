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
		yggdrasil->SetAnimeLeftHand("phase2HandLeftIdle", true);
		yggdrasil->SetAnimeRightHand("phase2HandRightIdle", true);
	}
	else
	{
		yggdrasil->SetAnimeLeftHand("phase1HandLeftIdle", true);
		yggdrasil->SetAnimeRightHand("phase1HandRightIdle", true);
	}
}

void YggdrasilIdleState::Exit()
{
}

void YggdrasilIdleState::Update(float deltaTime)
{
	if (yggdrasil->GetPhaseUp() && !changeOn)
	{
		Enter();
		changeOn = true;
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad7))
	{
		fsm->ChangeState(YggdrasilStateType::FistAttack);
	}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad8))
	{
		fsm->ChangeState(YggdrasilStateType::SweepAttack);
	}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad9))
	{
		fsm->ChangeState(YggdrasilStateType::EnergyBallAttack);
	}
}

void YggdrasilIdleState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilIdleState::YggdrasilIdleState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::Idle)
{
}
