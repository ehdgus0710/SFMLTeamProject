#include "stdafx.h"
#include "KoopaFireBullet.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Rigidbody.h"


KoopaFireBullet::KoopaFireBullet(const std::string& texId, const std::string& name)
	: Bullet(ColliderLayer::EnemyBullet, texId, name)
{
	speed = 300.f;
	lifeTime = 10.f;
	CreateAnimator();
	animator->LoadCsv("animators/koopaFire.csv");
}

void KoopaFireBullet::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	animator->Start();
	collider->Reset();
	collider->SetScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });
	animator->ChangeAnimation("koopaFire", true);
}

void KoopaFireBullet::Update(const float& deltaTime)
{
	animator->Update(deltaTime);
	SetPosition(position + speed * moveDirection * deltaTime);

	currentLifeTime += deltaTime;

	if (currentLifeTime >= lifeTime)
		SetDestory(true);
}

void KoopaFireBullet::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Wall || target->GetColliderLayer() == ColliderLayer::Block)
	{
		SetDestory(true);
	}
	else if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		SetDestory(true);
		((Player*)target->GetOwner())->TakeDamage();
	}
}

void KoopaFireBullet::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
	collider->Render(renderWindow);
}

bool KoopaFireBullet::Save() const
{
	return false;
}

bool KoopaFireBullet::Load()
{
	return false;
}

bool KoopaFireBullet::SaveCsv(const std::string& filePath) const
{
	return false;
}

bool KoopaFireBullet::LoadCsv(const std::string& filePath)
{
	return false;
}