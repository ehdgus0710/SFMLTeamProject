#pragma once

#include "UIGameObject.h"

class UIAnimationObject : public UIGameObject
{
protected:
	sf::Sprite		sprite;
	sf::Vector2f	rectSize;

public:
	void SetPosition(const sf::Vector2f& pos) override; 
	void SetScale(const sf::Vector2f& scale) override;
	void Render(sf::RenderWindow& renderWindow) override;
	void Start() override;

	void Update(const float& deltaTime) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void CreateAnimator() override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	UIAnimationObject(const std::string& name);
	virtual ~UIAnimationObject() = default;
	UIAnimationObject& operator= (const UIAnimationObject& other) = delete;
};
