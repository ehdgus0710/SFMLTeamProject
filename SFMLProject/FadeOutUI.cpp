#include "stdafx.h"
#include "FadeOutUI.h"


FadeOutUI::FadeOutUI(const std::string& name)
	: UIGameObject(name)
	, isEndFadeInOut(false)
	, isStartFadeInOut(false)
	, currentAlpha(0.f)
	, isFadeIn(false)
	, currentTime(0.f)
	, fadeTime(1.f)
{
	currentColor = sf::Color::Black;
	currentColor.a = 0;
	fadeOutRect.setFillColor(currentColor);
}


void FadeOutUI::EndFadeOut()
{
	if (!isEndFadeInOut)
		return;

	for (auto& endEvnet : fadeOutEndEvenets)
	{
		if (endEvnet)
			endEvnet();
	}

	isEndFadeInOut = false;
	fadeOutEndEvenets.clear();
}

void FadeOutUI::StartFadeOut(float time)
{
	if (isStartFadeInOut)
		return;

	for (auto& startEvenet : fadeOutStartEvenets)
	{
		if (startEvenet)
			startEvenet();
	}
	fadeOutStartEvenets.clear();

	fadeTime = time;
	currentTime = 0.f;
	currentColor = sf::Color::Black;
	currentColor.a = 0;
	currentAlpha = 0.f;
	fadeOutRect.setFillColor(currentColor);
	isStartFadeInOut = true;
}

void FadeOutUI::EndFadeIn()
{
	if (!isEndFadeInOut)
		return;

	for (auto& endEvnet : fadeInEndEvenets)
	{
		if (endEvnet)
			endEvnet();
	}

	isFadeIn = false;
	isEndFadeInOut = false;
	fadeInEndEvenets.clear();
}

void FadeOutUI::StartFadeIn(float time)
{
	if (isStartFadeInOut)
		return;

	for (auto& startEvenet : fadeInStartEvenets)
	{
		if (startEvenet)
			startEvenet();
	}
	fadeInStartEvenets.clear();

	fadeTime = time;
	currentTime = 0.f;
	currentColor = sf::Color::Black;
	currentColor.a = 255;
	currentAlpha = 255.f;
	fadeOutRect.setFillColor(currentColor);
	isStartFadeInOut = true;
	isFadeIn = true;
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
	if (!isStartFadeInOut)
		return;

	currentTime += TimeManager::GetInstance().GetUnScaleDeletaTime();

	if (isFadeIn)
		currentAlpha = Utils::Lerp(255, 0, currentTime / fadeTime);
	else
		currentAlpha = Utils::Lerp(0, 255, currentTime / fadeTime);

	currentColor.a = (unsigned int)currentAlpha;
	fadeOutRect.setFillColor(currentColor);

	if (currentTime >= fadeTime)
	{
		isEndFadeInOut = true;
		isStartFadeInOut = false;

		if (isFadeIn)
			EndFadeIn();
		else
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