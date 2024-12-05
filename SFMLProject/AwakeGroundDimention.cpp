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
	SetScale({ 2.5f,1.f });
}


void AwakeGroundDimention::Start()
{
	TEXTURE_MANAGER.Load("DimensionDelete", "graphics/boss/Rayanna/effects/GroundDimension.png");
	AnimationGameObject::Start();
	animator->ChangeAnimation("awakenGroundDimension");
}