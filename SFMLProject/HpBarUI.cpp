#include "stdafx.h"
#include "HpBarUI.h"

HpBarUI::HpBarUI(const std::string& texId,const std::string& name)
	: UIRectangleShapeObject(texId, name)
	, ownerStatus(nullptr)
{
}

void HpBarUI::Start()
{
	UIRectangleShapeObject::Start();
}

void HpBarUI::Update(const float& deltaTime)
{
}

void HpBarUI::SetMaxHpBarSize(const sf::Vector2f& maxSize)
{
	this->maxSize = maxSize;
	currentSize = maxSize;
	SetScale(currentSize);
}

void HpBarUI::ChangeHP(float currentHP, float maxHp)
{
	float hp =  currentHP / maxHp;
	currentSize.x = maxSize.x * hp;
	SetScale(currentSize);
}

void HpBarUI::ChangeSprite(std::string changeTextureID)
{
	textureId = changeTextureID;
	rectangleShape.setTexture(&ResourcesManager<sf::Texture>::GetInstance().Get(textureId), true);

	SetOrigin(originPreset);
}
