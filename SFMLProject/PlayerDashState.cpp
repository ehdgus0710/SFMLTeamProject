#include "stdafx.h"
#include "PlayerDashState.h"
#include "Rigidbody.h"

PlayerDashState::PlayerDashState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Dash)
	, extraDash(false)
	, dashCount(0)
{
}

PlayerDashState::~PlayerDashState()
{
}

void PlayerDashState::Awake()
{
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
	dashTime = 0.5f;
	currentTime = 0.f;

	dashEndPos = player->GetPosition() + (player->IsFlipX() ? sf::Vector2f::left : sf::Vector2f::right) * 500.f;
	dashStartPos = player->GetPosition();
	dashCount = 1;

	player->OnDash();

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

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Z))
	{
		extraDash = true;
	}

	if (currentTime >= dashTime)
	{
		if (extraDash && dashCount == 1)
		{
			dashEndPos = player->GetPosition() + (player->IsFlipX() ? sf::Vector2f::left : sf::Vector2f::right) * 500.f;
			dashStartPos = player->GetPosition();
			currentTime = 0.f;
			++dashCount;
			extraDash = false;
		}
		else
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
