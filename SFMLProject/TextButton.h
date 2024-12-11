#pragma once
#include "UIButtonObject.h"

class TextButton : public UIButtonObject
{
protected:
	sf::Color defalutColor;
	sf::Color changeColor;

protected:
	virtual void OnCollisionEnterChangeColor();
	virtual void OnCollisionStayChangeColor();
	virtual void OnCollisionEndChangeColor();

public:
	void SetChangeColor(const sf::Color& color);

public:
	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

public:
	TextButton(const std::string& textId, const std::string& name, unsigned int textSize, const sf::Color& textColor = sf::Color::White);
	TextButton(const std::string& textId, const std::string& name, unsigned int textSize, const sf::Color& textColor, const sf::Color& changeColor);
	virtual ~TextButton() = default;
	//UiTextureGameObject(const UiTextureGameObject& other) = delete;
	TextButton& operator= (const TextButton& other) = delete;
};

