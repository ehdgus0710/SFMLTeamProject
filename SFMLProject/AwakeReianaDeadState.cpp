#include "stdafx.h"

#include "AwakeReianaDeadState.h"
#include "Animator.h"
#include "Animation.h"
#include "AwakenDeadCreate.h"
#include "AwakenDeadDelete.h"
#include "Scene.h"
#include "ReianaUIHub.h"
#include "Collider.h"

AwakeReianaDeadState::AwakeReianaDeadState(AwakeReianaFsm* fsm)
	:AwakeReianaBaseState(fsm, AwakeReianaStateType::Dead)
{
}

AwakeReianaDeadState::~AwakeReianaDeadState()
{
}

void AwakeReianaDeadState::Enter()
{
	AwakeReianaBaseState::Enter();
	animator->ChangeAnimation("awakenDarkDeadBody", false);
	Animation* animation = new Animation();
	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	AwakenDeadCreate* awakenDeadCreate = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AwakenDeadCreate("AwakenDeadStart"), LayerType::BackGround_Forward);
	awakenDeadCreate->SetPosition(awakeReiana->GetPosition() - sf::Vector2f{ 0.f, -45.f });
	awakenDeadCreate->SetOrigin(Origins::BottomCenter);
	awakenDeadCreate->Start();
	int effectEndFream = awakenDeadCreate->GetAnimator()->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	awakenDeadCreate->GetAnimator()->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&AwakeReianaDeadState::DeleteEffect, this), effectEndFream);
	awakeReiana->GetCollider()->SetActive(false);
}

void AwakeReianaDeadState::DeleteEffect()
{
	AwakenDeadDelete* awakenDeadDelete = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AwakenDeadDelete("AwakenDeadStart"), LayerType::BackGround_Forward);
	awakenDeadDelete->SetPosition({ awakeReiana->GetPosition() - sf::Vector2f{ 0.f, -45.f} });
	awakenDeadDelete->SetOrigin(Origins::BottomCenter);
	awakenDeadDelete->Start();

	int effectEndFream = awakenDeadDelete->GetAnimator()->GetCurrentAnimation()->GetFrameInfo().size() - 1;

	awakenDeadDelete->GetAnimator()->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&AwakeReianaDeadState::OnDead, this), effectEndFream);
}

void AwakeReianaDeadState::OnDead()
{
	awakeReiana->SetActive(false);
	//awakeReiana->GetReianaUIHub()->SetActive(false);
}



