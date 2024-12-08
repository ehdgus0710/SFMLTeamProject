#pragma once

#include "ReianaBaseState.h"

class ReianaDeadState : public ReianaBaseState
{
protected:
	bool onDead = false;

	void OnChangeDeadAnimation();
public:
	void Enter() override;
public:
	ReianaDeadState(ReianaFsm* fsm);
	~ReianaDeadState();
};