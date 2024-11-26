#pragma once
#include "GameObject.h"
class UIGameObject : public GameObject
{
public:
	void Awake() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void Render(sf::RenderWindow& renderWindow) override;
	void Start() override;

	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
public:
	UIGameObject(const std::string& texId);
	virtual ~UIGameObject() = default;
	UIGameObject& operator= (const UIGameObject& other) = delete;
};

