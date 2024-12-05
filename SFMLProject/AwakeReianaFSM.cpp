#include "stdafx.h"
#include "AwakeReianaFsm.h"

#include "AwakeReianaIdleState.h"
#include "AwakeReianaGroundAttackState.h"
#include "AwakeReianaAwakeDimensionState.h"
#include "AwakeReianaDimensionState.h"
#include "AwakeReianaDropAttackState.h"
#include "AwakeReianaDeadState.h"
#include "AwakeReianaDiagonalDropState.h"

AwakeReianaFsm::AwakeReianaFsm(AwakeReiana* owner)
	: owner(owner)
{
	CreateAllState();
}

AwakeReianaFsm::~AwakeReianaFsm()
{
}

void AwakeReianaFsm::Awake()
{
}

void AwakeReianaFsm::Start()
{
	for (auto state : stateMap)
	{
		state.second->Start();
	}
}

void AwakeReianaFsm::CreateAllState()
{
	for (int i = 0; i < (int)AwakeReianaStateType::End; ++i)
	{
		switch ((AwakeReianaStateType)i)
		{
		case AwakeReianaStateType::Idle:
			AddState(AwakeReianaStateType::Idle);
			break;
		case AwakeReianaStateType::AwakeDimension:
			AddState(AwakeReianaStateType::AwakeDimension);
			break;
		case AwakeReianaStateType::Dimension:
			AddState(AwakeReianaStateType::Dimension);
			break;
		case AwakeReianaStateType::DropAttack:
			AddState(AwakeReianaStateType::DropAttack);
			break;
		case AwakeReianaStateType::GroundAttack:
			AddState(AwakeReianaStateType::GroundAttack);
			break;
		case AwakeReianaStateType::DiagonalDrop:
			AddState(AwakeReianaStateType::DiagonalDrop);
			break;
		case AwakeReianaStateType::Dead:
			AddState(AwakeReianaStateType::Dead);
			break;
		case AwakeReianaStateType::End:
			break;
		default:
			break;
		}
	}
}

BaseState<AwakeReianaStateType>* AwakeReianaFsm::CreateState(AwakeReianaStateType type)
{
	AwakeReianaBaseState* state = nullptr;

	switch (type)
	{
	case AwakeReianaStateType::Idle:
		state = new AwakeReianaIdleState(this);
		break;
	case AwakeReianaStateType::AwakeDimension:
		state = new AwakeReianaAwakeDimensionState(this);
		break;
	case AwakeReianaStateType::Dimension:
		state = new AwakeReianaDimensionState(this);
		break;
	case AwakeReianaStateType::DropAttack:
		state = new AwakeReianaDropAttackState(this);
		break;
	case AwakeReianaStateType::GroundAttack:
		state = new AwakeReianaGroundAttackState(this);
		break;
	case AwakeReianaStateType::DiagonalDrop:
		state = new AwakeReianaDiagonalDropState(this);
		break;
	case AwakeReianaStateType::Dead:
		state = new AwakeReianaDeadState(this);
		break;
	case AwakeReianaStateType::End:
		break;
	default:
		break;
	}

	state->Awake();
	return state;
}

void AwakeReianaFsm::Update(float deltaTime)
{
	stateMap[currentStateType]->Update(deltaTime);
}

void AwakeReianaFsm::FixedUpdate(float fixedDeltaTime)
{
	stateMap[currentStateType]->FixedUpdate(fixedDeltaTime);
}

void AwakeReianaFsm::LateUpdate(float deltaTime)
{
	stateMap[currentStateType]->LateUpdate(deltaTime);
}
