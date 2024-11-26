#pragma once
#include "UIButtonObject.h"

class TextButton : public UIButtonObject
{
public:
	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

public:
	TextButton(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor = sf::Color::White);
	virtual ~TextButton() = default;
	//UiTextureGameObject(const UiTextureGameObject& other) = delete;
	TextButton& operator= (const TextButton& other) = delete;
};

