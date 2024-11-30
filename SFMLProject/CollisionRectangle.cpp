#include "stdafx.h"

#include "CollisionRectangle.h"

CollisionRectangle::CollisionRectangle(sf::Vector2f size)
	: Collision(ColliderType::Rectangle)
	, rectanleRender(size)
{
	scale = size;
	Init();
}

CollisionRectangle::~CollisionRectangle()
{
}

void CollisionRectangle::SetOrigin(const Origins& origins)
{
	originPosition = Utils::SetOrigin(rectanleRender, origins);
	originsPreset = origins;
}

void CollisionRectangle::Init()
{
	rectanleRender.setFillColor(sf::Color::Transparent);
	rectanleRender.setOutlineColor(sf::Color::Green);
	rectanleRender.setOutlineThickness(1);
	SetScale(scale);
}

void CollisionRectangle::Update()
{
	Collision::Update();
}

void CollisionRectangle::Render(sf::RenderWindow& renderWindow)
{
	if (collisionCount > 0)
		rectanleRender.setOutlineColor(sf::Color::Red);
	else
		rectanleRender.setOutlineColor(sf::Color::Green);

	renderWindow.draw(rectanleRender);
}

void CollisionRectangle::Reset()
{ 
	rectanleRender.setSize(scale);
	rectanleRender.setPosition(position);
	SetOrigin(originsPreset);
}

void CollisionRectangle::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	//rectanglePosition.SetSize(scale);
	rectanleRender.setSize(scale);

	SetOrigin(originsPreset);
}

void CollisionRectangle::SetPosition(const sf::Vector2f& pos)
{
	rectanleRender.setPosition(pos);
	Collision::SetPosition(pos);
}

void CollisionRectangle::SetRotation(float angle)
{
	rectanleRender.setRotation(angle);
	rotation = angle;
}
