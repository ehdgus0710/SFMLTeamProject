#include "stdafx.h"
#include "AwakenDropStart.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

AwakenDropStart::AwakenDropStart(const std::string& name)
	: AnimationGameObject("AwakenDropStartEffect")
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/AwakenDropStartEffect.csv");
	animator->AddAnimation(animation, "AwakenDropStartEffect");
	SetScale({ 2.f,2.f });
	SetOrigin(Origins::BottomCenter);
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}

void AwakenDropStart::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("AwakenDropStartEffect");
}