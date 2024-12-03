#pragma once

#include "UISpriteGameObject.h"

class Player;
class UITextGameObject;
class HpBarUI;
class SkillCoolTimeUI;

class PlayerUIHub : public UISpriteGameObject
{
protected:
	Player*					player;
	Player*					player2;
	UISpriteGameObject*		playerSimbolUI;
	UISpriteGameObject*		playerSkill2Frame;
	SkillCoolTimeUI*		playerSkill1;
	SkillCoolTimeUI*		playerSkill2;
	UISpriteGameObject*		subSkullFrame;
	UISpriteGameObject*		subSkullSpriteUI;

	UITextGameObject*		hpText;
	UITextGameObject*		maxHPText;
	UITextGameObject*		hpSlashText;
	HpBarUI*				playerHpBar;


public:
	void ChangeHP(float currentHp, float maxHp);
	void ChangeSkull(Player* player);
	void ChangeSkillSprite(SkullType type);
	void AddSkull(Player* player);

	void OnSkill1CoolTime();
	void OnSkill2CoolTime();
public:
	void Awake() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void Render(sf::RenderWindow& renderWindow) override;
	void Start() override;

	void Update(const float& deltaTime) override;
public:
	PlayerUIHub(const std::string& texId, const std::string& name = "PlayerUI");
	virtual ~PlayerUIHub() = default;
	PlayerUIHub& operator= (const PlayerUIHub& other) = delete;
};

