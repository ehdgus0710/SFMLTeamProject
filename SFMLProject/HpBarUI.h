#pragma once

#include "UIRectangleShapeObject.h"

class HpBarUI : public UIRectangleShapeObject
{
protected:
	sf::Color				hpColor;

public:
	void Start() override;
public:
	HpBarUI(const std::string& textureId, const sf::Color& color, const std::string& name = "");
	virtual ~HpBarUI() = default;
	HpBarUI& operator= (const HpBarUI& other) = delete;
};

