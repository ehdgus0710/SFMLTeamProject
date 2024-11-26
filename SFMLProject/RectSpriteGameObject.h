#pragma once
#include "SpriteGameObject.h"
class RectSpriteGameObject : public SpriteGameObject
{
protected:
	sf::IntRect rect;

public:
	void Start() override;
	void SetScale(const sf::Vector2f& scale) override;

public:
	RectSpriteGameObject(const sf::IntRect& rect, const std::string& texId, const std::string& name = "");
	virtual ~RectSpriteGameObject() = default;
	RectSpriteGameObject& operator= (const RectSpriteGameObject& other) = delete;
};

