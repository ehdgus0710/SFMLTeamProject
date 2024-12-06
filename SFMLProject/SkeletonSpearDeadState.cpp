#include "stdafx.h"
#include "SkeletonSpearDeadState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"

SkeletonSpearDeadState::SkeletonSpearDeadState(SkeletonSpearFSM* fsm)
	: SkeletonSpearBaseState(fsm, SkeletonSpearStateType::Dead)
{
}

void SkeletonSpearDeadState::Enter()
{
	SkeletonSpearBaseState::Enter();
}

void SkeletonSpearDeadState::Exit()
{
	SkeletonSpearBaseState::Exit();
}

void SkeletonSpearDeadState::Update(float deltaTime)
{
}

void SkeletonSpearDeadState::FixedUpdate(float fixedDeltaTime)
{
}