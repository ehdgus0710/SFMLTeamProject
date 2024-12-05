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
	SetScale({ 1.f,1.f });
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}

void AwakenDropStart::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("AwakenDropStartEffect");
}