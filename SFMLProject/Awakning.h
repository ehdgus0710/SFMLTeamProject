#pragma once

#include "AnimationGameObject.h"

class Awakning : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void Start() override;
public:
	Awakning(const std::string& name = "AwakenNing");
	virtual ~Awakning() = default;
	Awakning& operator= (const Awakning& other) = delete;
};

