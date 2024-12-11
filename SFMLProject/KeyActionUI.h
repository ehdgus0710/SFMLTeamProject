#pragma once
#include "TextButton.h"
class KeyActionUI : public TextButton
{
private:
	sf::Text		actionText;
	sf::Vector2f	actionKeyPosition;
	ActionKeyType	actionKeyType;
	bool			isOnInputChangeKey;
public:
	void ChangeAction(const sf::Keyboard::Key& chageKey);
	void OnChangeKeyName(const sf::Keyboard::Key& chageKey);
	void OnInputKey();
	void OnCollisionEnterChangeColor() override;
	void OnCollisionStayChangeColor() override;
	void OnCollisionEndChangeColor() override;

public:
	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Start() override;
	void Update(const float& deltaTime) override;
	void Render(sf::RenderWindow& renderWindow) override;
public:
	KeyActionUI(const std::string& actionName,const ActionKeyType& actionKey, const std::string& textId, const std::string& name, unsigned int textSize, const sf::Color& textColor = sf::Color::White);
	KeyActionUI(const std::string& actionName,const ActionKeyType& actionKey, const std::string& textId, const std::string& name, unsigned int textSize, const sf::Color& textColor, const sf::Color& changeColor);
	virtual ~KeyActionUI() = default;
	//UiTextureGameObject(const UiTextureGameObject& other) = delete;
	KeyActionUI& operator= (const KeyActionUI& other) = delete;
};

