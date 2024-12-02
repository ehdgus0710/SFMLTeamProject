#pragma once

#include "YggdrasilBaseState.h"


class YggdrasilEnergyBallAttackState : public YggdrasilBaseState
{
protected:

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

