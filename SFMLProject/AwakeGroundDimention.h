#pragma once

#include "AnimationGameObject.h"

class AwakeGroundDimention : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void Start() override;
	void OnAttack();
public:
	AwakeGroundDimention(const std::string& name = "AwakeGroundDimention");
	virtual ~AwakeGroundDimention() = default;
	AwakeGroundDimention& operator= (const AwakeGroundDimention& other) = delete;
};

