#include "stdafx.h"
#include "PlayerHitState.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"
#include "Rigidbody.h"

PlayerHitState::PlayerHitState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Hit)
	, currentTime(0.f)
	, rigidbody(nullptr)
{
}

PlayerHitState::~PlayerHitState()
{
}

void PlayerHitState::SetDamageInfo(const DamegeInfo& damage)
{
	currentDamageInfo = damage;
}

void PlayerHitState::Awake()
{
	PlayerBaseState::Awake();

}

void PlayerHitState::Start()
{
	rigidbody = player->GetRigidbody();
}

void PlayerHitState::Enter()
{
	PlayerBaseState::Enter();

	currentTime = 0.f;
	rigidbody->ResetVelocity();

	if (currentDamageInfo.hitDirection == sf::Vector2f::down || currentDamageInfo.hitDirection == sf::Vector2f::up)
	{
		if (player->GetPosition().x < currentDamageInfo.owner->GetPosition().x)
			rigidbody->SetVelocity(sf::Vector2f::right * currentDamageInfo.knockbackVelocity);
		else
			rigidbody->SetVelocity(sf::Vector2f::left * currentDamageInfo.knockbackVelocity);
	}
	else
	{
		if (currentDamageInfo.knockbackVelocity.y != 0.f && rigidbody->GetCurrentVelocity().y == 0.f)
		{
			rigidbody->SetGround(false);
		}

		rigidbody->SetVelocity(currentDamageInfo.knockbackVelocity);
	}
}

void PlayerHitState::Exit()
{
	PlayerBaseState::Exit();

	rigidbody->SetVelocity({0.f, rigidbody->GetCurrentVelocity().y});
}

void PlayerHitState::Update(float deltaTime)
{
	currentTime += deltaTime;
	if (currentTime >= currentDamageInfo.knockbackDuration)
	{
		if(rigidbody->GetCurrentVelocity().y != 0.f)
			fsm->ChangeState(PlayerStateType::Falling);
		else
			fsm->ChangeState(PlayerStateType::Idle);
	}
}