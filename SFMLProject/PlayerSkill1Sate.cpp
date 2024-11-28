#include "stdafx.h"
#include "PlayerSkill1Sate.h"

void PlayerSkill1Sate::Awake()
{
	PlayerBaseState::Awake();
}

void PlayerSkill1Sate::Start()
{
	rigidbody = player->GetRigidbody();
}

void PlayerSkill1Sate::Enter()
{
	PlayerBaseState::Enter();

}

void PlayerSkill1Sate::Exit()
{
}

void PlayerSkill1Sate::Update(float deltaTime)
{
}

void PlayerSkill1Sate::FixedUpdate(float fixedDeltaTime)
{
}

PlayerSkill1Sate::PlayerSkill1Sate(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Dash)
{
}

PlayerSkill1Sate::~PlayerSkill1Sate()
{
}
