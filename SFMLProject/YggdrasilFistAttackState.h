#pragma once
#include "YggdrasilBaseState.h"

class Player;
class yggdrasil;

class YggdrasilFistAttackState : public YggdrasilBaseState
{
protected:

	sf::Vector2f	startPos;
	sf::Vector2f	endPos;
	sf::Vector2f	firstLeftPos;
	sf::Vector2f	firstRightPos;

	int			attackCount;
	int			currentAttackCount;

	float		currentAttackDelay;
	float		attackDelay;
	float		switchFistDelay;
	float		readyDelay;

	float		readyTime;
	float		currentAttackTime;
	float		attackTime;
	float		recoveryTime;
	float		currentRecoveryTime;
	float		switchFistTime;
	
	bool		isWait;
	bool		isAttack;
	bool		isRecovery;
	bool		onAttack;
	bool		switchFist;
	bool		readyFist;

private:
	void ReadyFist(float deltaTime);
	void StartAttack(float deltaTime);
	void EndAttackWait(float deltaTime);
	void EndFistPos(float deltaTime);
	void Recovery(float deltaTime);

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	YggdrasilFistAttackState(YggdrasilFSM* fsm);
	~YggdrasilFistAttackState() = default;
};

