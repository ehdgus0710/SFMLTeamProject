#pragma once

#include "AwakeReianaBaseState.h"

class AwakeReianaDeadState : public AwakeReianaBaseState
{
protected:

public:
	void Enter() override;
	void OnDead();
public:
	AwakeReianaDeadState(AwakeReianaFsm* fsm);
	~AwakeReianaDeadState();
};