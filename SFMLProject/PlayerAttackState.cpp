#include "stdafx.h"
#include "PlayerAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"

PlayerAttackState::PlayerAttackState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Attack)
{
	animationKeys.push_back("littleboneAttack");
	animationKeys.push_back("noheadlittleboneAttack");
}

PlayerAttackState::~PlayerAttackState()
{
}

void PlayerAttackState::Awake()
{
	PlayerBaseState::Awake();
}

void PlayerAttackState::Start()
{
	rigidbody = player->GetRigidbody();
	sequenceAttack = false;
}

void PlayerAttackState::Enter()
{
	PlayerBaseState::Enter();
	StartAttack();
}

void PlayerAttackState::Exit()
{
	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->GetCurrentAnimation()->ClearEndEvent(endFrame);
	PlayerBaseState::Exit();
}

void PlayerAttackState::Update(float deltaTime)
{
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::X))
	{
		sequenceAttack = true;
	}
}

void PlayerAttackState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerAttackState::StartAttack()
{
	currentAttackCount = 1;
	animator->ChangeAnimation(animationKeys[currentAnimationIndex] + "1", false);
	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&PlayerAttackState::EndAttack, this), endFrame);
}

void PlayerAttackState::NextAttack()
{
	animator->ChangeAnimation(animationKeys[currentAnimationIndex] + "2", true);
	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&PlayerAttackState::EndAttack, this), endFrame);
}

void PlayerAttackState::EndAttack()
{
	if (sequenceAttack)
	{
		SequenceAttack();
	}
	else
	{
		fsm->ChangeState(PlayerStateType::Idle);
	}
}

void PlayerAttackState::SequenceAttack()
{
	if (currentAttackCount == 1)
	{
		int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
		animator->GetCurrentAnimation()->ClearEndEvent(endFrame);
		NextAttack();
	}
	else
	{
		int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
		animator->GetCurrentAnimation()->ClearEndEvent(endFrame);
		StartAttack();
	}

	sequenceAttack = false;
}