#include "stdafx.h"
#include "PlayerFallingState.h"
#include "Rigidbody.h"
#include "Animator.h"


PlayerFallingState::PlayerFallingState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Falling)
{
	animationKeys.push_back("littleboneFalling");
	animationKeys.push_back("noheadlittleboneFalling");
}

PlayerFallingState::~PlayerFallingState()
{
}

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
	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], false);
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

	if (KeyActionManager::GetInstance().GetKeyDown(KeyActionType::Jump) && player->GetCurrentJumpCount() > 0)
	{
		player->SetCurrentJumpCount(player->GetCurrentJumpCount() - 1);
		fsm->ChangeState(PlayerStateType::Jump);
	}

	if ((horizontal < 0.f && !player->IsFlipX()) || (horizontal > 0.f && player->IsFlipX()))
	{
		player->OnFlipX();
	}

	if (KeyActionManager::GetInstance().GetKeyDown(KeyActionType::Dash) && player->GetCurrentDashCount() > 0)
	{
		fsm->ChangeState(PlayerStateType::Dash);
	}

	if (KeyActionManager::GetInstance().GetKeyDown(KeyActionType::Attack))
	{
		fsm->ChangeState(PlayerStateType::JumpAttack);
		return;
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