#include "stdafx.h"
#include "SkeletonSpearBaseState.h"

#include "Animator.h"
#include "Animation.h"

SkeletonSpearBaseState::SkeletonSpearBaseState(SkeletonSpearFSM* fsm, SkeletonSpearStateType stateType)
	: BaseState<PlayerStateType>(stateType)
	, fsm(fsm)
	, skeletonSpear(fsm->GetSkeletonSpear())
	, animator(nullptr)
	, currentAnimationIndex(0)
{
}

SkeletonSpearBaseState::~SkeletonSpearBaseState()
{
}

void SkeletonSpearBaseState::SetChangeAnimationKey(int index)
{
	if (currentAnimationIndex != index)
	{
		currentAnimationIndex = index;
		int animationIndex = animator->GetCurrentAnimation()->GetCurrentIndex();
		animator->ChangeAnimation(animationKeys[currentAnimationIndex], animationIndex, animator->GetCurrentAnimation()->IsRepeat(), animator->GetCurrentAnimation()->IsUnScale());
	}
}

int SkeletonSpearBaseState::GetAnimationIndex()
{
	currentAnimationIndex = (skeletonSpear->IsNoneHead() ? 1 : 0);
	return currentAnimationIndex;
}

void SkeletonSpearBaseState::Awake()
{
	animator = skeletonSpear->GetAnimator();
}

void SkeletonSpearBaseState::Start()
{
}

void SkeletonSpearBaseState::Enter()
{
	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void SkeletonSpearBaseState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}

void SkeletonSpearBaseState::Update(float deltaTime)
{
}

void SkeletonSpearBaseState::FixedUpdate(float fixedDeltaTime)
{
}

void SkeletonSpearBaseState::LateUpdate(float deltaTime)
{
}


