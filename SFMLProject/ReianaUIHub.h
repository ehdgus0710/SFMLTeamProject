#pragma once

#include "UISpriteGameObject.h"

class HpBarUI;
class UITextGameObject;
class Yggdrasil;

class ReianaUIHub : public UISpriteGameObject
{
private:
	UISpriteGameObject* topBackSprite;
	UISpriteGameObject* bottomBackSprite;
	UISpriteGameObject* hpBarSprite;
	HpBarUI* reianaABar;
	HpBarUI* reianaBBar;
	UITextGameObject* nameText;
	UITextGameObject* tribeText;
	Yggdrasil* yggdrasil;

public:
	void ChangeHP(float currentHp, float maxHp);
	void ChangePhase();
public:
	void SetPosition(const sf::Vector2f& pos) override;
	void Start() override;

public:
	ReianaUIHub(const std::string& texId, const std::string& name = "ReianaUIHub");
	virtual ~ReianaUIHub() = default;
	ReianaUIHub& operator= (const ReianaUIHub& other) = delete;
};
