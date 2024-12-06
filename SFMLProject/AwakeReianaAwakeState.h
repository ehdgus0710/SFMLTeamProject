#pragma once

#include "AwakeReianaBaseState.h"

class AwakeReianaAwakeState : public AwakeReianaBaseState
{
protected:
	float awakeTiem;
	float awakeCurrentTime;
public:
	void Enter() override;
	void Update(float deltaTime) override;
public:
	AwakeReianaAwakeState(AwakeReianaFsm* fsm);
	~AwakeReianaAwakeState();
};