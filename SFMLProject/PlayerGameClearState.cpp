#include "stdafx.h"
#include "PlayerGameClearState.h"
#include "Animator.h"
#include "Rigidbody.h"

PlayerGameClearState::PlayerGameClearState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::GameClear)
{
	animationKeys.push_back("marioSmallGrap");
	animationKeys.push_back("marioGrap");
	animationKeys.push_back("marioFireGrap");
}

PlayerGameClearState::~PlayerGameClearState()
{
}

void PlayerGameClearState::Awake()
{
}

void PlayerGameClearState::Start()
{
}

void PlayerGameClearState::Enter()
{
	PlayerBaseState::Enter();

	animationKeyIndex = player->GetCurrentHP() - 1;
	player->GetAnimator()->ChangeAnimation(animationKeys[animationKeyIndex], true);

	if (player->IsFlipX())
		player->OnFlipX();
}

void PlayerGameClearState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerGameClearState::Update(float deltaTime)
{
}

void PlayerGameClearState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerGameClearState::LateUpdate(float deltaTime)
{
}