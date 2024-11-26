#include "stdafx.h"
#include "PlayerFSM.h"

#include "PlayerIdleState.h"
#include "PlayerBreakState.h"
#include "PlayerRunState.h"
#include "PlayerJumpState.h"
#include "PlayerDeadState.h"
#include "PlayerBaseState.h"
#include "PlayerHitState.h"
#include "PlayerUpgradeState.h"
#include "PlayerGameClearState.h"
#include "PlayerDownState.h"

PlayerFSM::PlayerFSM(Player* owner)
	: owner(owner)
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
		case PlayerStateType::Break:
			AddState(PlayerStateType::Break);
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
		case PlayerStateType::Upgrade:
			AddState(PlayerStateType::Upgrade);
			break;
		case PlayerStateType::GameClear:
			AddState(PlayerStateType::GameClear);
			break;
		case PlayerStateType::Down:
			AddState(PlayerStateType::Down);
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
	case PlayerStateType::Break:
		state = new PlayerBreakState(this);
		break;
	case PlayerStateType::Jump:
		state = new PlayerJumpState(this);
		break;
	case PlayerStateType::Hit:
		state= new PlayerHitState(this);
		break;
	case PlayerStateType::Dead:
		state = new PlayerDeadState(this);
		break;
	case PlayerStateType::Upgrade:
		state = new PlayerUpgradeState(this);
		break;
	case PlayerStateType::GameClear:
		state = new PlayerGameClearState(this);
		break;
	case PlayerStateType::Down:
		state = new PlayerDownState(this);
		break;
	case PlayerStateType::End:
		break;
	default:
		break;
	}

	state->Awake();
	return state;
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
