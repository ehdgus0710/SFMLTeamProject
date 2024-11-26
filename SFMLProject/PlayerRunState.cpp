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
}

PlayerRunState::~PlayerRunState()
{
}


void PlayerRunState::InputMove()
{
}

void PlayerRunState::InputJump()
{
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Space))
	{
		fsm->ChangeState(PlayerStateType::Jump);
	}
}

void PlayerRunState::Awake()
{
}

void PlayerRunState::Start()
{
	rigidbody = player->GetRigidbody();

}
void PlayerRunState::Enter()
{
	PlayerBaseState::Enter();

	// animator->ChangeAnimation(animationKeys[animationKeyIndex], true);


	//horizontal = InputManager::GetInstance().GetAxis(Axis::Horizontal);
	//isLeftRun = horizontal > 0.f ? false : true;


	if((isLeftRun && !player->IsFlipX()) || (!isLeftRun && player->IsFlipX()))
		player->OnFlipX();
}

void PlayerRunState::Exit()
{
	PlayerBaseState::Exit();
	horizontal = 0.f;
}

void PlayerRunState::Update(float deltaTime)
{
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left))
	{
		horizontal = -1.f;
	}
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		horizontal = 1.f;
	}
	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Left) || 
		InputManager::GetInstance().GetKeyUp(sf::Keyboard::Right))
	{
		horizontal = 0.f;
	}
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C))
	{
		if (rigidbody->IsGround())
		{
			fsm->ChangeState(PlayerStateType::Jump);
			return;
		}
	}

	if (horizontal == 0)
	{
		fsm->ChangeState(PlayerStateType::Idle);
		rigidbody->SetVelocity({ 0.f, rigidbody->GetCurrentVelocity().y });
	}

	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Z))
	{
		player->Attack();
	}
}

void PlayerRunState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ horizontal * player->GetSpeed() , rigidbody->GetCurrentVelocity().y});
}