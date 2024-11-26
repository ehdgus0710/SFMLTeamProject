#include "stdafx.h"
#include "RectSpriteGameObject.h"
#include "Animator.h"
#include "Collider.h"

void RectSpriteGameObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	if (animator)
		animator->Start();
	else
	{
		sprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get(textureId));
		sprite.setTextureRect(rect);
	}

	if (collider != nullptr)
		collider->Reset();

	SetOrigin(originPreset);
}

void RectSpriteGameObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	sprite.setScale(scale);

	if (collider != nullptr)
	{
		collider->SetOwnerScale(sf::Vector2f((float)rect.width, (float)rect.height) * scale);
	}
}

RectSpriteGameObject::RectSpriteGameObject(const sf::IntRect& rect, const std::string& texId, const std::string& name)
	: SpriteGameObject(texId, name)
	, rect(rect)
{
}
