#include "stdafx.h"
#include "Knife.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Enemy.h"
#include "Rigidbody.h"
#include "Player.h"
#include "HitBoxObject.h"

Knife::Knife(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name)
	: AnimationBullet(owner, thisLayerType, targetLayer, texId, name)
	, player(nullptr)
{
	TEXTURE_MANAGER.Load("Knife", "graphics/HomingPierce_Ready_8.png");
	animator->CreateAnimation("Knife", "idle", { 96,31 }, 1, 0.1f);


	damageInfo.damege = 10.f;
	damageInfo.useKnockback = true;
	damageInfo.knockbackDuration = 0.5f;
	damageInfo.owner = this;
	damageInfo.knockbackVelocity = { 100.f,0.f };
}

void Knife::Start()
{
	player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("Player"));

	AnimationBullet::Start();	
	Bullet::SetSpeed(2000.f);

	effect1 = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AnimationGameObject("AwakenedThunder"), LayerType::EnemyBullet);
	Animation* animation = new Animation();
	animation->loadFromFile("animations/Enemy/Rayanna/Effects/HomingPierceReady.csv");
	effect1->GetAnimator()->AddAnimation(animation, "HomingPierceReady");
	effect1->GetAnimator()->ChangeAnimation("HomingPierceReady");
	effect1->Awake();
	effect1->Start();
	OnCreateHitBox();
	currentDelay = 0.f;
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, effect1), animation->GetFrameCount() - 1);
	collider->SetActive(false);
	collider->SetScale({ 80.f,30.f });
	effect1->SetPosition(position);
	effect1->SetScale({ 2.f,2.f });

	animator->ChangeAnimation("idle");
} 
void Knife::Update(const float& deltaTime)
{
	if (!isShoot)
	{
		currentDelay += deltaTime;

		moveDirection = player->GetPosition() - position;
		moveDirection.Normalized();
		effect1->SetRotation(Utils::Angle(moveDirection));

		SetRotation(Utils::Angle(moveDirection));

		if (currentDelay >= delayTime)
		{
			OnCreateHitBox();
			isShoot = true;
		}
	}

	AnimationBullet::Update(deltaTime);
}

void Knife::setDelay(float delay)
{
	delayTime = delay;
}

void Knife::OnCreateHitBox()
{
	collider->SetActive(true);
	damageInfo.hitDirection = moveDirection;
	SetDamage(damageInfo);
}

void Knife::OnDestoryHitBox()
{
	OnDestory();
	SetActive(false);
}
