#include "stdafx.h"
#include "PlayerSkill2State.h"

#include "Animator.h"
#include "Animation.h"
#include "Rigidbody.h"
#include "Collider.h"

PlayerSkill2State::PlayerSkill2State(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Skill2)
{
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("SkulReborn", "AudioClip/Skul/Skul_Reborn.wav");
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

	animation->SetAnimationStartEvent(std::bind(&PlayerSkill2State::OnEndAniamtion, this), animation->GetEndFrameCount());

	player->GetRigidbody()->SetActive(false);
	player->SetPosition(player->GetHeadPosition() + 23.5f * sf::Vector2f::up);
	player->OnSkill2CoolTime();
	player->OnGetHead();
	SoundManger::GetInstance().PlaySfx("SkulReborn");
}

void PlayerSkill2State::Exit()
{
	PlayerBaseState::Exit();

	Animation* animation = animator->GetCurrentAnimation();
	animation->ClearEndEvent(1);
	animation->ClearEndEvent(animation->GetEndFrameCount());
}

void PlayerSkill2State::Update(float deltaTime)
{
	if (KeyActionManager::GetInstance().GetKeyDown(KeyActionType::Dash))
	{
		player->GetRigidbody()->SetActive(true);
		player->GetRigidbody()->ResetDropSpeed();
		player->GetRigidbody()->ResetVelocity();

		fsm->ChangeState(PlayerStateType::Dash);
	}
}

void PlayerSkill2State::FixedUpdate(float fixedDeltaTime)
{
}


void PlayerSkill2State::OnEndAniamtion()
{
	Animation* animation = animator->GetCurrentAnimation();
	animation->ClearEndEvent(animation->GetEndFrameCount());

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