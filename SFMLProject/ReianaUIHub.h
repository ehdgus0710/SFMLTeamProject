#pragma once

#include "UISpriteGameObject.h"

class HpBarUI;
class UITextGameObject;
class Yggdrasil;
class Reiana;
class B_Reiana;
class AwakeReiana;

class ReianaUIHub : public UISpriteGameObject
{
private:
	UISpriteGameObject* topBackSprite;
	UISpriteGameObject* bottomBackSprite;
	UISpriteGameObject* frontHpBarSprite;
	HpBarUI*			reianaAHPBar;
	HpBarUI*			reianaBHPBar;
	HpBarUI*			awakenReianaHPBar;
	UITextGameObject*	nameText;
	UITextGameObject*	tribeText;

	Reiana*				reianaA;
	B_Reiana*			reianaB;
	AwakeReiana*		awakeReiana;

public:

	void ChangeReianaAHP(float currentHp, float maxHp);
	void ChangeReianaBHP(float currentHp, float maxHp);
	void ChangeAwakenReianaHP(float currentHp, float maxHp);
	void ChangePhase();
	void SetAwakeReiana(AwakeReiana* reiana) { awakeReiana = reiana; }
public:
	// void SetPosition(const sf::Vector2f& pos) override;
	void Start() override;
public:
	ReianaUIHub(const std::string& texId, const std::string& name = "ReianaUIHub");
	virtual ~ReianaUIHub() = default;
	ReianaUIHub& operator= (const ReianaUIHub& other) = delete;
};
