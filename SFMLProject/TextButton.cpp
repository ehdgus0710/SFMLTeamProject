#include "stdafx.h"
#include "TextButton.h"
#include "Scene.h"

TextButton::TextButton(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor)
	: UIButtonObject(textId, name, textSize, textColor)
{
}

void TextButton::OnCollisionEnter(Collider* target)
{
	textColor = sf::Color::Red;
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
	textColor = sf::Color::White;
	text.setFillColor(textColor);
}
