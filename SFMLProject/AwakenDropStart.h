#pragma once

#include "AnimationGameObject.h"

class AwakenDropStart : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void Start() override;
public:
	AwakenDropStart(const std::string& name = "AwakenDropStartEffect");
	virtual ~AwakenDropStart() = default;
	AwakenDropStart& operator= (const AwakenDropStart& other) = delete;
};

