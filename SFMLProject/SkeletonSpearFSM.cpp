#include "stdafx.h"
#include "SkeletonSpearFSM.h"

#include "SkeletonSpearIdleState.h"
#include "SkeletonSpearRunState.h"
#include "SkeletonSpearJumpState.h"
#include "SkeletonSpearDeadState.h"
#include "SkeletonSpearBaseState.h"
#include "SkeletonSpearHitState.h"
#include "SkeletonSpearFallingState.h"
#include "SkeletonSpearDashState.h"
#include "SkeletonSpearAttackState.h"
#include "SkeletonSpearSkill1State.h"
#include "SkeletonSpearSkill2State.h"
#include "SkeletonSpearJumpAttackState.h"

SkeletonSpearFSM::SkeletonSpearFSM(SkeletonSpear* owner)
    : owner(owner)
{
	CreateAllState();
}

SkeletonSpearFSM::~SkeletonSpearFSM()
{
}


void SkeletonSpearFSM::CreateAllState()
{
	for (int i = 0; i < (int)SkeletonSpearStateType::End; ++i)
	{
		switch ((SkeletonSpearStateType)i)
		{
		case SkeletonSpearStateType::Idle:
			AddState(SkeletonSpearStateType::Idle);
			break;
		case SkeletonSpearStateType::Run:
			AddState(SkeletonSpearStateType::Run);
			break;
		case SkeletonSpearStateType::Jump:
			AddState(SkeletonSpearStateType::Jump);
			break;
		case SkeletonSpearStateType::Hit:
			AddState(SkeletonSpearStateType::Hit);
			break;
		case SkeletonSpearStateType::Dead:
			AddState(SkeletonSpearStateType::Dead);
			break;
		case SkeletonSpearStateType::Falling:
			AddState(SkeletonSpearStateType::Falling);
			break;
		case SkeletonSpearStateType::Dash:
			AddState(SkeletonSpearStateType::Dash);
			break;
		case SkeletonSpearStateType::Attack:
			AddState(SkeletonSpearStateType::Attack);
			break;
		case SkeletonSpearStateType::JumpAttack:
			AddState(SkeletonSpearStateType::JumpAttack);
			break;
		case SkeletonSpearStateType::Skill1:
			AddState(SkeletonSpearStateType::Skill1);
			break;
		case SkeletonSpearStateType::Skill2:
			AddState(SkeletonSpearStateType::Skill2);
			break;
		case SkeletonSpearStateType::End:
			break;
		default:
			break;
		}
	}
}

BaseState<SkeletonStateType>* SkeletonSpearFSM::CreateState(SkeletonStateType type)
{
	SkeletonSpearBaseState* state = nullptr;

	switch (type)
	{
	case SkeletonSpearStateType::Idle:
		state = new SkeletonSpearIdleState(this);
		break;
	case SkeletonSpearStateType::Run:
		state = new SkeletonSpearRunState(this);
		break;
	case SkeletonSpearStateType::Jump:
		state = new SkeletonSpearJumpState(this);
		break;
	case SkeletonSpearStateType::Hit:
		state = new SkeletonSpearHitState(this);
		break;
	case SkeletonSpearStateType::Dead:
		state = new SkeletonSpearDeadState(this);
		break;
	case SkeletonSpearStateType::Falling:
		state = new SkeletonSpearFallingState(this);
		break;
	case SkeletonSpearStateType::Dash:
		state = new SkeletonSpearDashState(this);
		break;
	case SkeletonSpearStateType::Attack:
		state = new SkeletonSpearAttackState(this);
		break;
	case SkeletonSpearStateType::JumpAttack:
		state = new SkeletonSpearJumpAttackState(this);
		break;
	case SkeletonSpearStateType::Skill1:
		state = new SkeletonSpearSkill1State(this);
		break;
	case SkeletonSpearStateType::Skill2:
		state = new SkeletonSpearSkill2State(this);
		break;
	case SkeletonSpearStateType::End:
		break;
	default:
		break;
	}

	state->Awake();
	return state;
}

SkeletonSpearBaseState* SkeletonSpearFSM::GetCurrentState()
{
	return (SkeletonSpearBaseState*)stateMap[currentStateType];
}

SkeletonSpearBaseState* SkeletonSpearFSM::GetState(PlayerStateType type)
{
	auto iter = stateMap.find(type);
	if (iter != stateMap.end())
		return (SkeletonSpearBaseState*)iter->second;

	return nullptr;
}

void SkeletonSpearFSM::Awake()
{
}

void SkeletonSpearFSM::Start()
{
    for (auto state : stateMap)
    {
        state.second->Start();
    }
}

void SkeletonSpearFSM::Update(float deltaTime)
{
	if (!InputManager::GetInstance().GetInputable())
		stateMap[currentStateType]->Update(deltaTime);
}

void SkeletonSpearFSM::FixedUpdate(float fixedDeltaTime)
{
	if (!InputManager::GetInstance().GetInputable())
		stateMap[currentStateType]->FixedUpdate(fixedDeltaTime);
}

void SkeletonSpearFSM::LateUpdate(float deltaTime)
{
	if (!InputManager::GetInstance().GetInputable())
		stateMap[currentStateType]->LateUpdate(deltaTime);
}

