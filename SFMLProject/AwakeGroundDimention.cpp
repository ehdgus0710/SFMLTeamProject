#include "stdafx.h"
#include "AwakeGroundDimention.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

AwakeGroundDimention::AwakeGroundDimention(const std::string& name)
	: AnimationGameObject("AwakeGroundDimention")
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/awakenGroundDimension.csv");
	animator->AddAnimation(animation, "awakenGroundDimension");
	SetScale({ 10.f,1.f });
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}

void AwakeGroundDimention::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("awakenGroundDimension");
}