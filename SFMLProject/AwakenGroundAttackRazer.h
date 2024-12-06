#pragma once

#include "AnimationGameObject.h"

class AwakenGroundAttackRazer : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void Start() override;
public:
	AwakenGroundAttackRazer(const std::string& name = "AwakenDropStartEffect");
	virtual ~AwakenGroundAttackRazer() = default;
	AwakenGroundAttackRazer& operator= (const AwakenGroundAttackRazer& other) = delete;
};

