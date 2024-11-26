#pragma once

#include "SpriteGameObject.h"

class Test : public SpriteGameObject
{
public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetSpriteRect();

	void Awake() override;

	void Start() override;
	void Update(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

public:
	Test(const std::string& texId, const std::string& name = "");
	virtual ~Test();
};

