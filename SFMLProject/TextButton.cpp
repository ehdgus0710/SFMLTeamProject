#include "stdafx.h"
#include "TextButton.h"
#include "Scene.h"

TextButton::TextButton(const std::string& textId, const std::string& name, unsigned int textSize, const  sf::Color& textColor)
	: UIButtonObject(textId, name, textSize, textColor)
{
}

TextButton::TextButton(const std::string& textId, const std::string& name, unsigned int textSize, const sf::Color& textColor, const sf::Color& changeColor)
	: UIButtonObject(textId, name, textSize, textColor)
	, changeColor(changeColor)
	, defalutColor(textColor)
{
}


void TextButton::SetChangeColor(const sf::Color& color)
{
	defalutColor = textColor;
	changeColor = color;
}

void TextButton::OnCollisionEnter(Collider* target)
{
	textColor = changeColor;
	text.setFillColor(textColor);
}

void TextButton::OnCollisionStay(Collider* target)
{
	if (InputManager::GetInstance().GetKeyUp(sf::Mouse::Left))
	{
		for (auto& buttonEvent : buttonClickEvents)
		{
			if(buttonEvent)
				buttonEvent();
		}
	}
}

void TextButton::OnCollisionEnd(Collider* target)
{
	textColor = defalutColor;
	text.setFillColor(textColor);
}