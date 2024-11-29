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


void PlayerRunState::InputMove()
{
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

	if ((horizontal < 0.f && !player->IsFlipX()) || (horizontal > 0.f && player->IsFlipX()))
		player->OnFlipX();
	player->SetMoveDirection(horizontal);
}

void PlayerRunState::InputJump()
{
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C) && player->GetCurrentJumpCount() > 0)
	{
		fsm->ChangeState(PlayerStateType::Jump);
	}
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

	animator->ChangeAnimation(animationKeys[currentAnimationIndex], true);

	// animator->ChangeAnimation(animationKeys[animationKeyIndex], true);


	//horizontal = InputManager::GetInstance().GetAxis(Axis::Horizontal);
	//isLeftRun = horizontal > 0.f ? false : true;


	if ((isLeftRun && !player->IsFlipX()) || (!isLeftRun && player->IsFlipX()))
		player->OnFlipX();
}

void PlayerRunState::Exit()
{
	PlayerBaseState::Exit();
	horizontal = 0.f;
}

void PlayerRunState::Update(float deltaTime)
{
	InputMove();

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C) && player->GetCurrentJumpCount() > 0)
	{
		player->SetCurrentJumpCount(player->GetCurrentJumpCount() - 1);

		fsm->ChangeState(PlayerStateType::Jump);
	}

	if (horizontal == 0)
	{
		if (rigidbody->GetCurrentVelocity().y == 0.f)
		{
			fsm->ChangeState(PlayerStateType::Idle);
			rigidbody->SetVelocity({ 0.f, rigidbody->GetCurrentVelocity().y });
		}
	}

	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Z) && player->GetCurrentDashCount() > 0)
	{
		fsm->ChangeState(PlayerStateType::Dash);
	}
}

void PlayerRunState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ horizontal * player->GetSpeed() , rigidbody->GetCurrentVelocity().y});
}