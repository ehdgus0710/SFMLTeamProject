#pragma once

#include "Collision.h"

class CollisionCircle : public Collision
{
private:
	float radian;
	sf::CircleShape collisionCircle;

public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRadian(float radian);
	
	float GetRadian() const { return radian; }
	void SetScale(const sf::Vector2f& scale) override;
	sf::Vector2f GetScale() const override { return sf::Vector2f::one * radian; };

	void SetOrigin(const sf::Vector2f& origin);
	void SetOrigin(const Origins& origins) override;

	sf::FloatRect GetLocalBounds() { return collisionCircle.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() { return collisionCircle.getGlobalBounds(); }

public:
	void Init() override;
	void Reset() override;
	void Update() override;
	virtual void Render(sf::RenderWindow& renderWindow);
public:
	CollisionCircle(float radian);
	~CollisionCircle();
};

