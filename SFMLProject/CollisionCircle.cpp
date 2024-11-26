#include "stdafx.h"
#include "CollisionCircle.h"


CollisionCircle::CollisionCircle(float radian)
	: radian(radian)
	, Collision(ColliderType::Circle)
	, collisionCircle(radian)
{
	Init();
}

CollisionCircle::~CollisionCircle()
{
}

void CollisionCircle::Init()
{
	collisionCircle.setFillColor(sf::Color::Transparent);
	collisionCircle.setOutlineColor(sf::Color::Green);
	collisionCircle.setOutlineThickness(1);
	collisionCircle.setOrigin({ radian, radian });
}

void CollisionCircle::Reset()
{
	collisionCircle.setRadius(radian);
	collisionCircle.setPosition(position);
	collisionCircle.setOrigin(originPosition);
}

void CollisionCircle::Update()
{
	Collision::Update();
}

void CollisionCircle::Render(sf::RenderWindow& renderWindow)
{
	if (collisionCount > 0)
		collisionCircle.setOutlineColor(sf::Color::Red);
	else
		collisionCircle.setOutlineColor(sf::Color::Green);

	renderWindow.draw(collisionCircle);
}

void CollisionCircle::SetPosition(const sf::Vector2f& pos)
{ 
	collisionCircle.setPosition(pos);
	Collision::SetPosition(pos);
}

void CollisionCircle::SetRadian(float radian)
{
	this->radian = radian;
	scale.x = radian;
	scale.y = radian;
	collisionCircle.setRadius(radian);
}

void CollisionCircle::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	radian = scale.x <= scale.y ? scale.x : scale.y;
	radian *= 0.5f;
	collisionCircle.setRadius(radian);
}

void CollisionCircle::SetOrigin(const sf::Vector2f& origin)
{

}

void CollisionCircle::SetOrigin(const Origins& origins)
{
	originPosition = Utils::SetOrigin(collisionCircle, origins);
}
