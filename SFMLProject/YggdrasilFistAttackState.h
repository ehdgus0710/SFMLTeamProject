#pragma once
#include "YggdrasilBaseState.h"

class Player;
class yggdrasil;

class YggdrasilFistAttackState : public YggdrasilBaseState
{
protected:

	sf::Vector2f	startPos;
	sf::Vector2f	endPos;

	sf::Vector2f	firstPos;
	
	int			attackCount;
	int			currentAttackCount;

	float		currentAttackDelay;
	float		attackDelay;

	float		currentAttackTime;
	float		attackTime;
	float		recoveryTime;
	float		currentRecoveryTime;
	
	bool		isWait;
	bool		isAttack;
	bool		isRecovery;
	bool		onAttack;

private:
	void StartAttack(float deltaTime);
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
	YggdrasilFistAttackState(YggdrasilFSM* fsm);
	~YggdrasilFistAttackState() = default;
};

