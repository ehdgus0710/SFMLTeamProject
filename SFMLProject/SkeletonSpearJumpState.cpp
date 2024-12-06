#include "stdafx.h"
#include "SkeletonSpearJumpState.h"
#include "Rigidbody.h"
#include "Animator.h"

SkeletonSpearJumpState::SkeletonSpearJumpState(SkeletonSpearFSM* fsm)
	: SkeletonSpearBaseState(fsm, SkeletonSpearStateType::Jump)
{
	animationKeys.push_back("littleboneJump");
	animationKeys.push_back("noheadlittleboneJump");
}

SkeletonSpearJumpState::~SkeletonSpearJumpState()
{
}

void SkeletonSpearJumpState::Awake()
{
	SkeletonSpearBaseState::Awake();
}

void SkeletonSpearJumpState::Start()
{
	rigidbody = skeletonSpear->GetRigidbody();
}

void SkeletonSpearJumpState::Enter()
{
	SkeletonSpearBaseState::Enter();

	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], false);

	skeletonSpear->SetIsJump(true);
	rigidbody->SetGround(false);
	rigidbody->ResetDropSpeed();
	rigidbody->SetVelocity({ rigidbody->GetCurrentVelocity().x, -800.f });
}

void SkeletonSpearJumpState::Exit()
{
	SkeletonSpearBaseState::Exit();
	horizontal = 0.f;
}

void SkeletonSpearJumpState::Update(float deltaTime)
{
	if (rigidbody->IsGround())
	{
		fsm->ChangeState(SkeletonSpearStateType::Idle);
		return;
	}
	horizontal = skeletonSpear->GetMoveDirection();

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
	skeletonSpear->SetMoveDirection(horizontal);

	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Z) && skeletonSpear->GetCurrentDashCount() > 0)
	{
		fsm->ChangeState(SkeletonSpearStateType::Dash);
		return;
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C) && skeletonSpear->GetCurrentJumpCount() > 0)
	{
		skeletonSpear->SetCurrentJumpCount(skeletonSpear->GetCurrentJumpCount() - 1);
		fsm->ChangeState(SkeletonSpearStateType::Jump);
		return;
	}
	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::X))
	{
		fsm->ChangeState(SkeletonSpearStateType::JumpAttack);
		return;
	}

	if ((horizontal < 0.f && !skeletonSpear->IsFlipX()) || (horizontal > 0.f && skeletonSpear->IsFlipX()))
		skeletonSpear->OnFlipX();
}

void SkeletonSpearJumpState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ horizontal * skeletonSpear->GetSpeed() , rigidbody->GetCurrentVelocity().y });
}