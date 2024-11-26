#pragma once
#include "UIGameObject.h"
class FadeOutUI : public UIGameObject
{
protected:
	sf::RectangleShape					fadeOutRect;
	std::vector<std::function<void()>>	fadeOutStartEvenets;
	std::vector<std::function<void()>>	fadeOutEndEvenets;

	sf::Color currentColor;

	float speed;
	float currentAlpha;
	bool isStartFadeOut;
	bool isFadeOutEnd;
	bool isFadeIn;

public:
	void AddFadeOutStartEvent(std::function<void()> startEvent) { fadeOutStartEvenets.push_back(startEvent); }
	void AddFadeOutEndEvent(std::function<void()> endEvent) { fadeOutEndEvenets.push_back(endEvent); }
	void EndFadeOut();
	void StartFadeOut();
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

