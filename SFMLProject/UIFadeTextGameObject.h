#pragma once
#include "UITextGameObject.h"
class UIFadeTextGameObject : public UITextGameObject
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
	UIFadeTextGameObject(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor = sf::Color::White);
	virtual ~UIFadeTextGameObject() = default;
	//UiTextureGameObject(const UiTextureGameObject& other) = delete;
	UIFadeTextGameObject& operator= (const UIFadeTextGameObject& other) = delete;
};

