#pragma once

#include "AnimationBullet.h"

class Reiana;
class HitBoxObject;
class AnimationGameObject;

class Rising : public AnimationBullet
{
protected:
	Reiana* reiana;
	AnimationGameObject* effect1;
	float				delayTime = 0.5f;
	float				currentDelay;
public:
	void Start() override;
	void Update(const float& deltaTime) override;

	void setDelay(float delay);

	void OnCreateHitBox();
	void OnDestoryHitBox();

	void SetPosition(const sf::Vector2f& pos) override;

public:
	Rising(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name = "Rising");
	virtual ~Rising() = default;
	Rising& operator= (const Rising& other) = delete;
};