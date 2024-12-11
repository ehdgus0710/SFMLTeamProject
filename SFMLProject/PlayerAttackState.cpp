#include "stdafx.h"
#include "PlayerAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "HitBoxObject.h"

PlayerAttackState::PlayerAttackState(PlayerFSM* fsm)
	: PlayerBaseState(fsm, PlayerStateType::Attack)
	, attackMoveSpeed(300.f)
{
	animationKeys.push_back("littleboneAttack");
	animationKeys.push_back("noheadlittleboneAttack");

	damageInfo.damege = 10.f;
	damageInfo.useKnockback = true;
	damageInfo.knockbackDuration = 0.2f;
	damageInfo.owner = player;
	damageInfo.knockbackVelocity = { 30.f,0.f };
	damageInfo.hitDirection = sf::Vector2f::down;

	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("SkulAtk1", "AudioClip/Skul/Skul_Atk 1.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("SkulAtk2", "AudioClip/Skul/Skul_Atk 2.wav");
}

PlayerAttackState::~PlayerAttackState()
{
}

void PlayerAttackState::SetChangeAnimationKey(int index)
{
	ClearAttackEvent();
	ClearEndAttackEvenet();
	
	PlayerBaseState::SetChangeAnimationKey(index);
	SetAnimationEvent();
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
	rigidbody->ResetVelocity();
	StartAttack(); 
}

void PlayerAttackState::Exit()
{
	PlayerBaseState::Exit();
}

void PlayerAttackState::Update(float deltaTime)
{
	if (KeyActionManager::GetInstance().GetKeyDown(ActionKeyType::Attack))
	{
		sequenceAttack = true;
	}

}

void PlayerAttackState::FixedUpdate(float fixedDeltaTime)
{
}

void PlayerAttackState::ClearEndAttackEvenet()
{
	Animation* animation = animator->GetCurrentAnimation();
	animator->GetCurrentAnimation()->ClearEndEvent(animation->GetEndFrameCount());
}

void PlayerAttackState::CreateEffect(GameObject* object)
{
	AnimationGameObject* effect = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new AnimationGameObject("AttackEffect"), LayerType::Effect);
	Animation* animation(new Animation("animations/Effect/normalAttack.csv"));
	effect->GetAnimator()->AddAnimation(animation, "NormalAttack");
	effect->GetAnimator()->ChangeAnimation("NormalAttack");
	
	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, effect), animation->GetEndFrameCount());
	effect->SetPosition(object->GetPosition());

	if (player->IsFlipX())
		effect->SetScale({ effect->GetScale().x * -2.f ,effect->GetScale().y * 2.f});
	else
		effect->SetScale(sf::Vector2f::one * 2.f);

	effect->Awake();
	effect->Start();
}

void PlayerAttackState::StartMove()
{
}

void PlayerAttackState::EndMove()
{
	rigidbody->ResetVelocity();
}

void PlayerAttackState::SetAnimationEvent()
{
	Animation* animation = animator->GetCurrentAnimation();

	if (currentAttackCount == 1)
	{
		animation->SetAnimationStartEvent(std::bind(&PlayerAttackState::EndMove, this), 2);
		animation->SetAnimationStartEvent(std::bind(&PlayerAttackState::OnCreateHitBox, this), 2);
		animation->SetAnimationEndEvent(std::bind(&PlayerAttackState::OnDestoryHitBox, this), 2);
	}
	else
	{
		animation->SetAnimationStartEvent(std::bind(&PlayerAttackState::EndMove, this), 1);
		animation->SetAnimationStartEvent(std::bind(&PlayerAttackState::OnCreateHitBox, this), 1);
		animation->SetAnimationEndEvent(std::bind(&PlayerAttackState::OnDestoryHitBox, this), 1);
	}
	animation->SetAnimationEndEvent(std::bind(&PlayerAttackState::EndAttack, this), animation->GetEndFrameCount());
}

void PlayerAttackState::ClearAttackEvent()
{
	Animation* animation = animator->GetCurrentAnimation();
	if (currentAttackCount == 1)
	{
		animation->ClearStartEvent(2);
		animation->ClearEndEvent(2);
	}
	else
	{
		animation->ClearStartEvent(1);
		animation->ClearEndEvent(1);
	}
}

void PlayerAttackState::MoveAttack()
{
	if (KeyActionManager::GetInstance().GetKeyPressed(ActionKeyType::LeftMove))
	{
		if (!player->IsFlipX())
			player->OnFlipX();

		rigidbody->SetVelocity(sf::Vector2f::left * attackMoveSpeed);
	
	}
	else if (KeyActionManager::GetInstance().GetKeyPressed(ActionKeyType::RightMove))
	{
		if (player->IsFlipX())
			player->OnFlipX();

		rigidbody->SetVelocity(sf::Vector2f::right * attackMoveSpeed);
	}

}

void PlayerAttackState::StartAttack()
{
	MoveAttack();

	currentAttackCount = 1;
	animator->ChangeAnimation(animationKeys[GetAnimationIndex()] + "1", false);

	SetAnimationEvent();
}

void PlayerAttackState::NextAttack()
{
	MoveAttack();

	currentAttackCount = 2;
	animator->ChangeAnimation(animationKeys[GetAnimationIndex()] + "2", true);

	SetAnimationEvent();
}

void PlayerAttackState::EndAttack()
{
	if (sequenceAttack)
	{
		SequenceAttack();
	}
	else
	{
		rigidbody->ResetVelocity();
		ClearEndAttackEvenet();
		fsm->ChangeState(PlayerStateType::Idle);
	}
}

void PlayerAttackState::SequenceAttack()
{
	ClearEndAttackEvenet();
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
	if (attackBox)
		attackBox->OnDestory();

	attackBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(player, ColliderLayer::PlayerBullet, ColliderLayer::Reiana, true, sf::Vector2f::right * 50.f), LayerType::PlayerBullet);
	attackBox->SetScale({ 150.f,150.f });
	attackBox->SetDamage(damageInfo);

	attackBox->AddStartHitEvent(std::bind(&PlayerAttackState::CreateEffect, this, std::placeholders::_1));
	attackBox->AddStartHitEvent(std::bind(&Player::OnAttackHitSound, player, std::placeholders::_1));
	attackBox->Start();

	if(currentAttackCount == 1)
		SoundManger::GetInstance().PlaySfx("SkulAtk1");
	else
		SoundManger::GetInstance().PlaySfx("SkulAtk2");
}

void PlayerAttackState::OnDestoryHitBox()
{
	attackBox->OnDestory();
	attackBox->SetActive(false);
	attackBox = nullptr;

	ClearAttackEvent();
}
