#pragma once
#include "UITextGameObject.h"
class EndingCreditTimeLine : public UITextGameObject
{
private:
	bool isRender;
	sf::Vector2f colliderPosition;
	float		currentTime;
	float		endTime;
public:
	void OnStartCreadit();

	void Update(const float& deltaTime) override;

	void Start() override;
	void Render(sf::RenderWindow& window) override;
public:
	EndingCreditTimeLine(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor = sf::Color::White);
	virtual ~EndingCreditTimeLine() = default;
};

