#pragma once

#include "AnimationBullet.h"

class Reiana;
class HitBoxObject;

class RisingReady : public AnimationBullet
{
protected:
	Reiana* reiana;
	float				delayTime = 1.0f;
	float				currentDelay = 0.f;
public:
	void Start() override;
	void Update(const float& deltaTime) override;

	void setDelay(float delay);
public:
	RisingReady(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name = "RisingReady");
	virtual ~RisingReady() = default;
	RisingReady& operator= (const RisingReady& other) = delete;
};