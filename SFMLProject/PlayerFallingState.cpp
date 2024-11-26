#include "stdafx.h"
#include "PlayerFallingState.h"
#include "Rigidbody.h"

void PlayerFallingState::Awake()
{
	PlayerBaseState::Awake();
}

void PlayerFallingState::Start()
{
	rigidbody = player->GetRigidbody();
	PlayerBaseState::Start();
}

void PlayerFallingState::Enter()
{
	PlayerBaseState::Enter();

}

void PlayerFallingState::Exit()
{
	horizontal = 0.f;
	PlayerBaseState::Exit();
}

void PlayerFallingState::Update(float deltaTime)
{
	horizontal = player->GetMoveDirection();

	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left) &&
		InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		horizontal = 0.f;
	}
	else if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left))
	{
		if (horizontal != -1.f)
			player->OnFlipX();
		horizontal = -1.f;
	}
	else if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		if (horizontal != 1.f)
			player->OnFlipX();
		horizontal = 1.f;
	}
	else
		horizontal = 0.f;
	player->SetMoveDirection(horizontal);

	
	if (rigidbody->IsGround())
	{
		fsm->ChangeState(PlayerStateType::Idle);
		player->SetCurrentJumpCount(player->GetJumpCount());
	}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C) && rigidbody->IsGround() == false && player->GetCurrentJumpCount() > 0)
	{
		player->SetCurrentJumpCount(player->GetCurrentJumpCount() - 1);
		fsm->ChangeState(PlayerStateType::Jump);
	}
	if ((horizontal < 0.f && !player->IsFlipX()) || (horizontal > 0.f && player->IsFlipX()))
	{
		player->OnFlipX();
	}
	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Z) && player->GetCurrentDashCount() > 0);
	{
		player->OnDash();
		fsm->ChangeState(PlayerStateType::Dash);
	}
	PlayerBaseState::Update(deltaTime);
}

void PlayerFallingState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ horizontal * player->GetSpeed() , rigidbody->GetCurrentVelocity().y });
	PlayerBaseState::FixedUpdate(fixedDeltaTime);
}

void PlayerFallingState::LateUpdate(float deltaTime)
{
	PlayerBaseState::LateUpdate(deltaTime);
}

PlayerFallingState::PlayerFallingState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Falling)
{
}

PlayerFallingState::~PlayerFallingState()
{
}
