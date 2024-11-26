#include "stdafx.h"
#include "PlayerHitState.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

PlayerHitState::PlayerHitState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Hit)
	, currentTime(0.f)
{
	animationKeys.push_back("marioSmallHit");
	animationKeys.push_back("marioHit");
}

PlayerHitState::~PlayerHitState()
{
}

void PlayerHitState::StartEffect()
{
	if (player->GetCurrentHP() == 1)
	{
		sf::Vector2f currentOrigin = player->GetOrigin();
		player->SetOrigin(Origins::BottomCenter);
		currentOrigin = player->GetOrigin();
		currentOrigin.y = 152.f * 0.5f;
		//player->SetPosition(player->GetPosition() + currentOrigin);
		player->GetAnimator()->ChangeAnimation("marioHit", true, true);
		player->GetCollider()->SetScale(player->GetCollider()->GetScale() * 0.5f);

		Animation* animation = player->GetAnimator()->GetCurrentAnimation();
		
		animation->SetAnimationStartEvent(std::bind(&PlayerHitState::ChangePosition ,this ), 2);
		animation->SetAnimationStartEvent(std::bind(&PlayerHitState::ChangePosition, this), 5);

		animation->SetAnimationEndEvent(std::bind(&PlayerHitState::ReturnPosition, this), 2);
		animation->SetAnimationEndEvent(std::bind(&PlayerHitState::ReturnPosition, this), 5);

		originalPosition = player->GetPosition();
		changePosition = originalPosition;
		changePosition.y += (animation->GetFrameInfo()[0].rectSize.y - animation->GetFrameInfo()[2].rectSize.y) * 0.5f;
	}


	//player->SetOrigin(Origins::MiddleCenter);
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

	currentTime = 0.f;

	StartEffect();

	SoundManger::GetInstance().PlaySfx("PowerUpAppears");

	player->SetOrigin(Origins::MiddleCenter);
	player->GetCollider()->SetActive(false);
	TimeManager::GetInstance().SetTimeScale(0.f);
}

void PlayerHitState::Exit()
{
	PlayerBaseState::Exit();
	TimeManager::GetInstance().SetTimeScale(1.f);
	player->GetCollider()->SetActive(true);

	if (player->GetCurrentHP() == 1)
	{
		player->SetPosition(changePosition);
		Animation* animation = player->GetAnimator()->GetCurrentAnimation();
		animation->ClearStartEvent(2);
		animation->ClearEndEvent(2);
		animation->ClearStartEvent(5);
		animation->ClearEndEvent(5);
	}
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
