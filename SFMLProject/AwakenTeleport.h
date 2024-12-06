#pragma once

#include "AnimationGameObject.h"

class AwakenTeleport : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void Start() override;
public:
	AwakenTeleport(const std::string& name = "AwakenTeleport");
	virtual ~AwakenTeleport() = default;
	AwakenTeleport& operator= (const AwakenTeleport& other) = delete;
};

