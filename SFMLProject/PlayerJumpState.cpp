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
}

void PlayerJumpState::Start()
{
	rigidbody = player->GetRigidbody();
}

void PlayerJumpState::Enter()
{
	PlayerBaseState::Enter();	
	
	// player->GetAnimator()->ChangeAnimation(animationKeys[animationKeyIndex], true);

	player->SetIsJump(true);
	rigidbody->SetGround(false);

	if(InputManager::GetInstance().GetAxis(Axis::Jump) == 1.f)
		rigidbody->SetVelocity({ rigidbody->GetCurrentVelocity().x, -850.f });
	else
		rigidbody->SetVelocity({ rigidbody->GetCurrentVelocity().x, -500.f });
}

void PlayerJumpState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerJumpState::Update(float deltaTime)
{
	if (rigidbody->IsGround())
	{
		fsm->ChangeState(PlayerStateType::Idle);
		return;
	}
	float horizontal = InputManager::GetInstance().GetAxis(Axis::Horizontal);
	if ((horizontal < 0.f && !player->IsFlipX()) || (horizontal > 0.f && player->IsFlipX()))
		player->OnFlipX();

	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Z))
	{
		player->Attack();
	}
}

void PlayerJumpState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ InputManager::GetInstance().GetAxis(Axis::Horizontal) * player->GetSpeed() , rigidbody->GetCurrentVelocity().y });
}