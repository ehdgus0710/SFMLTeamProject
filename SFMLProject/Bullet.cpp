#include "stdafx.h"
#include "Bullet.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Enemy.h"
#include "Rigidbody.h"


Bullet::Bullet(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name)
	: HitBoxObject(owner, thisLayerType, targetLayer,name)
	, textureID(texId)
	, speed(700.f)
	, lifeTime(10.f)
	, currentLifeTime(0.f)
	, isShoot(false)
{
	CreateCollider(ColliderType::Rectangle, thisLayerType);
}


void Bullet::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
	collider->Reset();
}

void Bullet::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, preset);
	collider->SetOrigin(preset);
}

void Bullet::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
	collider->SetOrigin(newOrigin);
}

void Bullet::SetMoveDirection(const sf::Vector2f& direction)
{
	moveDirection = direction;

	if (moveDirection.x > 0.f)
	{
		scale.x *= -1.f;
		SetScale(scale);
	}
}


void Bullet::Shoot()
{
	isShoot = true;
}

void Bullet::SetUVRect(const sf::IntRect uvRect)
{
	textureUVRect = uvRect;
	sprite.setTextureRect(textureUVRect);
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(position);
	collider->SetPosition(position);
}

void Bullet::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	if(animator != nullptr)
		animator->SetScale(scale);
	else
		sprite.setScale(scale);
	collider->SetOwnerScale(scale);
	SetOrigin(originPreset);
}

void Bullet::SetRotation(float angle)
{
	rotation = angle;
	sprite.setRotation(angle);
	collider->SetRotation(angle);
}

sf::Vector2f Bullet::GetScale() const
{
	return scale;
}

void Bullet::Update(const float& deltaTime)
{
	if(animator != nullptr)
		animator->Update(deltaTime);

	if (!isShoot)
		return;

	SetPosition(position + speed * moveDirection * deltaTime);

	currentLifeTime += deltaTime;

	if (currentLifeTime >= lifeTime)
		SetDestory(true);
}

void Bullet::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
	collider->Render(renderWindow);
}

void Bullet::OnCollisionEnter(Collider* target)
{
}

void Bullet::CreateAnimator()
{
	if (animator == nullptr)
	{
		animator = new Animator(this, sprite);
	}
}

sf::FloatRect Bullet::GetLocalBounds() const
{
	return sprite.getLocalBounds();
}

sf::FloatRect Bullet::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

bool Bullet::Save() const
{
	return false;
}

bool Bullet::Load()
{
	return false;
}

bool Bullet::SaveCsv(const std::string& filePath) const
{
	return false;
}

bool Bullet::LoadCsv(const std::string& filePath)
{
	return false;
}
