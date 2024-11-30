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
}

void Knife::Start()
{
	player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("Player"));

	AnimationBullet::Start();	
	Bullet::SetSpeed(2000.f);

	collider->SetActive(false);
	collider->SetScale({ 80.f,30.f });

	animator->ChangeAnimation("idle");
} 
void Knife::Update(const float& deltaTime)
{
	if (!isShoot)
	{
		currentDelay += deltaTime;

		moveDirection = player->GetPosition() - position;
		moveDirection.Normalized();

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
	SetDamage(1000);
}

void Knife::OnDestoryHitBox()
{
	OnDestory();
	SetActive(false);
}
