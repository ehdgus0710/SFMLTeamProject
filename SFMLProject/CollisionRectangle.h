#pragma once

#include "Collision.h"

class CollisionRectangle : public Collision
{
private:
	sf::RectangleShape rectanleRender;

public:
	void SetScale(const sf::Vector2f& scale) override;
	sf::Vector2f GetScale() const override { return rectanleRender.getSize(); }

	Rectangle GetRectangle() { return Rectangle(position, rectanleRender.getSize()); }
	sf::FloatRect GetGlobalBounds() { return rectanleRender.getGlobalBounds(); }
	sf::FloatRect GetLocalBounds() { return rectanleRender.getLocalBounds(); }

	const sf::Transform& GetTransform() { return rectanleRender.getTransform(); }

	void SetPosition(const sf::Vector2f& pos) override;

	void SetRotation(float angle) override;

	sf::Vector2f GetLeftTopPosition() { return { GetLeftPosition(),GetTopPosition() }; }
	sf::Vector2f GetRightBottomPosition() { return { GetRightPosition(),GetBottomPosition() }; }
	sf::Vector2f GetRightTopPosition() { return { GetRightPosition(),GetTopPosition() }; }
	sf::Vector2f GetLeftBottomPosition() { return { GetLeftPosition(),GetBottomPosition() }; }

	float GetLeftPosition() { return position.x - rectanleRender.getSize().x * 0.5f; }
	float GetRightPosition() { return position.x + rectanleRender.getSize().x * 0.5f; }
	float GetTopPosition() { return  position.y - rectanleRender.getSize().y * 0.5f; }
	float GetBottomPosition() { return position.y + rectanleRender.getSize().y * 0.5f; }

	void SetOrigin(const Origins& origins) override;
public:
	void Init() override;
	void Reset() override;
	void Update() override;
	void Render(sf::RenderWindow& renderWindow) override;

public:
	CollisionRectangle(sf::Vector2f size = sf::Vector2f::one);
	~CollisionRectangle();

};

