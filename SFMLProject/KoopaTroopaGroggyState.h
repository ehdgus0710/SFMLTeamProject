#pragma once
#include "EnemyBaseState.h"
class KoopaTroopaGroggyState : public EnemyBaseState
{
private:
	float groggyTime;
	float currentGroggyTime;

	bool isPlayAnimation;

public:
	void Awake() override;
	void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
	void LateUpdate(float deltaTime) override;
public:
	KoopaTroopaGroggyState(EnemyFSM* fsm);
	~KoopaTroopaGroggyState();
};

