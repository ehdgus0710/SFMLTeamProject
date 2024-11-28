#pragma once

#include "AnimationBullet.h"

class Knife : public AnimationBullet
{
protected:
	float				delayTime = 0.5f;
	float				currentDelay = 0.f;
public:
	void Start() override;
	void Update(const float& deltaTime) override;

public:
	Knife(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name = "Knife");
	virtual ~Knife() = default;
	Knife& operator= (const Knife& other) = delete;
};

