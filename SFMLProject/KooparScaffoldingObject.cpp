#include "stdafx.h"
#include "KooparScaffoldingObject.h"

#include "Collider.h"
#include "Koopa.h"
#include "Enemy.h"

KooparScaffoldingObject::KooparScaffoldingObject(const std::string& texId, const std::string& name)
	: SpriteGameObject(texId, name)
	, textureRect(textureRect)
{
	scale = sf::Vector2f(4.f, 4.f);
	textureRect = { 64, 16 * 24 , 16, 16 };
}


void KooparScaffoldingObject::Start()
{
	sprite.setTextureRect(textureRect);
	sprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get(textureId));
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
}

void KooparScaffoldingObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	sprite.setScale(scale);
}
