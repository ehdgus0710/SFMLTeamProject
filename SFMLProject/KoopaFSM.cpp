#include "stdafx.h"
#include "KoopaFSM.h"

#include "EnemyBaseState.h"
#include "KoopaAttackState.h"
#include "KoopaIdleState.h"
#include "KoopaDeadState.h"


KoopaFSM::KoopaFSM(Enemy* owner)
	: EnemyFSM(owner)

{
	CreateAllState();
}

KoopaFSM::~KoopaFSM()
{
}

void KoopaFSM::CreateAllState()
{
	for (int i = 0; i < (int)EnemyStateType::End; ++i)
	{
		switch ((EnemyStateType)i)
		{
		case EnemyStateType::Idle:
			AddState(EnemyStateType::Idle);
			break;
		case EnemyStateType::Scout:
			break;
		case EnemyStateType::Chase:
			break;
		case EnemyStateType::Hit:
			break;
		case EnemyStateType::Attack:
			AddState(EnemyStateType::Attack);
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

void KoopaFSM::Awake()
{
}

void KoopaFSM::Start()
{
	for (auto state : stateMap)
	{
		state.second->Start();
	}
}

BaseState<EnemyStateType>* KoopaFSM::CreateState(EnemyStateType type)
{
	EnemyBaseState* state = nullptr;

	switch (type)
	{
	case EnemyStateType::Idle:
		state = new KoopaIdleState(this);
		break;
	case EnemyStateType::Scout:
		break;
	case EnemyStateType::Chase:
		break;
	case EnemyStateType::Hit:
		break;
	case EnemyStateType::Attack:
		state = new KoopaAttackState(this);
		break;
	case EnemyStateType::Dead:
		state = new KoopaDeadState(this);
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