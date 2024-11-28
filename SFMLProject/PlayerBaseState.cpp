#include "stdafx.h"
#include "PlayerBaseState.h"
#include "Animator.h"
#include "Animation.h"

PlayerBaseState::PlayerBaseState(PlayerFSM* fsm, PlayerStateType stateType)
	: BaseState<PlayerStateType>(stateType)
	, fsm(fsm)
	, player(fsm->GetPlayer())
	, animator(nullptr)
	, currentAnimationIndex(0)
{
}

PlayerBaseState::~PlayerBaseState()
{
}

void PlayerBaseState::SetChangeAnimationKey(int index)
{
	if (currentAnimationIndex != index)
	{
		currentAnimationIndex = index;
		int animationIndex = animator->GetCurrentAnimation()->GetCurrentIndex();
		animator->ChangeAnimation(animationKeys[currentAnimationIndex], animationIndex, animator->GetCurrentAnimation()->IsRepeat(), animator->GetCurrentAnimation()->IsUnScale());
	}
}

void PlayerBaseState::Awake()
{
	animator = player->GetAnimator();
}

void PlayerBaseState::Start()
{
}

void PlayerBaseState::Enter()
{
	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void PlayerBaseState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}

void PlayerBaseState::Update(float deltaTime)
{
}

void PlayerBaseState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerBaseState::LateUpdate(float deltaTime)
{
}
