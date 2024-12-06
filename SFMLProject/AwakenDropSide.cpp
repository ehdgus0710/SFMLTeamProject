#include "stdafx.h"
#include "AwakenDropSide.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

AwakenDropSide::AwakenDropSide(const std::string& name)
	: AnimationGameObject("AwakenDropSideEffect")
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/AwakenDropSideEffect.csv");
	animator->AddAnimation(animation, "AwakenDropSideEffect");
	speed = 100.f;
	SetScale({ 2.5f, 2.5f });
	SetOrigin(Origins::BottomCenter);
}

void AwakenDropSide::Move(float deltaTime)
{
	auto pos = GetPosition();
	speed *= 1.01f;
	pos.x = pos.x + speed * deltaTime;
	SetPosition(pos);
}
void AwakenDropSide::Move2(float deltaTime)
{
	auto pos = GetPosition();
	speed *= 1.01f;
	pos.x = pos.x - speed * deltaTime;
	SetPosition(pos);
}

void AwakenDropSide::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("AwakenDropSideEffect");
}

void AwakenDropSide::Delete()
{
	OnDestory();
}