#pragma once

#include "UISpriteGameObject.h"

class Player;
class UITextGameObject;
class HpBarUI;

class PlayerUIHub : public UISpriteGameObject
{
protected:
	Player*					player;
	UISpriteGameObject*		playerSmbolUI;
	UITextGameObject*		hpText;
	UITextGameObject*		maxHPText;
	HpBarUI*				playerHpBar;

public:
	void ChangeHP(float currentHp, float maxHp);
public:
	void Awake() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void Render(sf::RenderWindow& renderWindow) override;
	void Start() override;

	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	PlayerUIHub(const std::string& texId, const std::string& name = "PlayerUI");
	virtual ~PlayerUIHub() = default;
	PlayerUIHub& operator= (const PlayerUIHub& other) = delete;
};

