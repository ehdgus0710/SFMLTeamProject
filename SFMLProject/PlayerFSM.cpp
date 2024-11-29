#include "stdafx.h"
#include "PlayerFSM.h"

#include "PlayerIdleState.h"
#include "PlayerRunState.h"
#include "PlayerJumpState.h"
#include "PlayerDeadState.h"
#include "PlayerBaseState.h"
#include "PlayerHitState.h"
#include "PlayerFallingState.h"
#include "PlayerDashState.h"
#include "PlayerAttackState.h"

PlayerFSM::PlayerFSM(Player* owner)
	: owner(owner)
{
	CreateAllState();
}

PlayerFSM::PlayerFSM(Head* owner)
	: head(owner)
{
	CreateAllState();
}

PlayerFSM::~PlayerFSM()
{
}

void PlayerFSM::Awake()
{
}

void PlayerFSM::Start()
{
	for (auto state : stateMap)
	{
		state.second->Start();
	}
}

void PlayerFSM::CreateAllState()
{
	for (int i = 0; i < (int)PlayerStateType::End; ++i)
	{
		switch ((PlayerStateType)i)
		{
		case PlayerStateType::Idle:
			AddState(PlayerStateType::Idle);
			break;
		case PlayerStateType::Run:
			AddState(PlayerStateType::Run);
			break;
		case PlayerStateType::Jump:
			AddState(PlayerStateType::Jump);
			break;
		case PlayerStateType::Hit:
			AddState(PlayerStateType::Hit);
			break;
		case PlayerStateType::Dead:
			AddState(PlayerStateType::Dead);
			break;
		case PlayerStateType::Falling:
			AddState(PlayerStateType::Falling);
			break;
		case PlayerStateType::Dash:
			AddState(PlayerStateType::Dash);
			break;
		case PlayerStateType::Attack:
			AddState(PlayerStateType::Attack);
			break;
		case PlayerStateType::End:
			break;
		default:
			break;
		}
	}
}

BaseState<PlayerStateType>* PlayerFSM::CreateState(PlayerStateType type)
{
	PlayerBaseState* state = nullptr;

	switch (type)
	{
	case PlayerStateType::Idle:
		state = new PlayerIdleState(this);
		break;
	case PlayerStateType::Run:
		state = new PlayerRunState(this);
		break;
	case PlayerStateType::Jump:
		state = new PlayerJumpState(this);
		break;
	case PlayerStateType::Hit:
		state = new PlayerHitState(this);
		break;
	case PlayerStateType::Dead:
		state = new PlayerDeadState(this);
		break;
	case PlayerStateType::Falling:
		state = new PlayerFallingState(this);
		break;
	case PlayerStateType::Dash:
		state = new PlayerDashState(this);
		break;
	case PlayerStateType::Attack:
		state = new PlayerAttackState(this);
		break;
	case PlayerStateType::End:
		break;
	default:
		break;
	}

	state->Awake();
	return state;
}

PlayerBaseState* PlayerFSM::GetCurrentState()
{ 
	return (PlayerBaseState*)stateMap[currentStateType];
}

void PlayerFSM::Update(float deltaTime)
{
	stateMap[currentStateType]->Update(deltaTime);
}

void PlayerFSM::FixedUpdate(float fixedDeltaTime)
{
	stateMap[currentStateType]->FixedUpdate(fixedDeltaTime);
}

void PlayerFSM::LateUpdate(float deltaTime)
{
	stateMap[currentStateType]->LateUpdate(deltaTime);
}
