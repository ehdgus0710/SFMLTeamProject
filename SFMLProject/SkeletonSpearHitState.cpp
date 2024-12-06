#include "stdafx.h"
#include "SkeletonSpearHitState.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"
#include "Rigidbody.h"

SkeletonSpearHitState::SkeletonSpearHitState(SkeletonSpearFSM* fsm)
	: SkeletonSpearBaseState(fsm, SkeletonSpearStateType::Hit)
	, currentTime(0.f)
	, rigidbody(nullptr)
{
}

SkeletonSpearHitState::~SkeletonSpearHitState()
{
}

void SkeletonSpearHitState::SetDamageInfo(const DamegeInfo& damage)
{
	currentDamageInfo = damage;
}

void SkeletonSpearHitState::Awake()
{
	SkeletonSpearBaseState::Awake();

}

void SkeletonSpearHitState::Start()
{
	rigidbody = skeletonSpear->GetRigidbody();
}

void SkeletonSpearHitState::Enter()
{
	SkeletonSpearBaseState::Enter();

	currentTime = 0.f;
	rigidbody->ResetVelocity();

	if (currentDamageInfo.hitDirection == sf::Vector2f::down || currentDamageInfo.hitDirection == sf::Vector2f::up)
	{
		if (skeletonSpear->GetPosition().x < currentDamageInfo.owner->GetPosition().x)
			rigidbody->SetVelocity(sf::Vector2f::right * currentDamageInfo.knockbackVelocity);
		else
			rigidbody->SetVelocity(sf::Vector2f::left * currentDamageInfo.knockbackVelocity);
	}
	else
	{
		if (currentDamageInfo.knockbackVelocity.y != 0.f && rigidbody->GetCurrentVelocity().y == 0.f)
		{
			rigidbody->SetGround(false);
		}

		rigidbody->SetVelocity(currentDamageInfo.knockbackVelocity);
	}
}

void SkeletonSpearHitState::Exit()
{
	SkeletonSpearBaseState::Exit();

	rigidbody->SetVelocity({ 0.f, rigidbody->GetCurrentVelocity().y });
}

void SkeletonSpearHitState::Update(float deltaTime)
{
	currentTime += deltaTime;
	if (currentTime >= currentDamageInfo.knockbackDuration)
	{
		if (rigidbody->GetCurrentVelocity().y != 0.f)
			fsm->ChangeState(SkeletonSpearStateType::Falling);
		else
			fsm->ChangeState(SkeletonSpearStateType::Idle);
	}
}