#pragma once

#include "B_ReianaBaseState.h"

class B_ReianaDeadState : public B_ReianaBaseState
{
protected:

public:
	void Enter() override;
public:
	B_ReianaDeadState(B_ReianaFsm* fsm);
	~B_ReianaDeadState();
};