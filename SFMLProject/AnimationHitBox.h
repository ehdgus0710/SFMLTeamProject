#pragma once
#include "HitBoxObject.h"
class AnimationHitBox : public HitBoxObject
{
protected:
	sf::Sprite sprite;

public:
	void Start() override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;


	void Update(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;
	void CreateAnimator() override;
public:
	AnimationHitBox(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name = "HitBox");
	virtual ~AnimationHitBox() = default;
	AnimationHitBox& operator= (const AnimationHitBox& other) = delete;
};

