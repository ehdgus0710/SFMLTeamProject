#pragma once

#include "AnimationGameObject.h"

class Dimension : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void OnAttack();
public:
	void Start() override;
public:
	Dimension(const std::string& name = "Dimension");
	virtual ~Dimension() = default;
	Dimension& operator= (const Dimension& other) = delete;
};

