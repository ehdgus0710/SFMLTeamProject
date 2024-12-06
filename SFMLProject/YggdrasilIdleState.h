#pragma once

#include "YggdrasilBaseState.h"

class YggdrasilIdleState : public YggdrasilBaseState
{
protected:
	sf::Vector2f bStartPos;
	sf::Vector2f bEndPos;
	sf::Vector2f hStartPos;
	sf::Vector2f hEndPos;
	sf::Vector2f mStartPos;
	sf::Vector2f mEndPos;

	int		choiceAttack;

	float attackTime;
	float attackDelay;

	float bodyMoveTime;
	float bodyMoveDelay;
	float headMoveTime;
	float headMoveDelay;
	float mouthMoveTime;
	float mouthMoveDelay;

	bool changeOn;
	bool bPos;
	bool hPos;
	bool mPos;
protected:
	void Moves(float dt);
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	YggdrasilIdleState(YggdrasilFSM* fsm);
	~YggdrasilIdleState() = default;
};

