#pragma once

#include "Collision.h"

class CollisionPoint : public Collision
{
private:
	sf::VertexArray vertexPoint;

public:	
	void SetPosition(const sf::Vector2f& pos) override;
	sf::Vector2f GetScale() const override { return sf::Vector2f::one; };

	void SetOrigin(const Origins& origins) override;

	sf::FloatRect GetLocalBounds() { return vertexPoint.getBounds(); }
	sf::FloatRect GetGlobalBounds() { return vertexPoint.getBounds(); }
public:
	void Init() override;
	void Reset() override;
	void Update() override;
	virtual void Render(sf::RenderWindow& renderWindow);

public:
	CollisionPoint();
	~CollisionPoint();
};

