#pragma once
#include "UIGameObject.h"
class FadeOutUI : public UIGameObject
{
protected:
	sf::RectangleShape					fadeOutRect;
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
	void SetPosition(const sf::Vector2f& pos) override; 
	void SetScale(const sf::Vector2f& scale);
	void Render(sf::RenderWindow& renderWindow) override;
	void Start() override;

	void Update(const float& deltaTime) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const { return fadeOutRect.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() const { return fadeOutRect.getGlobalBounds(); }
public:
	FadeOutUI(const std::string& name);
	virtual ~FadeOutUI() = default;
	FadeOutUI& operator= (const FadeOutUI& other) = delete;
};

