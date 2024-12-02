#pragma once

#include "UIRectangleShapeObject.h"

class HpBarUI : public UIRectangleShapeObject
{
protected:
	sf::Vector2f maxSize;
	sf::Vector2f currentSize;

	const DefaultStatus* ownerStatus;
public:
	void Start() override;
	void Update(const float& deltaTime) override;

	void SetMaxHpBarSize(const sf::Vector2f& maxSize);
	void SetOwnerStatus(const DefaultStatus& status) { ownerStatus = &status; }
	void ChangeHP(float currentHP, float maxHp);
public:
	HpBarUI(const std::string& textureId, const std::string& name = "");
	virtual ~HpBarUI() = default;
	HpBarUI& operator= (const HpBarUI& other) = delete;
};

