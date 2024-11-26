#pragma once
#include "UITextGameObject.h"
class UIButtonObject : public UITextGameObject
{
protected:
	std::vector<std::function<void()>> buttonCollsionEnterEvents;
	std::vector<std::function<void()>> buttonClickEvents;
	std::vector<std::function<void()>> buttonCollsionEndClickEvents;

	sf::Vector2f colliderSize;
	sf::Vector2f buttonSize;
public:
	void SetButtonSize(const sf::Vector2f& size);
	void SetColliderSize(const sf::Vector2f& size);
	void SetButtonClickEvent(std::function<void()> buttonEvent) { buttonClickEvents.push_back(buttonEvent); }

public:
	void Start() override;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;


	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

public:
	UIButtonObject(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor = sf::Color::White);
	virtual ~UIButtonObject() = default;
	//UiTextureGameObject(const UiTextureGameObject& other) = delete;
	UIButtonObject& operator= (const UIButtonObject& other) = delete;
};

