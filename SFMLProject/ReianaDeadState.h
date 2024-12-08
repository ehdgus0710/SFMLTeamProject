#pragma once

#include "ReianaBaseState.h"

class ReianaDeadState : public ReianaBaseState
{
protected:
	bool onDead = false;
public:
	void Enter() override;
public:
	ReianaDeadState(ReianaFsm* fsm);
	~ReianaDeadState();
};