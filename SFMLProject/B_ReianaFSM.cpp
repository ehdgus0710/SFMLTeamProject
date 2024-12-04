#include "stdafx.h"
#include "B_ReianaFsm.h"

#include "B_ReianaIdleState.h"
#include "B_ReianaGroundAttackState.h"
#include "B_ReianaThreeSwordState.h"
#include "B_ReianaDropAttackState.h"
#include "B_ReianaDeadState.h"
#include "B_ReianaDashState.h"

B_ReianaFsm::B_ReianaFsm(B_Reiana* owner)
	: owner(owner)
{
	CreateAllState();
}

B_ReianaFsm::~B_ReianaFsm()
{
}

void B_ReianaFsm::Awake()
{
}

void B_ReianaFsm::Start()
{
	for (auto state : stateMap)
	{
		state.second->Start();
	}
}

void B_ReianaFsm::CreateAllState()
{
	for (int i = 0; i < (int)B_ReianaStateType::End; ++i)
	{
		switch ((B_ReianaStateType)i)
		{
		case B_ReianaStateType::Idle:
			AddState(B_ReianaStateType::Idle);
			break;
		case B_ReianaStateType::GroundAttack:
			AddState(B_ReianaStateType::GroundAttack);
			break;
		case B_ReianaStateType::ThreeSword:
			AddState(B_ReianaStateType::ThreeSword);
			break;
		case B_ReianaStateType::DropAttack:
			AddState(B_ReianaStateType::DropAttack);
			break;
		case B_ReianaStateType::Dash:
			AddState(B_ReianaStateType::Dash);
			break;
		case B_ReianaStateType::Dead:
			AddState(B_ReianaStateType::Dead);
			break;
		case B_ReianaStateType::End:
			break;
		default:
			break;
		}
	}
}

BaseState<B_ReianaStateType>* B_ReianaFsm::CreateState(B_ReianaStateType type)
{
	B_ReianaBaseState* state = nullptr;

	switch (type)
	{
	case B_ReianaStateType::Idle:
		state = new B_ReianaIdleState(this);
		break;
	case B_ReianaStateType::GroundAttack:
		state = new B_ReianaGroundAttackState(this);
		break;
	case B_ReianaStateType::ThreeSword:
		state = new B_ReianaThreeSwordState(this);
		break;
	case B_ReianaStateType::DropAttack:
		state = new B_ReianaDropAttackState(this);
		break;
	case B_ReianaStateType::Dash:
		state = new B_ReianaDashState(this);
		break;
	case B_ReianaStateType::Dead:
		state = new B_ReianaDeadState(this);
		break;
	case B_ReianaStateType::End:
		break;
	default:
		break;
	}

	state->Awake();
	return state;
}

void B_ReianaFsm::Update(float deltaTime)
{
	stateMap[currentStateType]->Update(deltaTime);
}

void B_ReianaFsm::FixedUpdate(float fixedDeltaTime)
{
	stateMap[currentStateType]->FixedUpdate(fixedDeltaTime);
}

void B_ReianaFsm::LateUpdate(float deltaTime)
{
	stateMap[currentStateType]->LateUpdate(deltaTime);
}
