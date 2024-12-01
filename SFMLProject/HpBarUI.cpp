#include "stdafx.h"
#include "HpBarUI.h"

HpBarUI::HpBarUI(const std::string& texId, const sf::Color& color,const std::string& name)
	: UIRectangleShapeObject(texId, name)
	, hpColor(color)
{
}

void HpBarUI::Start()
{
	rectangleShape.setFillColor(hpColor);

	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
	SetOrigin(originPreset);
}