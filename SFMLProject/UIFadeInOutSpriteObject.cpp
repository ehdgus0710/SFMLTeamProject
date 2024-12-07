#include "stdafx.h"
#include "UIFadeInOutSpriteObject.h"

UIFadeInOutSpriteObject::UIFadeInOutSpriteObject(const std::string& texId, const std::string& name)
	: UISpriteGameObject(texId, name)
	, isEndFadeInOut(false)
	, isStartFadeInOut(false)
	, currentAlpha(0.f)
	, isFadeIn(false)
	, currentTime(0.f)
	, fadeTime(1.f)
{
}


void UIFadeInOutSpriteObject::EndFadeOut()
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

void UIFadeInOutSpriteObject::StartFadeOut(float time)
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
	currentColor = sprite.getColor();
	currentColor.a = 0;
	currentAlpha = 0.f;
	sprite.setColor(currentColor);
	isStartFadeInOut = true;
}

void UIFadeInOutSpriteObject::EndFadeIn()
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

void UIFadeInOutSpriteObject::StartFadeIn(float time)
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
	currentColor = sprite.getColor();
	currentColor.a = 255;
	currentAlpha = 255.f;
	sprite.setColor(currentColor);
	isStartFadeInOut = true;
	isFadeIn = true;
}
void UIFadeInOutSpriteObject::Update(const float& deltaTime)
{
	if (!isStartFadeInOut)
		return;

	currentTime += TimeManager::GetInstance().GetUnScaleDeletaTime();

	if (isFadeIn)
		currentAlpha = Utils::Lerp(255, 0, currentTime / fadeTime);
	else
		currentAlpha = Utils::Lerp(0, 255, currentTime / fadeTime);

	currentColor.a = (unsigned int)currentAlpha;
	sprite.setColor(currentColor);

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