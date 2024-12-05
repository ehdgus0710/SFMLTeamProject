#pragma once

#include "AnimationGameObject.h"

class AwakenDeadCreate : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void Start() override;
public:
	AwakenDeadCreate(const std::string& name = "AwakenDeadStart");
	virtual ~AwakenDeadCreate() = default;
	AwakenDeadCreate& operator= (const AwakenDeadCreate& other) = delete;
};

