#pragma once

#include "AwakeReianaBaseState.h"

class AwakeReianaDeadState : public AwakeReianaBaseState
{
protected:

public:
	void Enter() override;
public:
	AwakeReianaDeadState(AwakeReianaFsm* fsm);
	~AwakeReianaDeadState();
};