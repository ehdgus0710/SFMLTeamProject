#include "stdafx.h"
#include "CollisionPoint.h"


CollisionPoint::CollisionPoint()
	: Collision(ColliderType::Point)
{
	vertexPoint.resize(1);
}

CollisionPoint::~CollisionPoint()
{
}

void CollisionPoint::SetOrigin(const Origins& origins)
{
}

void CollisionPoint::Init()
{
}

void CollisionPoint::Reset()
{
}

void CollisionPoint::Update()
{
}

void CollisionPoint::Render(sf::RenderWindow& renderWindow)
{
	if (collisionCount > 0)
		vertexPoint[0].color = sf::Color::Red;
	else
		vertexPoint[0].color = sf::Color::Green;

	renderWindow.draw(vertexPoint);
}

void CollisionPoint::SetPosition(const sf::Vector2f& pos)
{
	vertexPoint[0].position = pos;
	position = pos;
}