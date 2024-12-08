#pragma once

#include "YggdrasilBaseState.h"

class YggdrasilEnergyBallBig;
class YggdrasilEnergyBallSmall;

class YggdrasilEnergyBallAttackState : public YggdrasilBaseState
{
protected:
	YggdrasilEnergyBallBig*		yggdrasilEnergyBallBig[2];
	YggdrasilEnergyBallSmall*	yggdrasilEnergyBallSmall[8];
	sf::Vector2f startPos;
	sf::Vector2f look;

	int attackCount;
	int maxAttackCount;

	float speed;

	float currentFirstAttack;
	float firstAttackDelay;
	float shootTime;
	float shootDelay;

	bool isShoot;
	bool changeOn;

private:
	void EnergyBallFire(sf::Vector2f pos, sf::Vector2f dir, float speed, float deltaTime);
	void SetEnergySmallBallPos();

	// 예시 함수
	void CreateEffect();
public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;

public:
	YggdrasilEnergyBallAttackState(YggdrasilFSM* fsm);
	~YggdrasilEnergyBallAttackState() = default;
};

