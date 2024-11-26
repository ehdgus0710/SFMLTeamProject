#include "stdafx.h"
#include "PlayerDownState.h"
#include "Animator.h"
#include "Rigidbody.h"
#include "Collider.h"

PlayerDownState::PlayerDownState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Down)
	, rigidbody(nullptr)
{
	animationKeys.push_back("marioSmallDown");
	animationKeys.push_back("marioDown");
	animationKeys.push_back("marioFireDown");
}

PlayerDownState::~PlayerDownState()
{
}

void PlayerDownState::Awake()
{
}

void PlayerDownState::Start()
{
	rigidbody = player->GetRigidbody();
}

void PlayerDownState::Enter()
{
	PlayerBaseState::Enter();

	animationKeyIndex = player->GetCurrentHP() - 1;
	player->GetAnimator()->ChangeAnimation(animationKeys[animationKeyIndex], true);

	sf::Vector2f scale = player->GetCollider()->GetScale();
	scale.y *= 0.5f;
	player->GetCollider()->SetScale(scale);
	player->GetCollider()->SetOffsetPosition({ 0.f, scale.y * 0.5f });
}

void PlayerDownState::Exit()
{ 
	sf::Vector2f scale = player->GetCollider()->GetScale();
	player->GetCollider()->SetOffsetPosition({ 0.f, 0.f });
	scale.y *= 2.f;
	player->GetCollider()->SetScale(scale);
	PlayerBaseState::Exit();
}

void PlayerDownState::Update(float deltaTime)
{
	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::Down))
	{
		fsm->ChangeState(PlayerStateType::Idle);
	}
}

void PlayerDownState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerDownState::LateUpdate(float deltaTime)
{
}
