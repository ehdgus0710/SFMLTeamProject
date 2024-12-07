#pragma once

#include "AnimationBullet.h"

class Reiana;
class HitBoxObject;
class AnimationGameObject;

class RisingReady : public AnimationBullet
{
protected:
	AnimationGameObject* effect1;
	Reiana* reiana;
	sf::Vector2f risingReadyPos{ 55.f,0.f };
	float				delayTime = 1.0f;
	float				currentDelay = 0.f;
public:
	void Start() override;
	void Update(const float& deltaTime) override;

	sf::Vector2f GetEffectPos();
	void setDelay(float delay);
public:
	RisingReady(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name = "RisingReady");
	virtual ~RisingReady() = default;
	RisingReady& operator= (const RisingReady& other) = delete;
};