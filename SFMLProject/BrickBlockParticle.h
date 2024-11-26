#pragma once

#include "SpriteGameObject.h"

class BrickBlockParticle : public SpriteGameObject
{
private:
	sf::IntRect textureRect;
	sf::Vector2f moveDirection;
	float rotationSpeed;

public:
	void SetMoveDirection(const sf::Vector2f& direction) { moveDirection = direction; }
	void StartMove(float height);
	void Start() override;

	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;

public:
	BrickBlockParticle(const sf::IntRect& rect, const std::string& texId, const std::string& name = "BrickBlockParticle");
	virtual ~BrickBlockParticle() = default;
	BrickBlockParticle& operator= (const BrickBlockParticle& other) = delete;
};

