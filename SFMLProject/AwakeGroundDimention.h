#pragma once

#include "AnimationGameObject.h"

class AwakeGroundDimention : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void Start() override;
public:
	AwakeGroundDimention(const std::string& name = "Dimension");
	virtual ~AwakeGroundDimention() = default;
	AwakeGroundDimention& operator= (const AwakeGroundDimention& other) = delete;
};
