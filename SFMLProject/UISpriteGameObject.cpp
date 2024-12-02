#include "stdafx.h"
#include "UISpriteGameObject.h"

#include "Collider.h"
#include "Animator.h"

UISpriteGameObject::UISpriteGameObject(const std::string& texId, const std::string& name)
	: UIGameObject(name)
	, textureId(texId)
{
}


void UISpriteGameObject::SetPosition(const sf::Vector2f& pos)
{
	UIGameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void UISpriteGameObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	sprite.setScale(scale);
}

void UISpriteGameObject::SetRotation(float angle)
{
	rotation = angle;
	sprite.setRotation(rotation);
}

void UISpriteGameObject::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
	UIGameObject::Render(renderWindow);
}

void UISpriteGameObject::Start()
{
	sprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get(textureId));

	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
	SetOrigin(originPreset);
}

void UISpriteGameObject::Update(const float& deltaTime)
{
	UIGameObject::Update(deltaTime);
}

void UISpriteGameObject::FixedUpdate(const float& deltaTime)
{
	UIGameObject::FixedUpdate(deltaTime);
}

void UISpriteGameObject::LateUpdate(const float& deltaTime)
{
	UIGameObject::LateUpdate(deltaTime);
}

void UISpriteGameObject::CreateAnimator()
{
	if (animator != nullptr)
		return;

	animator = new Animator(this, sprite);
}

sf::FloatRect UISpriteGameObject::GetLocalBounds() const
{
	return sprite.getLocalBounds();
}

sf::FloatRect UISpriteGameObject::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

void UISpriteGameObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, preset);
}

void UISpriteGameObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
}

void UISpriteGameObject::ChangeSprite(std::string changeTextureID)
{
	textureId = changeTextureID;
	sprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get(textureId), true);

	SetOrigin(originPreset);
}
