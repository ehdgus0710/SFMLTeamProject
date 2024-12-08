#include "stdafx.h"
#include "PlayerDeadState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"
#include "Head.h"

PlayerDeadState::PlayerDeadState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Dead)
	, currentTime(0.f)
	, deadStateTime(1.f)
	, headRotationTime(2.5f)
	, head(nullptr)
{
}

void PlayerDeadState::Enter()
{
	PlayerBaseState::Enter();

	GameManager::GetInstance().PlayerDead();
	TimeManager::GetInstance().SetTimeScale(0.1f);

	head = player->GetHead();
	head->DeadThrowHead();

}

void PlayerDeadState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerDeadState::Update(float deltaTime)
{
	currentTime += TimeManager::GetInstance().GetUnScaleDeletaTime();

	head->SetRotation(Utils::Lerp(0.f, 360.f, currentTime / headRotationTime));
	head->SetPosition(head->GetPosition() + sf::Vector2f::up * 100.f * TimeManager::GetInstance().GetUnScaleDeletaTime());
	if (currentTime >= deadStateTime)
		GameManager::GetInstance().OnChangeScene();
}

void PlayerDeadState::FixedUpdate(float fixedDeltaTime)
{
	// head->FixedUpdate(TimeManager::GetInstance().GetUnScaleFixedDeletaTime());
}