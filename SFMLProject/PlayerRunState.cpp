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
	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Space) || (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Space) && InputManager::GetInstance().GetAxis(Axis::Jump) == 1.f))
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


	horizontal = InputManager::GetInstance().GetAxis(Axis::Horizontal);
	isLeftRun = horizontal > 0.f ? false : true;

	if((isLeftRun && !player->IsFlipX()) || (!isLeftRun && player->IsFlipX()))
		player->OnFlipX();
}

void PlayerRunState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerRunState::Update(float deltaTime)
{
	horizontal = InputManager::GetInstance().GetAxis(Axis::Horizontal);

	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Space) || (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Space) && InputManager::GetInstance().GetAxis(Axis::Jump) == 1.f))
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
		rigidbody->SetVelocity({ 0.f,rigidbody->GetCurrentVelocity().y });
	}
	else if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Right) && isLeftRun)
	{
		fsm->ChangeState(PlayerStateType::Break);
		return;
	}
	else if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Left) && !isLeftRun)
	{
		fsm->ChangeState(PlayerStateType::Break);
	}

	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Z))
	{
		player->Attack();
	}
}

void PlayerRunState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({InputManager::GetInstance().GetAxis(Axis::Horizontal) * player->GetSpeed() , rigidbody->GetCurrentVelocity().y});
}