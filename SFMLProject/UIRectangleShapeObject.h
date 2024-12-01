#pragma once
#include "UIGameObject.h"
class UIRectangleShapeObject :
    public UIGameObject
{
protected:
	sf::RectangleShape		rectangleShape;
	std::string				textureId;
	//sf::Texture

public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
public:
	void Render(sf::RenderWindow& renderWindow) override;
	void Start() override;

	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
public:
	UIRectangleShapeObject(const std::string& texId, const std::string& name = "");
	virtual ~UIRectangleShapeObject() = default;
	UIRectangleShapeObject& operator= (const UIRectangleShapeObject& other) = delete;
};

