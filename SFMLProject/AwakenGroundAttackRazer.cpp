#include "stdafx.h"
#include "AwakenGroundAttackRazer.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

AwakenGroundAttackRazer::AwakenGroundAttackRazer(const std::string& name)
	: AnimationGameObject("AwakenGroundAttackRazer")
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/AwakenGroundAttackRazer.csv");
	animator->AddAnimation(animation, "AwakenGroundAttackRazer");
	SetScale({ 2.f,2.f });
	SetOrigin(Origins::BottomCenter);
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}

void AwakenGroundAttackRazer::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("AwakenGroundAttackRazer");
}