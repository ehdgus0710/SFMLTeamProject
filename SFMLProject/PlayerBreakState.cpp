#include "stdafx.h"
#include "PlayerBreakState.h"
#include "Rigidbody.h"
#include "Animator.h"

PlayerBreakState::PlayerBreakState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Run)
	, rigidbody(nullptr)
	, horizontal(0.f)
	, isMoveDirectionLeft(false)
	, breakTime(0.2f)
	, currentBreakTime(0.f)

{
	animationKeys.push_back("marioSmallBreak");
	animationKeys.push_back("marioBreak");
	animationKeys.push_back("marioFireBreak");
}

PlayerBreakState::~PlayerBreakState()
{
}

void PlayerBreakState::Awake()
{
}

void PlayerBreakState::Start()
{
	rigidbody = player->GetRigidbody();
}
void PlayerBreakState::Enter()
{
	PlayerBaseState::Enter(); 
	animationKeyIndex = player->GetCurrentHP() - 1;
	player->GetAnimator()->ChangeAnimation(animationKeys[animationKeyIndex], true);

	horizontal = InputManager::GetInstance().GetAxis(Axis::Horizontal);
	isMoveDirectionLeft = horizontal > 0.f ? false : true;
	rigidbody->SetVelocity({ 0.f,  rigidbody->GetCurrentVelocity().y });

	if ((!isMoveDirectionLeft && !player->IsFlipX()) || (isMoveDirectionLeft && player->IsFlipX()))
		player->OnFlipX();

}

void PlayerBreakState::Exit()
{
	rigidbody->SetVelocity({ 0.f , rigidbody->GetCurrentVelocity().y });
	PlayerBaseState::Exit();
}

void PlayerBreakState::Update(float deltaTime)
{
	if(isMoveDirectionLeft && InputManager::GetInstance().GetAxis(Axis::Horizontal) >= 0.f)
		fsm->ChangeState(PlayerStateType::Idle);
	else if (!isMoveDirectionLeft && InputManager::GetInstance().GetAxis(Axis::Horizontal) <= 0.f)
		fsm->ChangeState(PlayerStateType::Idle);


	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Space) || (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Space) && InputManager::GetInstance().GetAxis(Axis::Jump) == 1.f))
	{
		fsm->ChangeState(PlayerStateType::Jump);
	}
}

void PlayerBreakState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ (isMoveDirectionLeft ? -40.f : 40.f)  , rigidbody->GetCurrentVelocity().y });
}