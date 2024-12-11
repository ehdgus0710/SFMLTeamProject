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

	if (KeyActionManager::GetInstance().GetKeyDown(ActionKeyType::Jump) && player->GetCurrentJumpCount() > 0)
	{
		player->SetCurrentJumpCount(player->GetCurrentJumpCount() - 1);
		fsm->ChangeState(PlayerStateType::Jump);
		return;
	}


	if (KeyActionManager::GetInstance().GetKeyDown(ActionKeyType::Attack))
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

	if (KeyActionManager::GetInstance().GetKeyUp(ActionKeyType::Dash) && player->GetCurrentDashCount() > 0)
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

	if (KeyActionManager::GetInstance().GetKeyPressed(ActionKeyType::LeftMove) &&
		KeyActionManager::GetInstance().GetKeyPressed(ActionKeyType::RightMove))
	{
		fsm->ChangeState(PlayerStateType::Idle);
		return;
	}
	if (KeyActionManager::GetInstance().GetKeyPressed(ActionKeyType::LeftMove))
	{
		horizontal = -1.f;
	}
	if (KeyActionManager::GetInstance().GetKeyPressed(ActionKeyType::RightMove))
	{
		horizontal = 1.f;
	}

	if (KeyActionManager::GetInstance().GetKeyNone(ActionKeyType::LeftMove) && KeyActionManager::GetInstance().GetKeyNone(ActionKeyType::RightMove))
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
	if (KeyActionManager::GetInstance().GetKeyDown(ActionKeyType::Jump) && player->GetCurrentJumpCount() > 0)
	{
		fsm->ChangeState(PlayerStateType::Jump);
	}
}
