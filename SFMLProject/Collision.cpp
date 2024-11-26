#include "stdafx.h"
#include "Collision.h"

void Collision::Update()
{
	//collionSprite.setPosition(position);
}

void Collision::Render(sf::RenderWindow& renderWindow)
{
}

void Collision::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
}

Collision::Collision(ColliderType colliderType)
	: colliderType(colliderType)
	, collisionCount(0)
	, rotation(0.f)
	, scale(sf::Vector2f::one)
	, originsPreset(Origins::MiddleCenter)
{
	//
}
