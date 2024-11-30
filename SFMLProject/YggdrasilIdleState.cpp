#include "stdafx.h"
#include "YggdrasilIdleState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"
#include "Yggdrasil.h"
#include "Player.h"

void YggdrasilIdleState::Awake()
{
	YggdrasilBaseState::Awake();
}

void YggdrasilIdleState::Start()
{
	YggdrasilBaseState::Start();
}

void YggdrasilIdleState::Enter()
{
	YggdrasilBaseState::Enter();
}

void YggdrasilIdleState::Exit()
{
}

void YggdrasilIdleState::Update(float deltaTime)
{
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Numpad7))
	{
		fsm->ChangeState(YggdrasilStateType::FistAttack);
	}
	fsm->Update(deltaTime);
}

void YggdrasilIdleState::FixedUpdate(float fixedDeltaTime)
{
	fsm->FixedUpdate(fixedDeltaTime);
}

YggdrasilIdleState::YggdrasilIdleState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::Idle)
{
}
