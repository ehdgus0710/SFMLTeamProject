#include "stdafx.h"
#include "PlayerHitState.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

PlayerHitState::PlayerHitState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Hit)
	, currentTime(0.f)
{
}

PlayerHitState::~PlayerHitState()
{
}

void PlayerHitState::StartEffect()
{
	if (player->GetCurrentHP() == 1)
	{
		// 공격 애니메이션으로 변경
		player->GetAnimator()->ChangeAnimation("marioHit", true, true);
		player->GetCollider()->SetScale(player->GetCollider()->GetScale() * 0.5f);

		
		// 현재 애니메이션은 공격 애니메이션으로 변경 됨
		Animation* animation = player->GetAnimator()->GetCurrentAnimation();
		
		// 현재 애니메이션을 가져와서 공격 이벤트를 넣어주는 상태
		animation->SetAnimationStartEvent(std::bind(&PlayerHitState::ChangePosition ,this ), 2);
		animation->SetAnimationStartEvent(std::bind(&PlayerHitState::ChangePosition, this), 5);

		animation->SetAnimationEndEvent(std::bind(&PlayerHitState::ReturnPosition, this), 2);
		animation->SetAnimationEndEvent(std::bind(&PlayerHitState::ReturnPosition, this), 5);
	}
}

void PlayerHitState::ChangePosition()
{
	player->SetPosition(changePosition);
}

void PlayerHitState::ReturnPosition()
{
	player->SetPosition(originalPosition);
}

void PlayerHitState::Awake()
{
}

void PlayerHitState::Start()
{
}

void PlayerHitState::Enter()
{
	PlayerBaseState::Enter();
}

void PlayerHitState::Exit()
{
	PlayerBaseState::Exit();

	/*if (player->GetCurrentHP() == 1)
	{
		player->SetPosition(changePosition);
		Animation* animation = player->GetAnimator()->GetCurrentAnimation();
		animation->ClearStartEvent(2);
		animation->ClearEndEvent(2);
		animation->ClearStartEvent(5);
		animation->ClearEndEvent(5);
	}*/
}

void PlayerHitState::Update(float deltaTime)
{
	currentTime += TimeManager::GetInstance().GetUnScaleDeletaTime();

	if (currentTime >= 1.f)
	{
		fsm->ChangeState(PlayerStateType::Idle);
		currentTime = 0.f;
 	}
}

void PlayerHitState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerHitState::LateUpdate(float deltaTime)
{
}
