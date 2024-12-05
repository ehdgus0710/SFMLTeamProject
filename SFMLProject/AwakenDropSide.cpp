#include "stdafx.h"
#include "AwakenDropSide.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

AwakenDropSide::AwakenDropSide(const std::string& name)
	: AnimationGameObject("AwakenDropSideEffect")
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/AwakenDropSideEffect.csv");
	animator->AddAnimation(animation, "AwakenDropSideEffect");
	SetScale({ 1.f,1.f });
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}

void AwakenDropSide::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("AwakenDropSideEffect");
}