#include "stdafx.h"
#include "IntroLandSmoke.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

IntroLandSmoke::IntroLandSmoke(const std::string& name)
	: AnimationGameObject("name")
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/IntroLandSmoke.csv");
	animator->AddAnimation(animation, "DimensionPierce");

	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}


void IntroLandSmoke::Start()
{
	SetScale({ 2.f,2.f });
	AnimationGameObject::Start();
	animator->ChangeAnimation("DimensionPierce");
}