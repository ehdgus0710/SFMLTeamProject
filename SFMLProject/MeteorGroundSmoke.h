#pragma once

#include "AnimationGameObject.h"

class MeteorGroundSmoke : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void Start() override;
public:
	MeteorGroundSmoke(const std::string& name = "MeteorGroundSmoke");
	virtual ~MeteorGroundSmoke() = default;
	MeteorGroundSmoke& operator= (const MeteorGroundSmoke& other) = delete;
};

