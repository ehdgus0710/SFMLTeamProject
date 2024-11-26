#include "stdafx.h"
#include "PlayerIdleState.h"
#include "Animator.h"
#include "Rigidbody.h"

PlayerIdleState::PlayerIdleState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Idle)
{
}

PlayerIdleState::~PlayerIdleState()
{
}

void PlayerIdleState::Awake()
{
}

void PlayerIdleState::Start()
{
	rigidbody = player->GetRigidbody();
}

void PlayerIdleState::Enter()
{
	PlayerBaseState::Enter();

	// player->GetAnimator()->ChangeAnimation(animationKeys[animationKeyIndex], true);
}

void PlayerIdleState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerIdleState::Update(float deltaTime)
{
	if (InputManager::GetInstance().GetAxis(Axis::Horizontal) != 0.f)
		fsm->ChangeState(PlayerStateType::Run);

	if ((InputManager::GetInstance().GetKeyUp(sf::Keyboard::Space) || (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Space) && InputManager::GetInstance().GetAxis(Axis::Jump) == 1.f)))
	{
		if(rigidbody->IsGround())
			fsm->ChangeState(PlayerStateType::Jump);
	}
}

void PlayerIdleState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerIdleState::LateUpdate(float deltaTime)
{
}
