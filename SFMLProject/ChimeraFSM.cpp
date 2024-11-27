#include "stdafx.h"
#include "ChimeraFSM.h"

#include "ChimeraIdleState.h"
#include "ChimeraGroundAttackState.h"
#include "ChimeraNomalAttackState.h"
#include "ChimeraVomitAttackState.h"
#include "ChimeraDropBallState.h"
#include "ChimeraDropGlassState.h"
#include "ChimeraDropPoisonState.h"
#include "ChimeraPongState.h"
#include "ChimeraDeadState.h"

ChimeraFSM::ChimeraFSM(Chimera* owner)
	: owner(owner)
{
	CreateAllState();
}

ChimeraFSM::~ChimeraFSM()
{
}

void ChimeraFSM::Awake()
{
}

void ChimeraFSM::Start()
{
	for (auto state : stateMap)
	{
		state.second->Start();
	}
}

void ChimeraFSM::CreateAllState()
{
	for (int i = 0; i < (int)ChimeraStateType::End; ++i)
	{
		switch ((ChimeraStateType)i)
		{
		case ChimeraStateType::Idle:
			AddState(ChimeraStateType::Idle);
			break;
		case ChimeraStateType::NomalAttack:
			AddState(ChimeraStateType::NomalAttack);
			break;
		case ChimeraStateType::GroundAttack:
			AddState(ChimeraStateType::GroundAttack);
			break;
		case ChimeraStateType::VomitAttack:
			AddState(ChimeraStateType::VomitAttack);
			break;
		case ChimeraStateType::Pong:
			AddState(ChimeraStateType::Pong);
			break;
		case ChimeraStateType::DropGlass:
			AddState(ChimeraStateType::DropGlass);
			break;
		case ChimeraStateType::DropBall:
			AddState(ChimeraStateType::DropBall);
			break;
		case ChimeraStateType::DropPoison:
			AddState(ChimeraStateType::DropPoison);
			break;
		case ChimeraStateType::Dead:
			AddState(ChimeraStateType::Dead);
			break;
		case ChimeraStateType::End:
			break;
		default:
			break;
		}
	}
}

BaseState<ChimeraStateType>* ChimeraFSM::CreateState(ChimeraStateType type)
{
	ChimeraBaseState* state = nullptr;

	switch (type)
	{
	case ChimeraStateType::Idle:
		state = new ChimeraIdleState(this);
		break;
	case ChimeraStateType::NomalAttack:
		state = new ChimeraNomalAttackState(this);
		break;
	case ChimeraStateType::GroundAttack:
		state = new ChimeraGroundAttackState(this);
		break;
	case ChimeraStateType::VomitAttack:
		state = new ChimeraVomitAttackState(this);
		break;
	case ChimeraStateType::Pong:
		state = new ChimeraPongState(this);
		break;
	case ChimeraStateType::DropGlass:
		state = new ChimeraDropGlassState(this);
		break;
	case ChimeraStateType::DropBall:
		state = new ChimeraDropBallState(this);
		break;
	case ChimeraStateType::DropPoison:
		state = new ChimeraDropPoisonState(this);
		break;
	case ChimeraStateType::Dead:
		state = new ChimeraDeadState(this);
		break;
	case ChimeraStateType::End:
		break;
	default:
		break;
	}

	state->Awake();
	return state;
}

void ChimeraFSM::Update(float deltaTime)
{
	stateMap[currentStateType]->Update(deltaTime);
}

void ChimeraFSM::FixedUpdate(float fixedDeltaTime)
{
	stateMap[currentStateType]->FixedUpdate(fixedDeltaTime);
}

void ChimeraFSM::LateUpdate(float deltaTime)
{
	stateMap[currentStateType]->LateUpdate(deltaTime);
}
