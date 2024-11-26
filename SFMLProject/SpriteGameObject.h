#pragma once
#include "GameObject.h"
class SpriteGameObject : public GameObject
{
protected:
	sf::Sprite sprite;
	std::string textureId;
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

	void CreateAnimator() override;
	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
public:
	SpriteGameObject(const std::string& texId, const std::string& name = "");
	virtual ~SpriteGameObject() = default;
	SpriteGameObject& operator= (const SpriteGameObject& other) = delete;
};

