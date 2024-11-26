#include "stdafx.h"
#include "KoopaTroopaFSM.h"
#include "EnemyBaseState.h"

#include "KoopaTroopaIdleState.h"
#include "KoopaTroopaMoveState.h"
#include "KoopaTroopaGroggyState.h"
#include "KoopaTroopaScoutState.h"
#include "KoopaTroopaDeadState.h"

KoopaTroopaFSM::KoopaTroopaFSM(Enemy* owner)
	: EnemyFSM(owner)
{
	CreateAllState();
}

KoopaTroopaFSM::~KoopaTroopaFSM()
{
}

void KoopaTroopaFSM::CreateAllState()
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
		case EnemyStateType::Move:
			AddState(EnemyStateType::Move);
			break;
		case EnemyStateType::Groggy:
			AddState(EnemyStateType::Groggy);
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

void KoopaTroopaFSM::Awake()
{
}

void KoopaTroopaFSM::Start()
{
	for (auto state : stateMap)
	{
		state.second->Start();
	}
}

BaseState<EnemyStateType>* KoopaTroopaFSM::CreateState(EnemyStateType type)
{
	EnemyBaseState* state = nullptr;

	switch (type)
	{
	case EnemyStateType::Idle:
		state = new KoopaTroopaIdleState(this);
		break;
	case EnemyStateType::Scout:
		state = new KoopaTroopaScoutState(this);
		break;
	case EnemyStateType::Chase:
		break;
	case EnemyStateType::Hit:
		break;
	case EnemyStateType::Move:
		state = new KoopaTroopaMoveState(this);
		break; 
	case EnemyStateType::Groggy:
		state = new KoopaTroopaGroggyState(this);
			break;
	case EnemyStateType::Dead:
		state = new KoopaTroopaDeadState(this);
		break;
	case EnemyStateType::End:
		break;
	default:
		break;
	}
	if (state != nullptr)
		state->Awake();
	return state;
}
