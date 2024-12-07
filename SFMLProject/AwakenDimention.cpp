#include "stdafx.h"
#include "AwakenDimention.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

AwakenDimention::AwakenDimention(const std::string& name)
	: AnimationGameObject("AwakenDimention")
{
	SoundManger::GetInstance().PlaySfx("Leiana_DarkDimensionRush_Impact", false);
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/DimensionPierce.csv");
	animator->AddAnimation(animation, "DimensionPierce");
	SetScale({ 3.f,3.f });
	animation->SetAnimationEndEvent(std::bind(&AwakenDimention::OnAttack, this), animation->GetEndFrameCount() - 3);
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount()-1);
}

void AwakenDimention::Start()
{
	AnimationGameObject::Start();
	animator->ChangeAnimation("DimensionPierce");
}
void AwakenDimention::OnAttack()
{
	AnimationHitBox* animationHitBox = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AnimationHitBox(nullptr, ColliderLayer::EnemyBullet, ColliderLayer::Player, "AwakenedThunder"), LayerType::EnemyBullet);

	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/awakenGroundDimension.csv");
	animationHitBox->GetAnimator()->AddAnimation(animation, "awakenGroundDimension");
	animationHitBox->GetAnimator()->ChangeAnimation("awakenGroundDimension");
	animationHitBox->GetAnimator()->SetAnimationSpeed(2.f);
	animationHitBox->SetPosition(position);
	animationHitBox->SetRotation(rotation);
	animationHitBox->SetScale({ 3.f,2.f });
	animationHitBox->SetDamage(10.f);
	animationHitBox->GetCollider()->SetScale({ 300.f, 20.f });
	animationHitBox->SetOrigin(originPreset);
	animationHitBox->Awake();
	animationHitBox->Start();
	animationHitBox->GetCollider()->SetRotation(rotation);
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, animationHitBox), animation->GetEndFrameCount());
}