#include "stdafx.h"
#include "SkeletonSpearRunState.h"
#include "Rigidbody.h"
#include "Animator.h"

SkeletonSpearRunState::SkeletonSpearRunState(SkeletonSpearFSM* fsm)
	: SkeletonSpearBaseState(fsm, SkeletonSpearStateType::Run)
	, rigidbody(nullptr)
	, horizontal(0.f)
	, isLeftRun(false)
{
	animationKeys.push_back("spearRun");
}

SkeletonSpearRunState::~SkeletonSpearRunState()
{
}


void SkeletonSpearRunState::Awake()
{
	SkeletonSpearBaseState::Awake();
}

void SkeletonSpearRunState::Start()
{
	rigidbody = skeletonSpear->GetRigidbody();

}
void SkeletonSpearRunState::Enter()
{
	SkeletonSpearBaseState::Enter();


	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], true);
}

void SkeletonSpearRunState::Exit()
{
	SkeletonSpearBaseState::Exit();
	horizontal = 0.f;
}

void SkeletonSpearRunState::Update(float deltaTime)
{
	InputMove();

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C) && skeletonSpear->GetCurrentJumpCount() > 0)
	{
		skeletonSpear->SetCurrentJumpCount(skeletonSpear->GetCurrentJumpCount() - 1);
		fsm->ChangeState(SkeletonSpearStateType::Jump);
		return;
	}


	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::X))
	{
		fsm->ChangeState(SkeletonSpearStateType::Attack);
		return;
	}

	if (horizontal == 0)
	{
		if (rigidbody->GetCurrentVelocity().y == 0.f)
		{
			fsm->ChangeState(SkeletonSpearStateType::Idle);
			rigidbody->SetVelocity({ 0.f, rigidbody->GetCurrentVelocity().y });
		}
	}

	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Z) && skeletonSpear->GetCurrentDashCount() > 0)
	{
		fsm->ChangeState(SkeletonSpearStateType::Dash);
	}
}

void SkeletonSpearRunState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ horizontal * skeletonSpear->GetSpeed() , rigidbody->GetCurrentVelocity().y });
}

void SkeletonSpearRunState::InputMove()
{
	horizontal = skeletonSpear->GetMoveDirection();

	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left) &&
		InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		fsm->ChangeState(SkeletonSpearStateType::Idle);
		return;
	}
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left))
	{
		horizontal = -1.f;
	}
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		horizontal = 1.f;
	}

	if (InputManager::GetInstance().GetKeyNone(sf::Keyboard::Left) && InputManager::GetInstance().GetKeyNone(sf::Keyboard::Right))
	{
		fsm->ChangeState(SkeletonSpearStateType::Idle);
		return;
	}


	if ((horizontal < 0.f && !skeletonSpear->IsFlipX()) || (horizontal > 0.f && skeletonSpear->IsFlipX()))
		skeletonSpear->OnFlipX();
	skeletonSpear->SetMoveDirection(horizontal);
}

void SkeletonSpearRunState::InputJump()
{
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C) && skeletonSpear->GetCurrentJumpCount() > 0)
	{
		fsm->ChangeState(SkeletonSpearStateType::Jump);
	}
}
