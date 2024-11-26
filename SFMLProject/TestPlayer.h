#pragma once

#include "SpriteGameObject.h"
#include "Rigidbody.h"

class TestPlayer : public SpriteGameObject
{
protected:
	sf::Vector2f	moveDirection;

	float speed;
	bool			isJump;

public:
	void InputMove();
	void InputJump();

public:
	void Awake() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	TestPlayer(const std::string& texId, const std::string& name = "");
	virtual ~TestPlayer();
	TestPlayer& operator= (const TestPlayer& other) = delete;
};

