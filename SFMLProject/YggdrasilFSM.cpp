#include "stdafx.h"
#include "YggdrasilFSM.h"

#include "YggdrasilIdleState.h"
#include "YggdrasilFistAttackState.h"
#include "YggdrasilSweepAttackState.h"
#include "YggdrasilEnergyBallAttackState.h"
#include "YggdrasilSpecialAttackState.h"
#include "YggdrasilDeadState.h"

YggdrasilFSM::YggdrasilFSM(Yggdrasil* owner)
	: owner(owner)
{
	CreateAllState();
}

YggdrasilFSM::~YggdrasilFSM()
{
}

void YggdrasilFSM::Awake()
{
}

void YggdrasilFSM::Start()
{
	for (auto state : stateMap)
	{
		state.second->Start();
	}
}

void YggdrasilFSM::CreateAllState()
{
	for (int i = 0; i < (int)YggdrasilStateType::End; ++i)
	{
		switch ((YggdrasilStateType)i)
		{
		case YggdrasilStateType::Idle:
			AddState(YggdrasilStateType::Idle);
			break;
		case YggdrasilStateType::FistAttack:
			AddState(YggdrasilStateType::FistAttack);
			break;
		case YggdrasilStateType::SweepAttack:
			AddState(YggdrasilStateType::SweepAttack);
			break;
		case YggdrasilStateType::EnergyBallAttack:
			AddState(YggdrasilStateType::EnergyBallAttack);
			break;
		case YggdrasilStateType::YggdrasilSpecialAttack:
			AddState(YggdrasilStateType::YggdrasilSpecialAttack);
			break;
		case YggdrasilStateType::Dead:
			AddState(YggdrasilStateType::Dead);
			break;
		case YggdrasilStateType::End:
			break;
		default:
			break;
		}
	}
}

BaseState<YggdrasilStateType>* YggdrasilFSM::CreateState(YggdrasilStateType type)
{
	YggdrasilBaseState* state = nullptr;

	switch (type)
	{
	case YggdrasilStateType::Idle:
		state = new YggdrasilIdleState(this);
		break;
	case YggdrasilStateType::FistAttack:
		state = new YggdrasilFistAttackState(this);
		break;
	case YggdrasilStateType::SweepAttack:
		state = new YggdrasilSweepAttackState(this);
		break;
	case YggdrasilStateType::EnergyBallAttack:
		state = new YggdrasilEnergyBallAttackState(this);
		break;
	case YggdrasilStateType::YggdrasilSpecialAttack:
		state = new YggdrasilSpecialAttackState(this);
		break;
	case YggdrasilStateType::Dead:
		state = new YggdrasilDeadState(this);
		break;
	case YggdrasilStateType::End:
		break;
	default:
		break;
	}

	state->Awake();
	return state;
}

void YggdrasilFSM::Update(float deltaTime)
{
	stateMap[currentStateType]->Update(deltaTime);
}

void YggdrasilFSM::FixedUpdate(float fixedDeltaTime)
{
	stateMap[currentStateType]->FixedUpdate(fixedDeltaTime);
}

void YggdrasilFSM::LateUpdate(float deltaTime)
{
	stateMap[currentStateType]->LateUpdate(deltaTime);
}
