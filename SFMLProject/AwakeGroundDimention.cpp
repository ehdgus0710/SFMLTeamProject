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
	SetScale({ 10.f,2.f });
	animator->SetAnimationSpeed(2.f);
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount()-1);
}

void AwakeGroundDimention::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("awakenGroundDimension");
}
void AwakeGroundDimention::OnAttack()
{
	AnimationHitBox* animationHitBox = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AnimationHitBox(nullptr, ColliderLayer::EnemyBullet, ColliderLayer::Player, "AwakenedThunder"), LayerType::EnemyBullet);

	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/awakenGroundDimension.csv");
	animationHitBox->GetAnimator()->AddAnimation(animation, "awakenGroundDimension");
	animationHitBox->GetAnimator()->ChangeAnimation("awakenGroundDimension");
	animationHitBox->GetAnimator()->SetAnimationSpeed(2.f);
	animationHitBox->SetPosition(position);
	animationHitBox->SetRotation(rotation);
	animationHitBox->SetScale({ 10.f,2.f });
	animationHitBox->SetDamage(10.f);
	animationHitBox->GetCollider()->SetScale({ 1050.f, 20.f });
	animationHitBox->SetOrigin(originPreset);
	animationHitBox->Awake();
	animationHitBox->Start();
	animationHitBox->GetCollider()->SetRotation(rotation);
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, animationHitBox), animation->GetEndFrameCount());
}