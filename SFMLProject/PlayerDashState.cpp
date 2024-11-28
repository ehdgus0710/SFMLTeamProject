#include "stdafx.h"
#include "PlayerDashState.h"
#include "Rigidbody.h"
#include "Animator.h"

void PlayerDashState::Awake()
{
	PlayerBaseState::Awake();
}

void PlayerDashState::Start()
{
	rigidbody = player->GetRigidbody();
}

void PlayerDashState::Enter()
{
	PlayerBaseState::Enter();
	rigidbody->ResetDropSpeed();
	rigidbody->ResetVelocity();
	rigidbody->Disable();
	dashTime = 0.3f;
	currentTime = 0.f;
	player->OnDash();

	animator->ChangeAnimation("noheadlittleboneDash", false);

	dashEndPos = player->GetPosition() + (player->IsFlipX() ? sf::Vector2f::left : sf::Vector2f::right) * 400.f;
	dashStartPos = player->GetPosition();

	

}

void PlayerDashState::Exit()
{
	rigidbody->SetActive(true);
	PlayerBaseState::Exit();
}

void PlayerDashState::Update(float deltaTime)
{
 	PlayerBaseState::Update(deltaTime);
	currentTime += deltaTime;
	player->SetPosition(sf::Vector2f::Lerp(dashStartPos, dashEndPos, currentTime / dashTime));
	if (currentTime <= dashTime)
	{
		if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Z) && player->GetCurrentDashCount() > 0)
		{
			dashEndPos = player->GetPosition() + (player->IsFlipX() ? sf::Vector2f::left : sf::Vector2f::right) * 400.f;
			dashStartPos = player->GetPosition();
			currentTime = 0.f;
			player->OnDash();
		}
	}
	else
	{
		player->OnDash();
		fsm->ChangeState(PlayerStateType::Idle);
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C) && player->GetCurrentJumpCount() > 0)
	{
		player->SetCurrentJumpCount(player->GetCurrentJumpCount() - 1);
		fsm->ChangeState(PlayerStateType::Jump);
	}
}

void PlayerDashState::FixedUpdate(float fixedDeltaTime)
{
	PlayerBaseState::FixedUpdate(fixedDeltaTime);
}

PlayerDashState::PlayerDashState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Dash)
	, extraDash(false)
{
}

PlayerDashState::~PlayerDashState()
{
}
