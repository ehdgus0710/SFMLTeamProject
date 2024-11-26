#pragma once

#include "UITextGameObject.h"
class InGameScoreUI : public UITextGameObject
{
private:
	sf::Color currentColor;
	float currentLifeTime;
	float lifeTime;
	float speed;

public:
	void Start() override;
	void Update(const float& deltaTime) override;
public:
	InGameScoreUI(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor = sf::Color::White);
	virtual ~InGameScoreUI() = default;
	InGameScoreUI& operator= (const InGameScoreUI& other) = delete;
};

