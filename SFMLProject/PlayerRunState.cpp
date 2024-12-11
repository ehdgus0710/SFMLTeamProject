#include "stdafx.h"
#include "PlayerRunState.h"
#include "Rigidbody.h"
#include "Animator.h"

PlayerRunState::PlayerRunState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Run)
	, rigidbody(nullptr)
	, horizontal(0.f)
	, isLeftRun(false)
{
	animationKeys.push_back("littleboneRun");
	animationKeys.push_back("noheadlittleboneRun");
}

PlayerRunState::~PlayerRunState()
{
}


void PlayerRunState::Awake()
{
	PlayerBaseState::Awake();
}

void PlayerRunState::Start()
{
	rigidbody = player->GetRigidbody();

}
void PlayerRunState::Enter()
{
	PlayerBaseState::Enter();


	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], true);
}

void PlayerRunState::Exit()
{
	PlayerBaseState::Exit();
	horizontal = 0.f;
}

void PlayerRunState::Update(float deltaTime)
{
	InputMove();

	if (KeyActionManager::GetInstance().GetKeyDown(KeyActionType::Jump) && player->GetCurrentJumpCount() > 0)
	{
		player->SetCurrentJumpCount(player->GetCurrentJumpCount() - 1);
		fsm->ChangeState(PlayerStateType::Jump);
		return;
	}


	if (KeyActionManager::GetInstance().GetKeyDown(KeyActionType::Attack))
	{
		fsm->ChangeState(PlayerStateType::Attack);
		return;
	}

	if (horizontal == 0)
	{
		if (rigidbody->GetCurrentVelocity().y == 0.f)
		{
			fsm->ChangeState(PlayerStateType::Idle);
			rigidbody->SetVelocity({ 0.f, rigidbody->GetCurrentVelocity().y });
		}
	}

	if (KeyActionManager::GetInstance().GetKeyUp(KeyActionType::Dash) && player->GetCurrentDashCount() > 0)
	{
		fsm->ChangeState(PlayerStateType::Dash);
	}
}

void PlayerRunState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ horizontal * player->GetSpeed() , rigidbody->GetCurrentVelocity().y});
}

void PlayerRunState::InputMove()
{
	horizontal = player->GetMoveDirection();

	if (KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::LeftMove) &&
		KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::RightMove))
	{
		fsm->ChangeState(PlayerStateType::Idle);
		return;
	}
	if (KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::LeftMove))
	{
		horizontal = -1.f;
	}
	if (KeyActionManager::GetInstance().GetKeyPressed(KeyActionType::RightMove))
	{
		horizontal = 1.f;
	}

	if (KeyActionManager::GetInstance().GetKeyNone(KeyActionType::LeftMove) && KeyActionManager::GetInstance().GetKeyNone(KeyActionType::RightMove))
	{
		fsm->ChangeState(PlayerStateType::Idle);
		return;
	}


	if ((horizontal < 0.f && !player->IsFlipX()) || (horizontal > 0.f && player->IsFlipX()))
		player->OnFlipX();
	player->SetMoveDirection(horizontal);
}

void PlayerRunState::InputJump()
{
	if (KeyActionManager::GetInstance().GetKeyDown(KeyActionType::Jump) && player->GetCurrentJumpCount() > 0)
	{
		fsm->ChangeState(PlayerStateType::Jump);
	}
}
