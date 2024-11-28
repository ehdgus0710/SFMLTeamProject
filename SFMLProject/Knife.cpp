#include "stdafx.h"
#include "Knife.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Enemy.h"
#include "Rigidbody.h"
#include "Player.h"


Knife::Knife(ColliderLayer type, const std::string& texId, const std::string& name)
	: GameObject(name)
	, textureID(texId)
	, lifeTime(2.f)
	, currentLifeTime(0.f)
	, delayTime(0.5f)
	, currentDelay(0.f)
{
	CreateCollider(ColliderType::Rectangle, type);
}


void Knife::Start()
{
	
	TEXTURE_MANAGER.Load("MenuBar", "graphics/MenuBar_Unselected.png");
	Player* player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("Player"));
	sprite.setTexture(TEXTURE_MANAGER.Get(textureID));
	direction = player->GetPosition() - position;
	direction.Normalized();
	SetPosition(position);
	SetScale(scale);
	SetRotation(Utils::Angle(direction));
	SetOrigin(originPreset);
	collider->Reset();
}

void Knife::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, preset);
	collider->SetOrigin(preset);
}

void Knife::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
	collider->SetOrigin(newOrigin);
}

void Knife::SetUVRect(const sf::IntRect uvRect)
{
	textureUVRect = uvRect;
	sprite.setTextureRect(textureUVRect);
}

void Knife::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(position);
	collider->SetPosition(position);
}

void Knife::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	if (animator != nullptr)
		animator->SetScale(scale);
	else
		sprite.setScale(scale);
	collider->SetOwnerScale(scale);
	SetOrigin(originPreset);
}

void Knife::SetRotation(float angle)
{
	rotation = angle;
	sprite.setRotation(angle);
	collider->SetRotation(angle);
}

sf::Vector2f Knife::GetScale() const
{
	return scale;
}

void Knife::Update(const float& deltaTime)
{
	if (animator != nullptr)
		animator->Update(deltaTime);

	currentLifeTime += deltaTime;
	delayTime += deltaTime;

	if (currentLifeTime >= lifeTime)
		SetDestory(true);
	if (currentDelay >= delayTime)
	{

	}
	else
		SetRotation(Utils::Angle(direction));

}

void Knife::FixedUpdate(const float& deltaTime)
{
}

void Knife::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
	collider->Render(renderWindow);
}

void Knife::OnCollisionEnter(Collider* target)
{
}

void Knife::CreateAnimator()
{
	if (animator == nullptr)
	{
		animator = new Animator(this, sprite);
	}
}

sf::FloatRect Knife::GetLocalBounds() const
{
	return sprite.getLocalBounds();
}

sf::FloatRect Knife::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}