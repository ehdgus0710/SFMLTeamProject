#pragma once

#include "AnimationBullet.h"

class Player;
class HitBoxObject;
class AnimationGameObject;

class Knife : public AnimationBullet
{
protected:
	Player* player;
	AnimationGameObject* effect1;
	float				delayTime = 1.0f;
	float				currentDelay = 0.f;
public:
	void Start() override;
	void Update(const float& deltaTime) override;

	void setDelay(float delay);

	void OnCreateHitBox();
	void OnDestoryHitBox();

public:
	Knife(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name = "Knife");
	virtual ~Knife() = default;
	Knife& operator= (const Knife& other) = delete;
};

