#include "stdafx.h"
#include "Rising.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Enemy.h"
#include "Rigidbody.h"
#include "HitBoxObject.h"
#include "Reiana.h"

Rising::Rising(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name)
	: AnimationBullet(owner, thisLayerType, targetLayer, texId, name)
	, reiana(nullptr)
{
	damageInfo.damege = 10.f;
	damageInfo.useKnockback = true;
	damageInfo.knockbackDuration = 0.4f;
	damageInfo.owner = this;
	damageInfo.knockbackVelocity = { 50.f,0.f };
	damageInfo.hitDirection = sf::Vector2f::down;
}

void Rising::Start()
{
	reiana = dynamic_cast<Reiana*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("Reiana"));
	AnimationBullet::Start();

	effect1 = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AnimationGameObject("AwakenedThunder"), LayerType::EnemyBullet);
	Animation* animation = new Animation();
	animation->loadFromFile("animations/Enemy/Rayanna/Effects/RisingPierce.csv");
	effect1->GetAnimator()->AddAnimation(animation, "RisingPierce");
	effect1->GetAnimator()->ChangeAnimation("RisingPierce");
	effect1->SetPosition(reiana->GetPosition());
	effect1->Awake();
	effect1->Start();
	OnCreateHitBox();
	currentDelay = 0.f;
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, effect1), animation->GetFrameCount() - 1);
	SetPosition(reiana->GetPosition());
}
void Rising::Update(const float& deltaTime)
{
	AnimationBullet::Update(deltaTime);
	currentDelay += deltaTime;
	if (currentDelay > delayTime)
	{
		OnDestoryHitBox();
	}
}

void Rising::setDelay(float delay)
{
	delayTime = delay;
}

void Rising::OnCreateHitBox()
{
	collider->SetActive(true);
	SetDamage(damageInfo);
}

void Rising::OnDestoryHitBox()
{
	OnDestory();
	SetActive(false);
}

void Rising::SetPosition(const sf::Vector2f& pos)
{
	AnimationBullet::SetPosition(pos);
	if (effect1 != nullptr)
	{
	effect1->SetPosition(pos);
	}
}
