#pragma once
#include "UIGameObject.h"
class UISpriteGameObject : public UIGameObject
{
protected:
	sf::Sprite	sprite;
	std::string textureId;
	//sf::Texture

public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void ChangeSprite(std::string changeTextureID);
public:
	void Render(sf::RenderWindow& renderWindow) override;
	void Start() override;

	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	void CreateAnimator() override;
	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
public:
	UISpriteGameObject(const std::string& texId, const std::string& name = "");
	virtual ~UISpriteGameObject() = default;
	UISpriteGameObject& operator= (const UISpriteGameObject& other) = delete;
};

