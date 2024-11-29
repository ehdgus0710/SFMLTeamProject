#include "stdafx.h"
#include "PlayerAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "HitBoxObject.h"

PlayerAttackState::PlayerAttackState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Attack)
{
	animationKeys.push_back("littleboneAttack");
	animationKeys.push_back("noheadlittleboneAttack");
}

PlayerAttackState::~PlayerAttackState()
{
}

void PlayerAttackState::Awake()
{
	PlayerBaseState::Awake();
}

void PlayerAttackState::Start()
{
	rigidbody = player->GetRigidbody();
	sequenceAttack = false;
}

void PlayerAttackState::Enter()
{
	PlayerBaseState::Enter();
	StartAttack();
}

void PlayerAttackState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerAttackState::Update(float deltaTime)
{
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::X))
	{
		sequenceAttack = true;
	}
}

void PlayerAttackState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerAttackState::EvenetClear()
{
	if (currentAttackCount == 2)
	{
		Animation* animation = animator->GetCurrentAnimation();
		animator->GetCurrentAnimation()->ClearEndEvent(animation->GetFrameCount() - 1);
	}
	else
	{
		Animation* animation = animator->GetCurrentAnimation();
		animator->GetCurrentAnimation()->ClearEndEvent(animation->GetFrameCount() - 1);
	}
}

void PlayerAttackState::StartAttack()
{
	currentAttackCount = 1;
	animator->ChangeAnimation(animationKeys[GetAnimationIndex()] + "1", false);

	Animation* animation = animator->GetCurrentAnimation();
	animation->SetAnimationEndEvent(std::bind(&PlayerAttackState::EndAttack, this), animation->GetFrameCount() - 1);
	animation->SetAnimationStartEvent(std::bind(&PlayerAttackState::OnCreateHitBox, this), 2);
	animation->SetAnimationEndEvent(std::bind(&PlayerAttackState::OnDestoryHitBox, this), 2);
}

void PlayerAttackState::NextAttack()
{
	currentAttackCount = 2;
	animator->ChangeAnimation(animationKeys[GetAnimationIndex()] + "2", true);

	Animation* animation = animator->GetCurrentAnimation();
	animation->SetAnimationEndEvent(std::bind(&PlayerAttackState::EndAttack, this), animation->GetFrameCount() - 1);
	animation->SetAnimationStartEvent(std::bind(&PlayerAttackState::OnCreateHitBox, this), 1);
	animation->SetAnimationEndEvent(std::bind(&PlayerAttackState::OnDestoryHitBox, this), 1);
}

void PlayerAttackState::EndAttack()
{
	if (sequenceAttack)
	{
		SequenceAttack();
	}
	else
	{
		EvenetClear();
		fsm->ChangeState(PlayerStateType::Idle);
	}
}

void PlayerAttackState::SequenceAttack()
{
	EvenetClear();
	if (currentAttackCount == 1)
	{
		NextAttack();
	}
	else
	{
		StartAttack();
	}

	sequenceAttack = false;
}

void PlayerAttackState::OnCreateHitBox()
{
	attackBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(player, ColliderLayer::PlayerBullet, ColliderLayer::Enemy), LayerType::PlayerBullet);
	attackBox->SetPosition(player->GetPosition() + (player->IsFlipX() ? sf::Vector2f::left * 30.f : sf::Vector2f::right * 30.f));
	attackBox->SetScale({ 50.f,50.f });
	attackBox->SetDamage(10);
}

void PlayerAttackState::OnDestoryHitBox()
{
	attackBox->OnDestory();
	attackBox->SetActive(false);
	attackBox = nullptr;

	if (currentAttackCount == 1)
	{
		Animation* animation = animator->GetCurrentAnimation();
		animation->ClearStartEvent(2);
		animation->ClearEndEvent(2);
	}
	else
	{
		Animation* animation = animator->GetCurrentAnimation();
		animation->ClearStartEvent(1);
		animation->ClearEndEvent(1);
	}
}
