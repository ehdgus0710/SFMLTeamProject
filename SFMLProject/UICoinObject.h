#pragma once
#include "UIAnimationObject.h"
class UICoinObject : public UIAnimationObject
{
private:


	sf::Sprite	subSprite;
public:
	void Start() override;

	void Render(sf::RenderWindow& renderWindow) override;
public:
	UICoinObject(const std::string& name);
	virtual ~UICoinObject() = default;
	UICoinObject& operator= (const UICoinObject& other) = delete;
};

