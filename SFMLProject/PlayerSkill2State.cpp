#include "stdafx.h"
#include "PlayerSkill2State.h"

#include "Animator.h"
#include "Animation.h"
#include "Rigidbody.h"

PlayerSkill2State::PlayerSkill2State(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Skill2)
{
}

PlayerSkill2State::~PlayerSkill2State()
{
}


void PlayerSkill2State::Start()
{
}

void PlayerSkill2State::Enter()
{
	PlayerBaseState::Enter();

	animator->ChangeAnimation("littleboneSkillMove");
	Animation* animation = animator->GetCurrentAnimation();

	animation->SetAnimationStartEvent(std::bind(&PlayerSkill2State::OnEndAniamtion, this), animation->GetFrameCount() - 1);

	player->GetRigidbody()->SetActive(false);
	player->SetPosition(player->GetHeadPosition());
	player->OnSkill2CoolTime();
}

void PlayerSkill2State::Exit()
{
	PlayerBaseState::Exit();

	Animation* animation = animator->GetCurrentAnimation();
	animation->ClearEndEvent(1);
	animation->ClearEndEvent(animation->GetFrameCount() - 1);
}

void PlayerSkill2State::Update(float deltaTime)
{
}

void PlayerSkill2State::FixedUpdate(float fixedDeltaTime)
{
}


void PlayerSkill2State::OnEndAniamtion()
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