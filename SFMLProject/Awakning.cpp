#include "stdafx.h"
#include "Awakning.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

Awakning::Awakning(const std::string& name)
	: AnimationGameObject("AwakenNing")
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/AwakenNing.csv");
	animator->AddAnimation(animation, "AwakenNing");
	SetScale({ 4.f,4.f });
	animator->SetAnimationSpeed(2.f);
	SetOrigin(Origins::BottomCenter);
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}

void Awakning::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("AwakenNing");
}