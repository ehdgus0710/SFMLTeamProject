#pragma once

#include "AnimationGameObject.h"

class AwakeDemensionWaitEffect : public AnimationGameObject
{
protected:
	sf::Vector2f			moveDirection;
	sf::Vector2f			changePos;
	sf::Vector2f			randomPos;
	float					changeRot;
	float					randomRot;

public:
	void Start() override;
	void ChangeAttackAnimation();
public:
	AwakeDemensionWaitEffect(const std::string& name = "AwakeDemensionWaitEffect");
	virtual ~AwakeDemensionWaitEffect() = default;
	AwakeDemensionWaitEffect& operator= (const AwakeDemensionWaitEffect& other) = delete;
};

