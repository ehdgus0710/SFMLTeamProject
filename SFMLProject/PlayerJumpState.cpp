#include "stdafx.h"
#include "PlayerJumpState.h"
#include "Rigidbody.h"
#include "Animator.h"

PlayerJumpState::PlayerJumpState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Jump)
{
}

PlayerJumpState::~PlayerJumpState()
{
}

void PlayerJumpState::Awake()
{
	PlayerBaseState::Awake();
}

void PlayerJumpState::Start()
{
	rigidbody = player->GetRigidbody();
}

void PlayerJumpState::Enter()
{
	PlayerBaseState::Enter();

	animator->ChangeAnimation("noheadlittleboneJump", false);

	player->SetIsJump(true);
	rigidbody->SetGround(false);
	rigidbody->ResetDropSpeed();
	rigidbody->SetVelocity({ rigidbody->GetCurrentVelocity().x, -800.f });
}

void PlayerJumpState::Exit()
{
	PlayerBaseState::Exit();
	horizontal = 0.f;
}

void PlayerJumpState::Update(float deltaTime)
{
	if (rigidbody->IsGround())
	{
		fsm->ChangeState(PlayerStateType::Idle);
		return;
	}
	horizontal = player->GetMoveDirection();

	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left) &&
		InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		horizontal = 0.f;
	}
	else if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left))
	{
		horizontal = -1.f;
	}
	else if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		horizontal = 1.f;
	}
	else
		horizontal = 0.f;
	player->SetMoveDirection(horizontal);

	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Z) && player->GetCurrentDashCount() > 0)
	{
		fsm->ChangeState(PlayerStateType::Dash);
	}
	//if (player->IsJump())
	//{
	//}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C) && player->GetCurrentJumpCount() > 0)
	{
		player->SetCurrentJumpCount(player->GetCurrentJumpCount() - 1);
		fsm->ChangeState(PlayerStateType::Jump);
	}


	if ((horizontal < 0.f && !player->IsFlipX()) || (horizontal > 0.f && player->IsFlipX()))
		player->OnFlipX();
}

void PlayerJumpState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ horizontal * player->GetSpeed() , rigidbody->GetCurrentVelocity().y });
}