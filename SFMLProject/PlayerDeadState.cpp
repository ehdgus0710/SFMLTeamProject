#include "stdafx.h"
#include "PlayerDeadState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"

PlayerDeadState::PlayerDeadState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Dead)
	, currentTime(0.f)
	, deadStateTime(1.f)
{
}

void PlayerDeadState::Enter()
{
	PlayerBaseState::Enter();

	GameManager::GetInstance().PlayerDead();
	TimeManager::GetInstance().SetTimeScale(0.f);
}

void PlayerDeadState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerDeadState::Update(float deltaTime)
{
	currentTime += TimeManager::GetInstance().GetUnScaleDeletaTime();

	if (currentTime >= deadStateTime)
		GameManager::GetInstance().OnChangeScene();
}

void PlayerDeadState::FixedUpdate(float fixedDeltaTime)
{
}