#include "stdafx.h"
#include "SkeletonSpearIdleState.h"
#include "Animator.h"
#include "Rigidbody.h"

SkeletonSpearIdleState::SkeletonSpearIdleState(SkeletonSpearFSM* fsm)
	: SkeletonSpearBaseState(fsm, SkeletonSpearStateType::Idle)
{
	animationKeys.push_back("littleboneIdle");
	animationKeys.push_back("noheadlittleboneIdle");
}

SkeletonSpearIdleState::~SkeletonSpearIdleState()
{
}

void SkeletonSpearIdleState::Awake()
{
	SkeletonSpearBaseState::Awake();
}

void SkeletonSpearIdleState::Start()
{
	rigidbody = skeletonSpear->GetRigidbody();
}

void SkeletonSpearIdleState::Enter()
{
	SkeletonSpearBaseState::Enter();
	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], true);
}

void SkeletonSpearIdleState::Exit()
{
	SkeletonSpearBaseState::Exit();
}

void SkeletonSpearIdleState::Update(float deltaTime)
{
	horizontal = skeletonSpear->GetMoveDirection();

	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left) &&
		InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		horizontal = 0.f;
	}
	else if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left))
	{
		if (horizontal != -1.f)
			skeletonSpear->OnFlipX();
		horizontal = -1.f;
		fsm->ChangeState(SkeletonSpearStateType::Run);
	}
	else if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		if (horizontal != 1.f)
			skeletonSpear->OnFlipX();
		horizontal = 1.f;
		fsm->ChangeState(SkeletonSpearStateType::Run);
	}
	else
		horizontal = 0.f;
	skeletonSpear->SetMoveDirection(horizontal);

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::X))
	{
		fsm->ChangeState(SkeletonSpearStateType::Attack);
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C))
	{
		if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Down))
			skeletonSpear->OnDownJump();
		else if (skeletonSpear->GetCurrentJumpCount() > 0)
		{
			fsm->ChangeState(SkeletonSpearStateType::Jump);
		}
	}



	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Z) && skeletonSpear->GetCurrentDashCount() > 0)
	{
		fsm->ChangeState(SkeletonSpearStateType::Dash);
	}


}

void SkeletonSpearIdleState::FixedUpdate(float fixedDeltaTime)
{
}

void SkeletonSpearIdleState::LateUpdate(float deltaTime)
{
}
