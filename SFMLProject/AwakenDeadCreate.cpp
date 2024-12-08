#include "stdafx.h"
#include "AwakenDeadCreate.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

AwakenDeadCreate::AwakenDeadCreate(const std::string& name)
	: AnimationGameObject("AwakenDeadStart")
{
	SoundManger::GetInstance().PlaySfx("Leiana_Awaken_Dead", false);
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/AwakenDeadStart.csv");
	animator->AddAnimation(animation, "AwakenDeadStart");
	SetScale({ 5.f,3.f });
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}

void AwakenDeadCreate::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("AwakenDeadStart");
}