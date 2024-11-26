#pragma once
#include "GameObject.h"
class MouseObject : public GameObject
{
public:
	void Awake() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void Render(sf::RenderWindow& renderWindow) override;
	void Start() override;

	void Update(const float& deltaTime) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
public:
	MouseObject(const std::string& name = "Mouse");
	virtual ~MouseObject() = default;
	MouseObject& operator= (const MouseObject& other) = delete;
};

