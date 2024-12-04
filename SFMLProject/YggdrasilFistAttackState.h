#pragma once
#include "YggdrasilBaseState.h"

class Player;
class yggdrasil;
class HitBoxObject;
class Animation;

class YggdrasilFistAttackState : public YggdrasilBaseState
{
protected:
	std::vector<std::function<void()>> events;

	Animation* animation;
	HitBoxObject*	attackBox;
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
	float		waitTime;
	
	bool		isWait;
	bool		isAttack;
	bool		isRecovery;
	bool		onAttack;
	bool		switchFist;
	bool		readyFist;

	bool		hitBoxOn;
	bool		changeOn;

private:
	void ReadyFist(float deltaTime);
	void StartAttack(float deltaTime);
	void EndAttackWait(float deltaTime);
	void EndFistPos(float deltaTime);
	void Recovery(float deltaTime);
	void CreateLeftEffect();
	void CreateRightEffect();

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

