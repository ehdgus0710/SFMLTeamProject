#include "stdafx.h"
#include "YggdrasilEnergyBallAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"

void YggdrasilEnergyBallAttackState::Awake()
{
	YggdrasilBaseState::Awake();
}

void YggdrasilEnergyBallAttackState::Start()
{
	YggdrasilBaseState::Start();
}

void YggdrasilEnergyBallAttackState::Enter()
{
	YggdrasilBaseState::Enter();

}

void YggdrasilEnergyBallAttackState::Exit()
{
	YggdrasilBaseState::Exit();
}

void YggdrasilEnergyBallAttackState::Update(float deltaTime)
{
}

void YggdrasilEnergyBallAttackState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilEnergyBallAttackState::YggdrasilEnergyBallAttackState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::EnergyBallAttack)
{
}
