#include "stdafx.h"
#include "MeteorGroundSmoke.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

MeteorGroundSmoke::MeteorGroundSmoke(const std::string& name)
	: AnimationGameObject(name)
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/MeteorGroundSmoke.csv");
	animator->AddAnimation(animation, "MeteorGroundSmoke");

	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}


void MeteorGroundSmoke::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("MeteorGroundSmoke");
}