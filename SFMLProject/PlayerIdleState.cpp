#include "stdafx.h"
#include "PlayerIdleState.h"
#include "Animator.h"
#include "Rigidbody.h"

PlayerIdleState::PlayerIdleState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Idle)
{
}

PlayerIdleState::~PlayerIdleState()
{
}

void PlayerIdleState::Awake()
{
}

void PlayerIdleState::Start()
{
	rigidbody = player->GetRigidbody();
}

void PlayerIdleState::Enter()
{
	PlayerBaseState::Enter();
	// player->GetAnimator()->ChangeAnimation(animationKeys[animationKeyIndex], true);
}

void PlayerIdleState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerIdleState::Update(float deltaTime)
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
		fsm->ChangeState(PlayerStateType::Run);
	}
	else if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		if (horizontal != 1.f)
			player->OnFlipX();
		horizontal = 1.f;
		fsm->ChangeState(PlayerStateType::Run);
	}
	else
		horizontal = 0.f;
	player->SetMoveDirection(horizontal);

	if ((InputManager::GetInstance().GetKeyDown(sf::Keyboard::C) || (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::C) && InputManager::GetInstance().GetAxis(Axis::Jump) == 1.f)))
	{
		player->SetCurrentJumpCount(player->GetCurrentJumpCount() - 1);
		fsm->ChangeState(PlayerStateType::Jump);
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Z) && player->GetCurrentDashCount() > 0)
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
