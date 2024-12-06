#pragma once
#include "SkeletonSpearBaseState.h"
class Rigidbody;

class SkeletonSpearHitState : public SkeletonSpearBaseState
{
private:
	Rigidbody* rigidbody;
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
	SkeletonSpearHitState(SkeletonSpearFSM* fsm);
	~SkeletonSpearHitState();
};