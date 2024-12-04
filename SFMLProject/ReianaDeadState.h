#pragma once

#include "ReianaBaseState.h"

class ReianaDeadState : public ReianaBaseState
{
protected:

public:
	void Enter() override;
public:
	ReianaDeadState(ReianaFsm* fsm);
	~ReianaDeadState();
};