#include "stdafx.h"
#include "AwakenDeadDelete.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

AwakenDeadDelete::AwakenDeadDelete(const std::string& name)
	: AnimationGameObject("AwakenDeadEnd")
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/AwakenDeadEnd.csv");
	animator->AddAnimation(animation, "AwakenDeadEnd");
	SetScale({ 5.f,3.f });
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}
void AwakenDeadDelete::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("AwakenDeadEnd");
}