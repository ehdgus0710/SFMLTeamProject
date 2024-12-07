#pragma once
#include "Bullet.h"
class AnimationBullet : public Bullet
{
public:
	void Start() override;
	void Render(sf::RenderWindow& renderWindow) override;
public:
	AnimationBullet(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name = "Bullet");
	AnimationBullet(GameObject* owner, ColliderLayer thisLayerType, ColliderLayerMask targetLayerMask, const std::string& texId, const std::string& name = "Bullet");
	virtual ~AnimationBullet() = default;
	AnimationBullet& operator= (const AnimationBullet& other) = delete;
};

