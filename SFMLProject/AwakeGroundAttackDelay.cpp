#include "stdafx.h"
#include "AwakeGroundAttackDelay.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

AwakeGroundAttackDelay::AwakeGroundAttackDelay(const std::string& name)
	: AnimationGameObject("AwakeGroundAttackDelay")
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/AwakeGroundAttackDelay.csv");
	animator->AddAnimation(animation, "AwakeGroundAttackDelay");
	SetScale({ 2.f,2.f });
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}

void AwakeGroundAttackDelay::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("AwakeGroundAttackDelay");
}
