#include "stdafx.h"
#include "SkeletonSpearSkill1State.h"
#include "Rigidbody.h"
#include "Animator.h"


SkeletonSpearSkill1State::SkeletonSpearSkill1State(SkeletonSpearFSM* fsm)
	: SkeletonSpearBaseState(fsm, SkeletonSpearStateType::Skill1)
	, isExtraDash(false)
	, dashTime(0.3f)
	, currentTime(0.f)
	, rigidbody(nullptr)
{
	animationKeys.push_back("littleboneDash");
	animationKeys.push_back("noheadlittleboneDash");
}

SkeletonSpearSkill1State::~SkeletonSpearSkill1State()
{
}

void SkeletonSpearSkill1State::StartDash()
{
	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], false);
	dashEndPos = skeletonSpear->GetPosition() + (skeletonSpear->IsFlipX() ? sf::Vector2f::left : sf::Vector2f::right) * 600.f;
	dashStartPos = skeletonSpear->GetPosition();
	skeletonSpear->OnDash();
	currentTime = 0.f;
}

void SkeletonSpearSkill1State::Start()
{
	rigidbody = skeletonSpear->GetRigidbody();
}

void SkeletonSpearSkill1State::Enter()
{
	SkeletonSpearBaseState::Enter();
	rigidbody->ResetDropSpeed();
	rigidbody->ResetVelocity();
	rigidbody->Disable();
	isExtraDash = false;
	StartDash();
}

void SkeletonSpearSkill1State::Exit()
{
	rigidbody->SetActive(true);
	SkeletonSpearBaseState::Exit();
}

void SkeletonSpearSkill1State::Update(float deltaTime)
{
	SkeletonSpearBaseState::Update(deltaTime);
	currentTime += deltaTime;
	skeletonSpear->SetPosition(sf::Vector2f::Lerp(dashStartPos, dashEndPos, currentTime / dashTime));

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Z))
		isExtraDash = true;

	if (currentTime >= dashTime + 0.1f)
	{
		if (isExtraDash && skeletonSpear->GetCurrentDashCount() > 0)
		{
			StartDash();
		}
		else
		{
			if (rigidbody->IsGround())
				fsm->ChangeState(SkeletonSpearStateType::Idle);
			else
				fsm->ChangeState(SkeletonSpearStateType::Falling);
		}
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C) && skeletonSpear->GetCurrentJumpCount() > 0)
	{
		skeletonSpear->SetCurrentJumpCount(skeletonSpear->GetCurrentJumpCount() - 1);
		fsm->ChangeState(SkeletonSpearStateType::Jump);
	}
}