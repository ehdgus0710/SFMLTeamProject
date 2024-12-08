#include "stdafx.h"
#include "IntroLandSmoke.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

IntroLandSmoke::IntroLandSmoke(const std::string& name)
	: AnimationGameObject("name")
{
	SoundManger::GetInstance().PlaySfx("Leiana_Landing", false);
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/IntroLandSmoke.csv");
	animator->AddAnimation(animation, "DimensionPierce");
	animator->SetAnimationSpeed(2.f);
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}


void IntroLandSmoke::Start()
{
	SetScale({ 4.f,4.f });
	AnimationGameObject::Start();
	animator->ChangeAnimation("DimensionPierce");
}