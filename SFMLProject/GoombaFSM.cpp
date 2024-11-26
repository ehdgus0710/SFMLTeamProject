#include "stdafx.h"
#include "GoombaFSM.h"

#include "EnemyBaseState.h"

#include "GoombaIdleState.h"
#include "GoombaScoutState.h"
#include "GoombaDeadState.h"

GoombaFSM::GoombaFSM(Enemy* owner)
	: EnemyFSM(owner)
{
	CreateAllState();
}

GoombaFSM::~GoombaFSM()
{
}

void GoombaFSM::CreateAllState()
{
	for (int i = 0; i < (int)EnemyStateType::End; ++i)
	{
		switch ((EnemyStateType)i)
		{
		case EnemyStateType::Idle:
			AddState(EnemyStateType::Idle);
			break;
		case EnemyStateType::Scout:
			AddState(EnemyStateType::Scout);
			break;
		case EnemyStateType::Chase:
			break;
		case EnemyStateType::Hit:
			break;
		case EnemyStateType::Dead:
			AddState(EnemyStateType::Dead);
			break;
		case EnemyStateType::End:
			break;
		default:
			break;
		}

	}
}

void GoombaFSM::Awake()
{
}

void GoombaFSM::Start()
{
	for (auto state : stateMap)
	{
		state.second->Start();
	}
}

BaseState<EnemyStateType>* GoombaFSM::CreateState(EnemyStateType type)
{
	EnemyBaseState* state = nullptr;

	switch (type)
	{
	case EnemyStateType::Idle:
		state = new GoombaIdleState(this);
		break;
	case EnemyStateType::Scout:
		state = new GoombaScoutState(this);
		break;
	case EnemyStateType::Chase:
		break;
	case EnemyStateType::Hit:
		break;
	case EnemyStateType::Dead:
		state = new GoombaDeadState(this);
		break;
	case EnemyStateType::End:
		break;
	default:
		break;
	}

	if(state != nullptr)
		state->Awake();
	return state;
}
