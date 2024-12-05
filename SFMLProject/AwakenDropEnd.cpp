#include "stdafx.h"
#include "AwakenDropEnd.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

AwakenDropEnd::AwakenDropEnd(const std::string& name)
	: AnimationGameObject("AwakenDropEnd")
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/AwakenDropEnd.csv");
	animator->AddAnimation(animation, "AwakenDropEnd");
	SetScale({ 1.f,1.f });
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}

void AwakenDropEnd::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("AwakenDropEnd");
}