#include "stdafx.h"
#include "PlayerSkill1State.h"

#include "Animator.h"
#include "Animation.h"
#include "Rigidbody.h"
#include "Camera.h"

PlayerSkill1State::PlayerSkill1State(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Skill1)
{
}

PlayerSkill1State::~PlayerSkill1State()
{
}

void PlayerSkill1State::OnThrowHead()
{
	player->OnThrowHead();
	Animation* animation = animator->GetCurrentAnimation();
	animation->ClearEndEvent(1);
}

void PlayerSkill1State::OnEndAniamtion()
{
	Animation* animation = animator->GetCurrentAnimation();
	animation->ClearEndEvent(animation->GetFrameCount() - 1);

	player->GetRigidbody()->SetActive(true);
	player->GetRigidbody()->ResetDropSpeed();
	player->GetRigidbody()->ResetVelocity();

	if (player->GetRigidbody()->IsGround())
		fsm->ChangeState(PlayerStateType::Idle);
	else
	{
		fsm->ChangeState(PlayerStateType::Falling);
	}

}

void PlayerSkill1State::Start()
{
}

void PlayerSkill1State::Enter()
{
	PlayerBaseState::Enter();

	player->OnSkill1CoolTime();

	animator->ChangeAnimation("littleboneThrowHead");
	Animation* animation = animator->GetCurrentAnimation();
	animation->SetAnimationStartEvent(std::bind(&PlayerSkill1State::OnThrowHead, this), 1);
	animation->SetAnimationStartEvent(std::bind(&PlayerSkill1State::OnEndAniamtion, this), animation->GetEndFrameCount());

	player->GetRigidbody()->SetActive(false);
}

void PlayerSkill1State::Exit()
{
	PlayerBaseState::Exit();

	Animation* animation = animator->GetCurrentAnimation();
	animation->ClearEndEvent(1);
	animation->ClearEndEvent(animation->GetEndFrameCount());
}

void PlayerSkill1State::Update(float deltaTime)
{
}

void PlayerSkill1State::FixedUpdate(float fixedDeltaTime)
{
}