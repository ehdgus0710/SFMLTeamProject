#include "stdafx.h"
#include "PlayerJumpState.h"
#include "Rigidbody.h"
#include "Animator.h"

PlayerJumpState::PlayerJumpState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Jump)
{
	animationKeys.push_back("marioSmallJump");
	animationKeys.push_back("marioJump");
	animationKeys.push_back("marioFireJump");
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
	
	animationKeyIndex = player->GetCurrentHP() - 1;
	player->GetAnimator()->ChangeAnimation(animationKeys[animationKeyIndex], true);

	player->SetIsJump(true);
	rigidbody->SetGround(false);

	if(animationKeyIndex == 0)
		SoundManger::GetInstance().PlaySfx("SmallJump");
	else
		SoundManger::GetInstance().PlaySfx("BigJump");


	if(InputManager::GetInstance().GetAxis(Axis::Jump) == 1.f)
		rigidbody->SetVelocity({ rigidbody->GetCurrentVelocity().x, -850.f });
	else
		rigidbody->SetVelocity({ rigidbody->GetCurrentVelocity().x, -500.f });

	if(player->IsRun())
		rigidbody->AddVelocity(sf::Vector2f::up * 100.f);
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