#include "stdafx.h"
#include "UIFadeTextGameObject.h"

UIFadeTextGameObject::UIFadeTextGameObject(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor)
	: UITextGameObject(textId, name, textSize, textColor)
	, isEndFadeInOut(false)
	, isStartFadeInOut(false)
	, currentAlpha(0.f)
	, isFadeIn(false)
	, currentTime(0.f)
	, fadeTime(1.f)
{
	currentColor = textColor;
}

void UIFadeTextGameObject::EndFadeOut()
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

void UIFadeTextGameObject::StartFadeOut(float time)
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
	currentColor.a = 0;
	currentAlpha = 0.f;
	text.setFillColor(currentColor);
	isStartFadeInOut = true;
}

void UIFadeTextGameObject::EndFadeIn()
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

void UIFadeTextGameObject::StartFadeIn(float time)
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
	currentColor.a = 255;
	currentAlpha = 255.f;
	text.setFillColor(currentColor);
	isStartFadeInOut = true;
	isFadeIn = true;
}
void UIFadeTextGameObject::Update(const float& deltaTime)
{
	if (!isStartFadeInOut)
		return;

	currentTime += TimeManager::GetInstance().GetUnScaleDeletaTime();

	if (isFadeIn)
		currentAlpha = Utils::Lerp(255, 0, currentTime / fadeTime);
	else
		currentAlpha = Utils::Lerp(0, 255, currentTime / fadeTime);

	currentColor.a = (unsigned int)currentAlpha;
	text.setFillColor(currentColor);

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