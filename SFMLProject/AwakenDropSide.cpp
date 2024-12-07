#include "stdafx.h"
#include "AwakenDropSide.h"

#include "Animation.h"
#include "Animator.h"
#include "AnimationHitBox.h"
#include "Collider.h"

AwakenDropSide::AwakenDropSide(const std::string& name)
	: AnimationGameObject("AwakenDropSideEffect")
{
	animationHitBox = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AnimationHitBox(nullptr, ColliderLayer::EnemyBullet, ColliderLayer::Player, "AwakenedThunder"), LayerType::EnemyBullet);
	Animation* animation = new Animation("animations/Enemy/Rayanna/Effects/AwakenDropSideEffect.csv");
	animationHitBox->GetAnimator()->AddAnimation(animation, "AwakenDropSideEffect");
	animationHitBox->GetAnimator()->ChangeAnimation("AwakenDropSideEffect");
	animationHitBox->GetAnimator()->SetAnimationSpeed(2.f);
	animationHitBox->SetRotation(rotation);
	animationHitBox->SetDamage(10.f);
	animationHitBox->GetCollider()->SetScale({ 80.f, 100.f });
	animationHitBox->GetCollider()->SetOffsetPosition({ 0.f,-80.f });
	animationHitBox->SetOrigin(Origins::BottomCenter);
	animationHitBox->Awake();
	animationHitBox->Start();
	animationHitBox->GetCollider()->SetRotation(rotation);
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, animationHitBox), animation->GetEndFrameCount());
	animationHitBox->SetScale({ 3.5f,3.5f });
	speed = 100.f;
}

void AwakenDropSide::Move(float deltaTime, sf::Vector2f pos)
{
	if (!setPos)
	{
		auto posi = pos;
		posi.y = posi.y + 80;
		animationHitBox->SetPosition(posi);
		setPos = true;
	}
	auto posi = animationHitBox->GetPosition();
	speed *= 1.01f;
	posi.x = posi.x + speed * deltaTime;
	animationHitBox->SetPosition(posi);
}
void AwakenDropSide::Move2(float deltaTime, sf::Vector2f pos)
{
	if (!setPosLeft)
	{
		auto posi = pos;
		posi.y = posi.y + 80;
		animationHitBox->SetPosition(posi);
		setPosLeft = true;
	}
	animationHitBox->SetScale({ -3.5f,3.5f });
	auto posi = animationHitBox->GetPosition();
	speed *= 1.01f;
	posi.x = posi.x - speed * deltaTime;
	animationHitBox->SetPosition(posi);
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