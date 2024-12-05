#include "stdafx.h"
#include "AwakeGroundDimention.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

AwakeGroundDimention::AwakeGroundDimention(const std::string& name)
	: AnimationGameObject("name")
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/GroundDimension.csv");
	animator->AddAnimation(animation, "GroundDimension");
	SetScale({ 2.5f,1.f });
}


void AwakeGroundDimention::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("GroundDimension");
}
