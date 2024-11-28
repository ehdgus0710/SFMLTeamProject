#include "stdafx.h"
#include "ReianaFsm.h"

#include "ReianaIdleState.h"
#include "ReianaGroundAttackState.h"
#include "ReianaNomalAttackState.h"
#include "ReianaVomitAttackState.h"
#include "ReianaDropAttackState.h"
#include "ReianaDropGlassState.h"
#include "ReianaDropPoisonState.h"
#include "ReianaPongState.h"
#include "ReianaDeadState.h"

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
		case ReianaStateType::VomitAttack:
			AddState(ReianaStateType::VomitAttack);
			break;
		case ReianaStateType::Pong:
			AddState(ReianaStateType::Pong);
			break;
		case ReianaStateType::DropGlass:
			AddState(ReianaStateType::DropGlass);
			break;
		case ReianaStateType::DropAttack:
			AddState(ReianaStateType::DropAttack);
			break;
		case ReianaStateType::DropPoison:
			AddState(ReianaStateType::DropPoison);
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
	case ReianaStateType::VomitAttack:
		state = new ReianaVomitAttackState(this);
		break;
	case ReianaStateType::Pong:
		state = new ReianaPongState(this);
		break;
	case ReianaStateType::DropGlass:
		state = new ReianaDropGlassState(this);
		break;
	case ReianaStateType::DropAttack:
		state = new ReianaDropAttackState(this);
		break;
	case ReianaStateType::DropPoison:
		state = new ReianaDropPoisonState(this);
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
