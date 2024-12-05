#pragma once

#include "AnimationGameObject.h"

class AwakenDropSide : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void Start() override;
public:
	AwakenDropSide(const std::string& name = "AwakenDropSideEffect");
	virtual ~AwakenDropSide() = default;
	AwakenDropSide& operator= (const AwakenDropSide& other) = delete;
};

