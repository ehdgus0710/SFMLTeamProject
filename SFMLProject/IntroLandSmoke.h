#pragma once

#include "AnimationGameObject.h"

class IntroLandSmoke : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void Start() override;
public:
	IntroLandSmoke(const std::string& name = "IntroLandSmoke");
	virtual ~IntroLandSmoke() = default;
	IntroLandSmoke& operator= (const IntroLandSmoke& other) = delete;
};

