#pragma once

#include "YggdrasilBaseState.h"

class HitBoxObject;

class YggdrasilSpecialAttackState : public YggdrasilBaseState
{
	HitBoxObject* attackBox;

	sf::Vector2f	lFirstPos;
	sf::Vector2f	rFirstPos;

	sf::Vector2f	lStartPos;
	sf::Vector2f	lEndPos;
	sf::Vector2f	rStartPos;
	sf::Vector2f	rEndPos;

	int			attackCount;
	int			currentAttackCount;
	int			whatFist;

	float		currentAttackDelay;
	float		attackDelay;
	float		readyFistDelay;

	float		currentAttackTime;
	float		attackTime;
	float		recoveryTime;
	float		currentRecoveryTime;
	float		readyFistTime;

	bool		readyAttack;
	bool		isWait;
	bool		isAttack;
	bool		isRecovery;
	bool		onAttack;
	bool		switchFist;

	bool		isAttackWait;
	bool		hitBoxOn;
	bool		changeOn;

private:
	void ReadyAttack(float deltaTime);
	void StartLeftAttack(float deltaTime);
	void StartRightAttack(float deltaTime);
	void EndAttackWait(float deltaTime);
	void Recovery(float deltaTime);

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	YggdrasilSpecialAttackState(YggdrasilFSM* fsm);
	~YggdrasilSpecialAttackState() = default;
};