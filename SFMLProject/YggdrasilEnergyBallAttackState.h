#pragma once

#include "YggdrasilBaseState.h"

class YggdrasilEnergyBallBig;
class YggdrasilEnergyBallSmall;

class YggdrasilEnergyBallAttackState : public YggdrasilBaseState
{
protected:
	YggdrasilEnergyBallBig*		yggdrasilEnergyBallBig;
	YggdrasilEnergyBallSmall*	yggdrasilEnergyBallSmall[8];

	sf::Vector2f startPos;
	sf::Vector2f look;

	int attackCount;

	float speed;

	float currentFirstAttack;
	float firstAttackDelay;
	float shootTime;
	float shootDelay;

	bool isShoot;

private:
	void EnergyBallFire(sf::Vector2f pos, sf::Vector2f dir, float speed, float deltaTime);
	void SetEnergySmallBallPos();

	// ���� �Լ�
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

