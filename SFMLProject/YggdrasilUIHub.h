#pragma once

#include "UISpriteGameObject.h"

class HpBarUI;
class UITextGameObject;
class Yggdrasil;

class YggdrasilUIHub : public UISpriteGameObject
{
private:
	UISpriteGameObject* topBackSprite;
	UISpriteGameObject* bottomBackSprite;
	UISpriteGameObject* frontHpBarSprite;
	HpBarUI*			hpBar;
	UITextGameObject*	nameText;
	UITextGameObject*	tribeText;
	Yggdrasil*			yggdrasil;

public:
	void ChangeHP(float currentHp, float maxHp);
	void ChangePhase();
public:
	void SetPosition(const sf::Vector2f& pos) override;
	void Start() override;

	void Update(const float& deltaTime) override;
public:
	YggdrasilUIHub(const std::string& texId, const std::string& name = "YggdrasilUIHub");
	virtual ~YggdrasilUIHub() = default;
	YggdrasilUIHub& operator= (const YggdrasilUIHub& other) = delete;
};