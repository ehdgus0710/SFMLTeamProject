#include "stdafx.h"
#include "UITextGameObject.h"

UITextGameObject::UITextGameObject(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor)
	: UIGameObject(name)
	, textId(textId)
	, textSize(textSize)
	, textColor(textColor)
{
}

void UITextGameObject::Awake()
{
	text.setFont(ResourcesManager<sf::Font>::GetInstance().Get(textId));
	SetOrigin(originPreset);

	text.setFillColor(textColor);
	text.setCharacterSize(textSize);
	text.setString(textString);
}

void UITextGameObject::Start()
{
	text.setFont(ResourcesManager<sf::Font>::GetInstance().Get(textId));
	SetPosition(position);
	text.setFillColor(textColor);
	text.setCharacterSize(textSize);
	text.setString(textString);
	SetOrigin(originPreset);
}

void UITextGameObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	Utils::SetOrigin(text, preset);
}

void UITextGameObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	text.setOrigin(origin);
}

void UITextGameObject::SetPosition(const sf::Vector2f& pos)
{
	UIGameObject::SetPosition(pos);
	text.setPosition(pos);
}

void UITextGameObject::SetString(const std::string& string)
{
	textString = std::wstring(string.begin(), string.end());
	text.setString(textString);
	SetScale({ (float)textString.length() * (float)textSize * 0.5f , (float)textSize });
}

void UITextGameObject::SetString(const std::wstring& string)
{
	textString = string;
	text.setString(string);
	SetScale({ (float)textString.length() * (float)textSize * 0.5f , (float)textSize });
}

void UITextGameObject::Update(const float& deltaTime)
{
	UIGameObject::Update(deltaTime);
}

void UITextGameObject::FixedUpdate(const float& deltaTime)
{
	UIGameObject::FixedUpdate(deltaTime);
}

void UITextGameObject::LateUpdate(const float& deltaTime)
{
	UIGameObject::LateUpdate(deltaTime);
}

sf::FloatRect UITextGameObject::GetLocalBounds() const
{
	return text.getLocalBounds();
}

sf::FloatRect UITextGameObject::GetGlobalBounds() const
{
	return text.getGlobalBounds();
}

void UITextGameObject::Render(sf::RenderWindow& window)
{
	UIGameObject::Render(window);
	window.draw(text);
}
