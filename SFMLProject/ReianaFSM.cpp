#include "stdafx.h"
#include "ReianaFsm.h"

#include "ReianaIdleState.h"
#include "ReianaGroundAttackState.h"
#include "ReianaNomalAttackState.h"
#include "ReianaThreeSwordState.h"
#include "ReianaDropAttackState.h"
#include "ReianaRisingState.h"
#include "ReianaDimensionState.h"
#include "ReianaDeadState.h"
#include "ReianaDashState.h"

ReianaFsm::ReianaFsm(Reiana* owner)
	: owner(owner)
{
	CreateAllState();
}

ReianaFsm::~ReianaFsm()
{
}

void ReianaFsm::Awake()
{
}

void ReianaFsm::Start()
{
	for (auto state : stateMap)
	{
		state.second->Start();
	}
}

void ReianaFsm::CreateAllState()
{
	for (int i = 0; i < (int)ReianaStateType::End; ++i)
	{
		switch ((ReianaStateType)i)
		{
		case ReianaStateType::Idle:
			AddState(ReianaStateType::Idle);
			break;
		case ReianaStateType::NomalAttack:
			AddState(ReianaStateType::NomalAttack);
			break;
		case ReianaStateType::GroundAttack:
			AddState(ReianaStateType::GroundAttack);
			break;
		case ReianaStateType::ThreeSword:
			AddState(ReianaStateType::ThreeSword);
			break;
		case ReianaStateType::Rising:
			AddState(ReianaStateType::Rising);
			break;
		case ReianaStateType::DropAttack:
			AddState(ReianaStateType::DropAttack);
			break;
		case ReianaStateType::Dimension:
			AddState(ReianaStateType::Dimension);
			break;
		case ReianaStateType::Dash:
			AddState(ReianaStateType::Dash);
			break;
		case ReianaStateType::Dead:
			AddState(ReianaStateType::Dead);
			break;
		case ReianaStateType::End:
			break;
		default:
			break;
		}
	}
}

BaseState<ReianaStateType>* ReianaFsm::CreateState(ReianaStateType type)
{
	ReianaBaseState* state = nullptr;

	switch (type)
	{
	case ReianaStateType::Idle:
		state = new ReianaIdleState(this);
		break;
	case ReianaStateType::NomalAttack:
		state = new ReianaNomalAttackState(this);
		break;
	case ReianaStateType::GroundAttack:
		state = new ReianaGroundAttackState(this);
		break;
	case ReianaStateType::ThreeSword:
		state = new ReianaThreeSwordState(this);
		break;
	case ReianaStateType::Rising:
		state = new ReianaRisingState(this);
		break;
	case ReianaStateType::DropAttack:
		state = new ReianaDropAttackState(this);
		break;
	case ReianaStateType::Dimension:
		state = new ReianaDimensionState(this);
		break;
	case ReianaStateType::Dash:
		state = new ReianaDashState(this);
		break;
	case ReianaStateType::Dead:
		state = new ReianaDeadState(this);
		break;
	case ReianaStateType::End:
		break;
	default:
		break;
	}

	state->Awake();
	return state;
}

void ReianaFsm::Update(float deltaTime)
{
	stateMap[currentStateType]->Update(deltaTime);
}

void ReianaFsm::FixedUpdate(float fixedDeltaTime)
{
	stateMap[currentStateType]->FixedUpdate(fixedDeltaTime);
}

void ReianaFsm::LateUpdate(float deltaTime)
{
	stateMap[currentStateType]->LateUpdate(deltaTime);
}
