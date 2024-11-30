#include "stdafx.h"
#include "Dimension.h"

#include "Animation.h"
#include "Animator.h"
#include "Enemy.h"
#include "Rigidbody.h"
#include "Player.h"
#include "HitBoxObject.h"


Dimension::Dimension(ColliderLayer type, const std::string& texId, const std::string& name)
	: GameObject(name)
	, textureID(texId)
	, lifeTime(2.f)
	, currentLifeTime(0.f)
{
}


void Dimension::Start()
{
	TEXTURE_MANAGER.Load("MenuBar", "graphics/MenuBar_Unselected.png");
	sprite.setTexture(TEXTURE_MANAGER.Get(textureID));
	SetPosition(position);
	SetScale(scale);
	SetRotation(rotation);
	SetOrigin(originPreset);
	OnCreateHitBox();
}

void Dimension::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, preset);
}

void Dimension::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
}

void Dimension::SetUVRect(const sf::IntRect uvRect)
{
	textureUVRect = uvRect;
	sprite.setTextureRect(textureUVRect);
}

void Dimension::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(position);
}

void Dimension::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	if (animator != nullptr)
		animator->SetScale(scale);
	else
		sprite.setScale(scale);
	SetOrigin(originPreset);
}

void Dimension::SetRotation(float angle)
{
	rotation = angle;
	sprite.setRotation(angle);
}

sf::Vector2f Dimension::GetScale() const
{
	return scale;
}

void Dimension::Update(const float& deltaTime)
{
	if (animator != nullptr)
	{
		animator->Update(deltaTime);
	}

	currentLifeTime += deltaTime;

	if (currentLifeTime >= lifeTime)
	{
		SetDestory(true);
		OnDestoryHitBox();
	}
}

void Dimension::FixedUpdate(const float& deltaTime)
{
}

void Dimension::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
}

void Dimension::OnCollisionEnter(Collider* target)
{
}

void Dimension::CreateAnimator()
{
	if (animator == nullptr)
	{
		animator = new Animator(this, sprite);
	}
}

sf::FloatRect Dimension::GetLocalBounds() const
{
	return sprite.getLocalBounds();
}

sf::FloatRect Dimension::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}
void Dimension::OnCreateHitBox()
{
	hitBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(this, ColliderLayer::EnemyBullet, ColliderLayer::Player, true), LayerType::EnemyBullet);
	hitBox->SetScale({ 100.f,50.f });
	hitBox->SetRotation(rotation);
	hitBox->SetDamage(1000);
}

void Dimension::OnDestoryHitBox()
{
	hitBox->OnDestory();
	hitBox->SetActive(false);
	hitBox = nullptr;
}
