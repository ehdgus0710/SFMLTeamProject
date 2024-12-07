#pragma once
#include "UISpriteGameObject.h"
class UIFadeInOutSpriteObject : public UISpriteGameObject
{
protected:
	std::vector<std::function<void()>>	fadeOutStartEvenets;
	std::vector<std::function<void()>>	fadeOutEndEvenets;
	std::vector<std::function<void()>>	fadeInStartEvenets;
	std::vector<std::function<void()>>	fadeInEndEvenets;

	sf::Color currentColor;

	float currentAlpha;
	float currentTime;
	float fadeTime;

	bool isStartFadeInOut;
	bool isEndFadeInOut;
	bool isFadeIn;

public:
	void AddFadeOutStartEvent(std::function<void()> startEvent) { fadeOutStartEvenets.push_back(startEvent); }
	void AddFadeOutEndEvent(std::function<void()> endEvent) { fadeOutEndEvenets.push_back(endEvent); }
	void AddFadeInStartEvent(std::function<void()> startEvent) { fadeInStartEvenets.push_back(startEvent); }
	void AddFadeInEndEvent(std::function<void()> endEvent) { fadeInEndEvenets.push_back(endEvent); }
	void EndFadeOut();
	void StartFadeOut(float time = 1.f);
	void EndFadeIn();
	void StartFadeIn(float time = 1.f);
public:
	void Update(const float& deltaTime) override;
public:
	UIFadeInOutSpriteObject(const std::string& texId, const std::string& name = "");
	virtual ~UIFadeInOutSpriteObject() = default;
	UIFadeInOutSpriteObject& operator= (const UISpriteGameObject& other) = delete;
};
