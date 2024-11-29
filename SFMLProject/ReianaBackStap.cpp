#include "stdafx.h"
#include "ReianaBackStap.h"
#include "Player.h"	
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"

ReianaBackStap::ReianaBackStap(ReianaFsm* fsm)
	: ReianaBaseState(fsm, ReianaStateType::GroundAttack)

{
}

ReianaBackStap::~ReianaBackStap()
{
}

void ReianaBackStap::BackStap(float deltaTime)
{
}

void ReianaBackStap::Awake()
{
	ReianaBaseState::Awake();
}

void ReianaBackStap::Start()
{
	ReianaBaseState::Start();
}

void ReianaBackStap::Enter()
{
	ReianaBaseState::Enter();
	animator->ChangeAnimation("meteorGroundReady", false);

}

void ReianaBackStap::Exit()
{
	ReianaBaseState::Exit();
}

void ReianaBackStap::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);

}

void ReianaBackStap::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);
}

void ReianaBackStap::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);
}
