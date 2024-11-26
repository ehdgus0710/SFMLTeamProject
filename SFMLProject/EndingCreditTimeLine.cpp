#include "stdafx.h"
#include "EndingCreditTimeLine.h"
#include "GameManager.h"


EndingCreditTimeLine::EndingCreditTimeLine(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor)
	: UITextGameObject(textId, name, textSize, textColor)
	, isRender(false)
	, currentTime(0.f)
	, endTime(5.f)
{
}

void EndingCreditTimeLine::OnStartCreadit()
{
	isRender = true;
	InputManager::GetInstance().SetInputable(true);
}

void EndingCreditTimeLine::Update(const float& deltaTime)
{
	if (isRender)
	{
		currentTime += deltaTime;

		if (currentTime >= endTime)
		{
			SetActive(false);
			InputManager::GetInstance().SetInputable(false);
		}
	}
}

void EndingCreditTimeLine::Start()
{
	text.setFont(ResourcesManager<sf::Font>::GetInstance().Get(textId));
	SetPosition(position);
	text.setFillColor(textColor);
	text.setCharacterSize(textSize);
	text.setString(textString);
	SetOrigin(originPreset);
}

void EndingCreditTimeLine::Render(sf::RenderWindow& window)
{
	if (isRender)
	{
		UIGameObject::Render(window);
		window.draw(text);
	}
}