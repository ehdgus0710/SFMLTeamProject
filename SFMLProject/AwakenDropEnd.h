#pragma once

#include "AnimationGameObject.h"

class AwakenDropEnd : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void Start() override;
public:
	AwakenDropEnd(const std::string& name = "AwakenDropEnd");
	virtual ~AwakenDropEnd() = default;
	AwakenDropEnd& operator= (const AwakenDropEnd& other) = delete;
};

