#pragma once
#include "AnimationHitBox.h"

class AroundDimention : public AnimationHitBox
{
protected:

public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;
	void CreateAnimator() override;
public:
	AroundDimention(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name = "HitBox");
	virtual ~AroundDimention() = default;
	AroundDimention& operator= (const AroundDimention& other) = delete;

};

