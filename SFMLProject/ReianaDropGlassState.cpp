#include "stdafx.h"
#include "ReianaDropGlassState.h"

ReianaDropGlassState::ReianaDropGlassState(ReianaFsm* fsm)
	:ReianaBaseState(fsm, ReianaStateType::DropGlass)
{
}

ReianaDropGlassState::~ReianaDropGlassState()
{
}

void ReianaDropGlassState::Awake()
{
}

void ReianaDropGlassState::Start()
{
}

void ReianaDropGlassState::Enter()
{
	ReianaBaseState::Enter();
}

void ReianaDropGlassState::Exit()
{
	ReianaBaseState::Exit();

}

void ReianaDropGlassState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);

}

void ReianaDropGlassState::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void ReianaDropGlassState::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);

}
