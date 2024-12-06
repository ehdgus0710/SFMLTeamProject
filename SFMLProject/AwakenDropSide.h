#pragma once

#include "AnimationGameObject.h"

class AwakenDropSide : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
	float					speed = 100.f;
public:
	void Start() override;
	void Delete();
public:
	AwakenDropSide(const std::string& name = "AwakenDropSideEffect");
	void Move(float deltaTime);
	void Move2(float deltaTime);
	virtual ~AwakenDropSide() = default;
	AwakenDropSide& operator= (const AwakenDropSide& other) = delete;
};

