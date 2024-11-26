#include "stdafx.h"
#include "PlayerDeadState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"

PlayerDeadState::PlayerDeadState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Dead)
	, waitTime(0.5f)
	, currentWaitTime(0.f)
	, isWait(true)
{
}

void PlayerDeadState::Enter()
{
	PlayerBaseState::Enter();

	currentWaitTime = 0.f;
	isWait = true;

	SoundManger::GetInstance().StopBgm();
	SoundManger::GetInstance().PlaySfx("DeathBGM");

	player->GetAnimator()->ChangeAnimation("marioDead", true, true);
	TimeManager::GetInstance().SetTimeScale(0.f);

	player->GetRigidbody()->SetGround(false);
	player->GetCollider()->SetActive(false);
}

void PlayerDeadState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerDeadState::Update(float deltaTime)
{
	currentWaitTime += TimeManager::GetInstance().GetUnScaleDeletaTime();

	if (isWait && currentWaitTime >= waitTime)
	{
  		player->GetRigidbody()->SetVelocity({ 0.f, -1000.f });
		isWait = !isWait;
	}

	if(currentWaitTime >= 3.f)
		GameManager::GetInstance().PlayerDie();
}

void PlayerDeadState::FixedUpdate(float fixedDeltaTime)
{
	if(!isWait)
		player->GetRigidbody()->FixedUpdate(TimeManager::GetInstance().GetUnScaleFixedDeletaTime() * 0.8f);
}