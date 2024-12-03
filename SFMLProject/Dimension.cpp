#include "stdafx.h"
#include "Dimension.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

Dimension::Dimension(const std::string& name)
	: AnimationGameObject("name")
{
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/DimensionPierce.csv");
	animator->AddAnimation(animation, "DimensionPierce");
	SetScale({ 2.f,2.f });
	animation->SetAnimationEndEvent(std::bind(&Dimension::OnAttack, this), animation->GetEndFrameCount()-6);
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
}


void Dimension::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("DimensionPierce");
}

void Dimension::OnAttack()
{
	AnimationHitBox* animationHitBox = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AnimationHitBox(nullptr, ColliderLayer::EnemyBullet, ColliderLayer::Player, "AwakenedThunder"), LayerType::EnemyBullet);
	
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/DimensionPierceAttack.csv");
	animationHitBox->GetAnimator()->AddAnimation(animation, "DimensionPierceAttack");
	animationHitBox->GetAnimator()->ChangeAnimation("DimensionPierceAttack");
	animationHitBox->SetPosition(position);
	animationHitBox->SetRotation(rotation + 135.f);
	animationHitBox->SetScale({ 2.f,2.f });
	animationHitBox->SetDamage(10.f);
	animationHitBox->GetCollider()->SetScale({ 150.f, 5.f });
	animationHitBox->SetOrigin(originPreset);
	animationHitBox->Awake();
	animationHitBox->Start();
	animationHitBox->GetCollider()->SetRotation(rotation);
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, animationHitBox), animation->GetEndFrameCount());
}