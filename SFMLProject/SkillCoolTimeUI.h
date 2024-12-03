#pragma once

#include "UISpriteGameObject.h"

class Player;

class SkillCoolTimeUI : public UISpriteGameObject
{
protected:
	Player* player;

	sf::VertexArray mask;
	sf::Sprite drawnicon;
	sf::RenderTexture renderTexture;
	sf::RenderStates iconRenderState;
	sf::RenderStates maskRenderState;


	float currentTime;
	float coolTime;
	bool	isCoolTimeCheck;
public:
	void OnSkillCoolTime();
	void SetSkillCooltime(float currentTime, float coolTime);
	void SetPlayer(Player* player) { this->player = player; }
	void OnSkillCheck();
public:
	void Render(sf::RenderWindow& renderWindow) override;
	void Start() override;
public:
	SkillCoolTimeUI(const std::string& texId, const std::string& name = "");
	virtual ~SkillCoolTimeUI() = default;
	SkillCoolTimeUI& operator= (const SkillCoolTimeUI& other) = delete;
};

