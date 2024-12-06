#pragma once

#include "AnimationGameObject.h"
class AnimationHitBox;

class AwakenDropSide : public AnimationGameObject
{
protected:
	AnimationHitBox*		animationHitBox;
	sf::Vector2f			moveDirection;
	float					speed = 100.f;
	bool					setPos = false;
	bool					setPosLeft = false;
public:
	void Start() override;
	void Delete();
public:
	AwakenDropSide(const std::string& name = "AwakenDropSideEffect");
	void Move(float deltaTime, sf::Vector2f pos);
	void Move2(float deltaTime, sf::Vector2f pos);
	virtual ~AwakenDropSide() = default;
	AwakenDropSide& operator= (const AwakenDropSide& other) = delete;
};

