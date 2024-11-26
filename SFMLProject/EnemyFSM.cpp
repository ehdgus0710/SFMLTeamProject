#include "stdafx.h"
#include "EnemyFSM.h"
#include "EnemyBaseState.h"


EnemyFSM::EnemyFSM(Enemy* owner)
	: owner(owner)
{
}

EnemyFSM::~EnemyFSM()
{
}

void EnemyFSM::CreateAllState()
{
}

BaseState<EnemyStateType>* EnemyFSM::CreateState(EnemyStateType type)
{
	EnemyBaseState* state = nullptr;

	switch (type)
	{
	case EnemyStateType::Idle:
		break;
	case EnemyStateType::Scout:
		break;
	case EnemyStateType::Chase:
		break;
	case EnemyStateType::Hit:
		break;
	case EnemyStateType::Dead:
		break;
	case EnemyStateType::End:
		break;
	default:
		break;
	}

	state->Awake();
	return state;
}

void EnemyFSM::Awake()
{
}

void EnemyFSM::Start()
{
	for (auto state : stateMap)
	{
		state.second->Start();
	}
}

void EnemyFSM::Update(float deltaTime)
{
	stateMap[currentStateType]->Update(deltaTime);
}

void EnemyFSM::FixedUpdate(float fixedDeltaTime)
{
	stateMap[currentStateType]->FixedUpdate(fixedDeltaTime);
}

void EnemyFSM::LateUpdate(float deltaTime)
{
	stateMap[currentStateType]->LateUpdate(deltaTime);
}