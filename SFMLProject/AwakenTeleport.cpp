#include "stdafx.h"
#include "AwakenTeleport.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

AwakenTeleport::AwakenTeleport(const std::string& name)
	: AnimationGameObject("AwakenTeleport")
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/AwakenTeleport.csv");
	animator->AddAnimation(animation, "AwakenTeleport");
	SetScale({ 2.f,2.f });
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}

void AwakenTeleport::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("AwakenTeleport");
}