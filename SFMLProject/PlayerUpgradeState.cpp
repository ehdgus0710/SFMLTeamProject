#include "stdafx.h"
#include "PlayerUpgradeState.h"

#include "Animation.h"
#include "Animator.h"
#include "Collider.h"

PlayerUpgradeState::PlayerUpgradeState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Hit)
	, currentCount(0)
{
	animationKeys.push_back("marioUpgrade");
	animationKeys.push_back("marioFireUpgrade");
}

PlayerUpgradeState::~PlayerUpgradeState()
{
}

void PlayerUpgradeState::StartEffect()
{
	if (player->GetCurrentHP() == 1)
	{
		sf::Vector2f currentOrigin = player->GetOrigin();
		player->GetAnimator()->ChangeAnimation(animationKeys[0], true, true);
		

		changePosition = player->GetPosition();
		changePosition.y -= 48.f;


		Animation* animation = player->GetAnimator()->GetCurrentAnimation();

		animation->SetAnimationStartEvent(std::bind(&PlayerUpgradeState::ChangePosition, this), 1);
		animation->SetAnimationEndEvent(std::bind(&PlayerUpgradeState::OnAnimationEnd, this), 2);
		// changePosition.y += (animation->GetFrameInfo()[0].rectSize.y - animation->GetFrameInfo()[2].rectSize.y) * 0.5f;
	}
	else if(player->GetCurrentHP() == 2)
	{
		player->GetAnimator()->ChangeAnimation(animationKeys[1], true, true);

		Animation* animation = player->GetAnimator()->GetCurrentAnimation();
		animation->SetAnimationEndEvent(std::bind(&PlayerUpgradeState::OnFireUpgrade, this), 1);
	}

	SoundManger::GetInstance().PlaySfx("PowerUp");

}

void PlayerUpgradeState::ChangePosition()
{
	player->SetPosition(changePosition);
	player->GetCollider()->SetScale(player->GetCollider()->GetScale() * 2.f);
}

void PlayerUpgradeState::OnAnimationEnd()
{
	fsm->ChangeState(PlayerStateType::Idle);
}

void PlayerUpgradeState::OnFireUpgrade()
{
	++currentCount;

	if (currentCount == 5)
	{
		Animation* animation = player->GetAnimator()->GetCurrentAnimation();
		animation->ClearEndEvent(1);
		fsm->ChangeState(PlayerStateType::Idle);		
	}
}

void PlayerUpgradeState::Awake()
{
}

void PlayerUpgradeState::Start()
{
}

void PlayerUpgradeState::Enter()
{
	PlayerBaseState::Enter();

	StartEffect();

	player->SetOrigin(Origins::MiddleCenter);
	player->GetCollider()->SetActive(false);
	TimeManager::GetInstance().SetTimeScale(0.f);
}

void PlayerUpgradeState::Exit()
{
	PlayerBaseState::Exit();
	TimeManager::GetInstance().SetTimeScale(1.f);
	player->GetCollider()->SetActive(true);

	if (player->GetCurrentHP() == 1)
	{
		player->SetPosition(changePosition);
		Animation* animation = player->GetAnimator()->GetCurrentAnimation();
		animation->ClearStartEvent(1);
		animation->ClearEndEvent(2);

	}
	player->AddHp();
}

void PlayerUpgradeState::Update(float deltaTime)
{
}

void PlayerUpgradeState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerUpgradeState::LateUpdate(float deltaTime)
{
}