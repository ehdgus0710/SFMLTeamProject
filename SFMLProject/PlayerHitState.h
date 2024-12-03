#pragma once
#include "PlayerBaseState.h"

class Rigidbody;
class PlayerHitState : public PlayerBaseState
{
private:
	Rigidbody*	rigidbody;
	DamegeInfo	currentDamageInfo;
	float		currentTime;

public:
	void SetDamageInfo(const DamegeInfo& damage);

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
public:
	PlayerHitState(PlayerFSM* fsm);
	~PlayerHitState();
};

