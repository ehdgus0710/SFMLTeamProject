#include "stdafx.h"
#include "FadeOutUI.h"


FadeOutUI::FadeOutUI(const std::string& name)
	: UIGameObject(name)
	, isFadeOutEnd(false)
	, isStartFadeOut(false)
	, currentAlpha(0.f)
	, speed(300.f)
{
	currentColor = sf::Color::Black;
	currentColor.a = 0;
	fadeOutRect.setFillColor(currentColor);
}


void FadeOutUI::EndFadeOut()
{
	if (!isFadeOutEnd)
		return;

	for (auto& endEvnet : fadeOutEndEvenets)
	{
		if (endEvnet)
			endEvnet();
	}

	isFadeOutEnd = false;
	fadeOutEndEvenets.clear();
}

void FadeOutUI::StartFadeOut()
{
	if (isStartFadeOut)
		return;

	for (auto& startEvenet : fadeOutStartEvenets)
	{
		if (startEvenet)
			startEvenet();
	}
	fadeOutStartEvenets.clear();

	currentColor = sf::Color::Black;
	currentColor.a = 0;
	currentAlpha = 0.f;
	fadeOutRect.setFillColor(currentColor);
	isStartFadeOut = true;
}

void FadeOutUI::SetPosition(const sf::Vector2f& pos)
{
	fadeOutRect.setPosition(pos);
	position = pos;
}

void FadeOutUI::SetScale(const sf::Vector2f& scale)
{
	fadeOutRect.setSize(scale);
	this->scale = scale;
}

void FadeOutUI::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(fadeOutRect);
}

void FadeOutUI::Start()
{
	SetPosition(position);
	SetScale(scale);
	SetOrigin(originPreset);
}

void FadeOutUI::Update(const float& deltaTime)
{
	if (!isStartFadeOut)
		return;

	currentAlpha += speed * TimeManager::GetInstance().GetUnScaleDeletaTime();
	currentColor.a = (unsigned int)currentAlpha;
	fadeOutRect.setFillColor(currentColor);

	if (currentColor.a == 255)
	{
		isFadeOutEnd = true;
		isStartFadeOut = false;
		EndFadeOut();
	}
}
void FadeOutUI::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(fadeOutRect, preset);
	//UIGameObject::SetOrigin(preset);
}

void FadeOutUI::SetOrigin(const sf::Vector2f& newOrigin)
{
	fadeOutRect.setOrigin(newOrigin);
	//UIGameObject::SetOrigin(newOrigin);
}