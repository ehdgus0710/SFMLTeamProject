#pragma once

#include "AnimationGameObject.h"

class AwakenDimention : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void Start() override;
	void OnAttack();
public:
	AwakenDimention(const std::string& name = "AwakenDimention");
	virtual ~AwakenDimention() = default;
	AwakenDimention& operator= (const AwakenDimention& other) = delete;
};

