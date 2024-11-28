#include "stdafx.h"
#include "PlayerAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"

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
	animator->ChangeAnimation("noheadlittleboneAttack1", false);

	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&PlayerAttackState::SequenceAttack, this), endFrame);
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

void PlayerAttackState::EndAttack()
{
	fsm->ChangeState(PlayerStateType::Idle);
}

void PlayerAttackState::SequenceAttack()
{
	if (sequenceAttack)
	{
		animator->ChangeAnimation("noheadlittleboneAttack2", false);
	}
	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&PlayerAttackState::EndAttack, this), endFrame);
}

PlayerAttackState::PlayerAttackState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Attack)
{
}

PlayerAttackState::~PlayerAttackState()
{
}
