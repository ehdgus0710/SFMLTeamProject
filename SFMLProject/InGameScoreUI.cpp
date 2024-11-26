#include "stdafx.h"
#include "InGameScoreUI.h"

InGameScoreUI::InGameScoreUI(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor)
	: UITextGameObject(textId, name, textSize, textColor)
	, currentLifeTime(0.f)
	, lifeTime(1.5f)
	, speed(100.f)
{
}

void InGameScoreUI::Start()
{
	UITextGameObject::Start();
	currentColor = textColor;
}

void InGameScoreUI::Update(const float& deltaTime)
{
	currentLifeTime += deltaTime;
	SetPosition(position + sf::Vector2f::up * speed * deltaTime);

	if (currentLifeTime >= lifeTime)
		OnDestory();
}
