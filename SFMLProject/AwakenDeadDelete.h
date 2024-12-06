#pragma once

#include "AnimationGameObject.h"

class AwakenDeadDelete : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
public:
	void Start() override;
public:
	AwakenDeadDelete(const std::string& name = "AwakenDeadEnd");
	virtual ~AwakenDeadDelete() = default;
	AwakenDeadDelete& operator= (const AwakenDeadDelete& other) = delete;
};

