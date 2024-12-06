#pragma once

#include "AnimationGameObject.h"

class AwakeGroundAttackDelay : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void Start() override;
public:
	AwakeGroundAttackDelay(const std::string& name = "AwakeGroundAttackDelay");
	virtual ~AwakeGroundAttackDelay() = default;
	AwakeGroundAttackDelay& operator= (const AwakeGroundAttackDelay& other) = delete;
};

