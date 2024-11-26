#include "stdafx.h"
#include "FireBullet.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Enemy.h"
#include "Rigidbody.h"


FireBullet::FireBullet(const std::string& texId, const std::string& name)
	: GameObject(name)
	, textureID(texId)
	, speed(700.f)
	, lifeTime(2.f)
	, currentLifeTime(0.f)
{

	CreateCollider(ColliderType::Rectangle, ColliderLayer::PlayerBullet);
	CreateAnimator();
	rigidBody = new Rigidbody(this);
	rigidBody->SetGround(false);
	animator->LoadCsv("animators/attackFire.csv");
}


void FireBullet::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	animator->Start();
	collider->Reset();
	collider->SetOwnerScale({ (sf::Vector2f)animator->GetCurrentAnimation()->GetFrameInfo()[0].rectSize });
	animator->ChangeAnimation("attackFire", true);
}

void FireBullet::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, preset);
	collider->SetOrigin(preset);
}

void FireBullet::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
	collider->SetOrigin(newOrigin);
}


void FireBullet::SetUVRect(const sf::IntRect uvRect)
{
	textureUVRect = uvRect;
	sprite.setTextureRect(textureUVRect);
}

void FireBullet::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(position);
	collider->SetPosition(position);
}

void FireBullet::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	sprite.setScale(scale);
	collider->SetOwnerScale(scale);
	SetOrigin(originPreset);
}

void FireBullet::SetRotation(float angle)
{
	rotation = angle;
	sprite.setRotation(angle);
	collider->SetRotation(angle);
}

sf::Vector2f FireBullet::GetScale() const
{
	return scale;
}

void FireBullet::Update(const float& deltaTime)
{
	animator->Update(deltaTime);

	currentLifeTime += deltaTime;

	if (currentLifeTime >= lifeTime)
		SetDestory(true);
}

void FireBullet::FixedUpdate(const float& deltaTime)
{
	rigidBody->SetVelocity({ speed * moveDirection.x, rigidBody->GetCurrentVelocity().y });
	rigidBody->FixedUpdate(deltaTime);
}

void FireBullet::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
	collider->Render(renderWindow);
}

void FireBullet::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Wall || target->GetColliderLayer() == ColliderLayer::Block)
	{
		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(target->GetPosition(), target->GetScale());

		sf::Vector2f prevPosition = rigidBody->GetCurrentVelocity() * TimeManager::GetInstance().GetFixedDeletaTime();
		if (rect.bottomPosition > targetRect.topPosition + prevPosition.y)
		{
			SetDestory(true);
		}
		else
		{
			rigidBody->ResetDropSpeed();
			rigidBody->SetVelocity({ rigidBody->GetCurrentVelocity().x, -300.f });
		}

	}
	else if (target->GetColliderLayer() == ColliderLayer::Enemy)
	{
		SetDestory(true);
		((Enemy*)target->GetOwner())->SetHitDirection(moveDirection);
		((Enemy*)target->GetOwner())->TakeDamage();
	}
}

void FireBullet::CreateAnimator()
{
	if (animator == nullptr)
	{
		animator = new Animator(this, sprite);
	}
}

sf::FloatRect FireBullet::GetLocalBounds() const
{
	return sprite.getLocalBounds();
}

sf::FloatRect FireBullet::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

bool FireBullet::Save() const
{
	return false;
}

bool FireBullet::Load()
{
	return false;
}

bool FireBullet::SaveCsv(const std::string& filePath) const
{
	return false;
}

bool FireBullet::LoadCsv(const std::string& filePath)
{
	return false;
}