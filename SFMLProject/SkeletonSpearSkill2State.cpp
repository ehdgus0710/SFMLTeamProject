#include "stdafx.h"
#include "SkeletonSpearSkill2State.h"
#include "Rigidbody.h"
#include "Animator.h"


SkeletonSpearSkill2State::SkeletonSpearSkill2State(SkeletonSpearFSM* fsm)
	: SkeletonSpearBaseState(fsm, SkeletonSpearStateType::Skill2)
	, isExtraDash(false)
	, dashTime(0.3f)
	, currentTime(0.f)
	, rigidbody(nullptr)
{
	animationKeys.push_back("spearDash");
}

SkeletonSpearSkill2State::~SkeletonSpearSkill2State()
{
}

void SkeletonSpearSkill2State::StartDash()
{
	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], false);
	dashEndPos = skeletonSpear->GetPosition() + (skeletonSpear->IsFlipX() ? sf::Vector2f::left : sf::Vector2f::right) * 400.f;
	dashStartPos = skeletonSpear->GetPosition();
	currentTime = 0.f;
}

void SkeletonSpearSkill2State::Start()
{
	rigidbody = skeletonSpear->GetRigidbody();
}

void SkeletonSpearSkill2State::Enter()
{
	SkeletonSpearBaseState::Enter();
	rigidbody->ResetDropSpeed();
	rigidbody->ResetVelocity();
	rigidbody->Disable();
	isExtraDash = false;

	skillOnTime = 0.f;
	skillEndTime = 10.f;
	skeletonSpear->SetDashCount(1000);
	StartDash();
}

void SkeletonSpearSkill2State::Exit()
{
	rigidbody->SetActive(true);
	SkeletonSpearBaseState::Exit();
}

void SkeletonSpearSkill2State::Update(float deltaTime)
{
	SkeletonSpearBaseState::Update(deltaTime);
	currentTime += deltaTime;
	skillOnTime += deltaTime;
	if (skillOnTime >= skillEndTime)
	{
		skeletonSpear->SetDashCount(2);
	}

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
}