#include "stdafx.h"
#include "ReianaKnifeState.h"
#include "Player.h"
#include "Knife.h"

ReianaKnifeState::ReianaKnifeState(ReianaFsm* fsm)
	:ReianaBaseState(fsm, ReianaStateType::Knife)
{
}

ReianaKnifeState::~ReianaKnifeState()
{
}

void ReianaKnifeState::Awake()
{
}

void ReianaKnifeState::Start()
{
}

void ReianaKnifeState::Enter()
{
	ReianaBaseState::Enter();
}

void ReianaKnifeState::Exit()
{
	ReianaBaseState::Exit();

}

void ReianaKnifeState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);
}

void ReianaKnifeState::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void ReianaKnifeState::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);

}
