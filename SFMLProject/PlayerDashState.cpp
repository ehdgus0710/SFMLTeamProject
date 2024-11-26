#include "stdafx.h"
#include "PlayerDashState.h"
#include "Rigidbody.h"

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
	currenttime = 0.f;

	dashEndPos = player->GetPosition() + (player->IsFlipX() ? sf::Vector2f::left : sf::Vector2f::right) * 500.f;
	dashStartPos = player->GetPosition();

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
	currenttime += deltaTime;
	player->SetPosition(sf::Vector2f::Lerp(dashStartPos, dashEndPos, currenttime / dashTime));

	if (currenttime >= dashTime)
	{
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
{
}

PlayerDashState::~PlayerDashState()
{
}
