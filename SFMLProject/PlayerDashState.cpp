#include "stdafx.h"
#include "PlayerDashState.h"
#include "Rigidbody.h"
#include "Animator.h"


PlayerDashState::PlayerDashState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Dash)
	, isExtraDash(false)
	, dashTime(0.3f)
	, currentTime(0.f)
	, rigidbody(nullptr)
{
	animationKeys.push_back("littleboneDash");
	animationKeys.push_back("noheadlittleboneDash");
}

PlayerDashState::~PlayerDashState()
{
}

void PlayerDashState::StartDash()
{
	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], false);
	dashEndPos = player->GetPosition() + (player->IsFlipX() ? sf::Vector2f::left : sf::Vector2f::right) * 400.f;
	dashStartPos = player->GetPosition();
	player->OnDash();
	currentTime = 0.f;
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
	isExtraDash = false;
	StartDash();
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
		isExtraDash = true;

	if (currentTime >= dashTime + 0.1f)
	{
		if (isExtraDash && player->GetCurrentDashCount() > 0)
		{
			StartDash();
		}
		else
		{
			if(rigidbody->IsGround())
				fsm->ChangeState(PlayerStateType::Idle);
			else
				fsm->ChangeState(PlayerStateType::Falling);
		}
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C) && player->GetCurrentJumpCount() > 0)
	{
		player->SetCurrentJumpCount(player->GetCurrentJumpCount() - 1);
		fsm->ChangeState(PlayerStateType::Jump);
	}
}