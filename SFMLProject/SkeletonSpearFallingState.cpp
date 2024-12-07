#include "stdafx.h"
#include "SkeletonSpearFallingState.h"
#include "Rigidbody.h"
#include "Animator.h"


SkeletonSpearFallingState::SkeletonSpearFallingState(SkeletonSpearFSM* fsm)
	: SkeletonSpearBaseState(fsm, SkeletonSpearStateType::Falling)
{
	animationKeys.push_back("spearFalling");
}

SkeletonSpearFallingState::~SkeletonSpearFallingState()
{
}

void SkeletonSpearFallingState::Awake()
{
	SkeletonSpearBaseState::Awake();
}

void SkeletonSpearFallingState::Start()
{
	rigidbody = skeletonSpear->GetRigidbody();
	SkeletonSpearBaseState::Start();
}

void SkeletonSpearFallingState::Enter()
{
	SkeletonSpearBaseState::Enter();
	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], false);
}

void SkeletonSpearFallingState::Exit()
{
	horizontal = 0.f;
	SkeletonSpearBaseState::Exit();
}

void SkeletonSpearFallingState::Update(float deltaTime)
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
	}
	else if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		if (horizontal != 1.f)
			skeletonSpear->OnFlipX();
		horizontal = 1.f;
	}
	else
		horizontal = 0.f;
	skeletonSpear->SetMoveDirection(horizontal);


	if (rigidbody->IsGround())
	{
		fsm->ChangeState(SkeletonSpearStateType::Idle);
		skeletonSpear->SetCurrentJumpCount(skeletonSpear->GetJumpCount());
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C) && skeletonSpear->GetCurrentJumpCount() > 0)
	{
		skeletonSpear->SetCurrentJumpCount(skeletonSpear->GetCurrentJumpCount() - 1);
		fsm->ChangeState(SkeletonSpearStateType::Jump);
	}

	if ((horizontal < 0.f && !skeletonSpear->IsFlipX()) || (horizontal > 0.f && skeletonSpear->IsFlipX()))
	{
		skeletonSpear->OnFlipX();
	}

	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Z) && skeletonSpear->GetCurrentDashCount() > 0)
	{
		fsm->ChangeState(SkeletonSpearStateType::Dash);
	}

	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::X))
	{
		fsm->ChangeState(SkeletonSpearStateType::JumpAttack);
		return;
	}

	SkeletonSpearBaseState::Update(deltaTime);
}

void SkeletonSpearFallingState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ horizontal * skeletonSpear->GetSpeed() , rigidbody->GetCurrentVelocity().y });
	SkeletonSpearBaseState::FixedUpdate(fixedDeltaTime);
}

void SkeletonSpearFallingState::LateUpdate(float deltaTime)
{
	SkeletonSpearBaseState::LateUpdate(deltaTime);
}