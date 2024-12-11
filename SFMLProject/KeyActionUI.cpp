#include "stdafx.h"
#include "KeyActionUI.h"

KeyActionUI::KeyActionUI(const std::string& actionName, const ActionKeyType& actionKey, const std::string& textId, const std::string& name, unsigned int textSize, const sf::Color& textColor)
	: TextButton(textId, name, textSize, textColor)
	, isOnInputChangeKey(false)
	, actionKeyType(actionKey)
{
	actionText.setFillColor(textColor);
	actionText.setString(actionName);
	actionText.setCharacterSize(textSize);
	actionKeyPosition = sf::Vector2f::left * 200.f;

	KeyActionManager::GetInstance().SetChangeActionKeyEvent(actionKeyType, std::bind(&KeyActionUI::OnChangeKeyName, this, std::placeholders::_1));
}

KeyActionUI::KeyActionUI(const std::string& actionName, const ActionKeyType& actionKey, const std::string& textId, const std::string& name, unsigned int textSize, const sf::Color& textColor, const sf::Color& changeColor)
	: TextButton(textId, name, textSize, textColor, changeColor)
	, isOnInputChangeKey(false)
	, actionKeyType(actionKey)
{
	actionText.setFillColor(textColor);
	actionText.setString(actionName);
	actionText.setCharacterSize(textSize);
	actionKeyPosition = sf::Vector2f::left * 200.f;

	KeyActionManager::GetInstance().SetChangeActionKeyEvent(actionKeyType, std::bind(&KeyActionUI::OnChangeKeyName, this, std::placeholders::_1));
}

void KeyActionUI::ChangeAction(const sf::Keyboard::Key& chageKey)
{
	if (chageKey == sf::Keyboard::Escape)
		return;

	KeyActionManager::GetInstance().ChangeActionKey(actionKeyType, chageKey);
}

void KeyActionUI::OnChangeKeyName(const sf::Keyboard::Key& chageKey)
{
	SetString("A");
}

void KeyActionUI::OnInputKey()
{
	isOnInputChangeKey = true;
}

void KeyActionUI::OnCollisionEnterChangeColor()
{
	textColor = changeColor;
	text.setFillColor(textColor);
	actionText.setFillColor(textColor);
}

void KeyActionUI::OnCollisionStayChangeColor()
{
}

void KeyActionUI::OnCollisionEndChangeColor()
{
	textColor = defalutColor;
	text.setFillColor(textColor);
	actionText.setFillColor(textColor);
}

void KeyActionUI::Start()
{
	TextButton::Start();
	actionText.setFillColor(textColor);
}

void KeyActionUI::Update(const float& deltaTime)
{
	if (isOnInputChangeKey)
	{
		if (InputManager::GetInstance().GetInputKey())
		{
			ChangeAction(InputManager::GetInstance().GetInputKeyCode());
			isOnInputChangeKey = false;
		}
	}
}

void KeyActionUI::SetPosition(const sf::Vector2f& pos)
{
	TextButton::SetPosition(pos);
	actionText.setPosition(pos + actionKeyPosition);
}

void KeyActionUI::SetOrigin(Origins preset)
{
	TextButton::SetOrigin(preset);
	Utils::SetOrigin(actionText, preset);
}

void KeyActionUI::SetOrigin(const sf::Vector2f& newOrigin)
{
	TextButton::SetOrigin(newOrigin);
	actionText.setOrigin(newOrigin);
}

void KeyActionUI::Render(sf::RenderWindow& window)
{
	window.draw(text);
	window.draw(actionText);
}
