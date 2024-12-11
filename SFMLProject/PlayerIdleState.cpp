#include "stdafx.h"
#include "PlayerIdleState.h"
#include "Animator.h"
#include "Rigidbody.h"

PlayerIdleState::PlayerIdleState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Idle)
{
	animationKeys.push_back("littleboneIdle");
	animationKeys.push_back("noheadlittleboneIdle");
}

PlayerIdleState::~PlayerIdleState()
{
}

void PlayerIdleState::Awake()
{
	PlayerBaseState::Awake();
}

void PlayerIdleState::Start()
{
	rigidbody = player->GetRigidbody();
}

void PlayerIdleState::Enter()
{
	PlayerBaseState::Enter();
	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], true);
}

void PlayerIdleState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerIdleState::Update(float deltaTime)
{
	horizontal = player->GetMoveDirection();

	if (KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::LeftMove) &&
		KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::RightMove))
	{
		horizontal = 0.f;
	}
	else if (KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::LeftMove))
	{
		if (horizontal != -1.f)
			player->OnFlipX();
		horizontal = -1.f;
		fsm->ChangeState(PlayerStateType::Run);
	}
	else if (KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::RightMove))
	{
		if (horizontal != 1.f)
			player->OnFlipX();
		horizontal = 1.f;
		fsm->ChangeState(PlayerStateType::Run);
	}
	else
		horizontal = 0.f;
	player->SetMoveDirection(horizontal);

	if (KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::Attack))
	{
		fsm->ChangeState(PlayerStateType::Attack);
	}

	if (KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::Jump))
	{
		if (KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::Down))
			player->OnDownJump();
		else if (player->GetCurrentJumpCount() > 0)
		{
			fsm->ChangeState(PlayerStateType::Jump);
		}
	}

	

	if (KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::Dash) && player->GetCurrentDashCount() > 0)
	{
		fsm->ChangeState(PlayerStateType::Dash);
	}
	
	
}

void PlayerIdleState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerIdleState::LateUpdate(float deltaTime)
{
}
