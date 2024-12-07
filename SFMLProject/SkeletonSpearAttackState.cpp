#include "stdafx.h"
#include "SkeletonSpearAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "HitBoxObject.h"

SkeletonSpearAttackState::SkeletonSpearAttackState(SkeletonSpearFSM* fsm)
	: SkeletonSpearBaseState(fsm, SkeletonSpearStateType::Attack)
	, attackMoveSpeed(300.f)
{
	animationKeys.push_back("spearAttackA");


	damageInfo.damege = 10.f;
	damageInfo.useKnockback = true;
	damageInfo.knockbackDuration = 0.2f;
	damageInfo.owner = skeletonSpear;
	damageInfo.knockbackVelocity = { 30.f,0.f };
	damageInfo.hitDirection = sf::Vector2f::down;
}

SkeletonSpearAttackState::~SkeletonSpearAttackState()
{
}

void SkeletonSpearAttackState::Awake()
{
	SkeletonSpearBaseState::Awake();
}

void SkeletonSpearAttackState::Start()
{
	rigidbody = skeletonSpear->GetRigidbody();
	sequenceAttack = false;
}

void SkeletonSpearAttackState::Enter()
{
	SkeletonSpearBaseState::Enter();
	rigidbody->ResetVelocity();
	StartAttack();
}

void SkeletonSpearAttackState::Exit()
{
	SkeletonSpearBaseState::Exit();
}

void SkeletonSpearAttackState::Update(float deltaTime)
{
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::X))
	{
		sequenceAttack = true;
	}

}

void SkeletonSpearAttackState::FixedUpdate(float fixedDeltaTime)
{
}

void SkeletonSpearAttackState::EvenetClear()
{
	Animation* animation = animator->GetCurrentAnimation();
	animator->GetCurrentAnimation()->ClearEndEvent(animation->GetFrameCount() - 1);
}

void SkeletonSpearAttackState::CreateEffect(GameObject* object)
{
	AnimationGameObject* effect = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new AnimationGameObject("AttackEffect"), LayerType::Effect);
	Animation* animation(new Animation("animations/Effect/normalAttack.csv"));
	effect->GetAnimator()->AddAnimation(animation, "NormalAttack");
	effect->GetAnimator()->ChangeAnimation("NormalAttack");

	animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, effect), animation->GetEndFrameCount());
	effect->SetPosition(object->GetPosition());

	if (skeletonSpear->IsFlipX())
		effect->SetScale({ effect->GetScale().x * -2.f ,effect->GetScale().y * 2.f });
	else
		effect->SetScale(sf::Vector2f::one * 2.f);

	effect->Awake();
	effect->Start();
}

void SkeletonSpearAttackState::StartMove()
{
}

void SkeletonSpearAttackState::EndMove()
{
	rigidbody->ResetVelocity();
}

void SkeletonSpearAttackState::StartAttack()
{
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left) || InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
		rigidbody->SetVelocity((skeletonSpear->IsFlipX() ? sf::Vector2f::left * attackMoveSpeed : sf::Vector2f::right * attackMoveSpeed));

	currentAttackCount = 1;
	animator->ChangeAnimation("spearAttackA", false);

	Animation* animation = animator->GetCurrentAnimation();
	animation->SetAnimationEndEvent(std::bind(&SkeletonSpearAttackState::EndAttack, this), animation->GetFrameCount() - 1);

	animation->SetAnimationStartEvent(std::bind(&SkeletonSpearAttackState::EndMove, this), 2);
	animation->SetAnimationStartEvent(std::bind(&SkeletonSpearAttackState::OnCreateHitBox, this), 2);
	animation->SetAnimationEndEvent(std::bind(&SkeletonSpearAttackState::OnDestoryHitBox, this), 2);

}

void SkeletonSpearAttackState::NextAttack()
{
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left) || InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
		rigidbody->SetVelocity((skeletonSpear->IsFlipX() ? sf::Vector2f::left * attackMoveSpeed : sf::Vector2f::right * attackMoveSpeed));

	currentAttackCount = 2;
	animator->ChangeAnimation("spearAttackB", true);

	Animation* animation = animator->GetCurrentAnimation();

	animation->SetAnimationStartEvent(std::bind(&SkeletonSpearAttackState::EndMove, this), 1);
	animation->SetAnimationEndEvent(std::bind(&SkeletonSpearAttackState::EndAttack, this), animation->GetFrameCount() - 1);
	animation->SetAnimationStartEvent(std::bind(&SkeletonSpearAttackState::OnCreateHitBox, this), 1);
	animation->SetAnimationEndEvent(std::bind(&SkeletonSpearAttackState::OnDestoryHitBox, this), 1);
}

void SkeletonSpearAttackState::LastAttack()
{
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left) || InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
		rigidbody->SetVelocity((skeletonSpear->IsFlipX() ? sf::Vector2f::left * attackMoveSpeed : sf::Vector2f::right * attackMoveSpeed));

	currentAttackCount = 3;
	animator->ChangeAnimation("spearAttackC", true);

	Animation* animation = animator->GetCurrentAnimation();

	animation->SetAnimationStartEvent(std::bind(&SkeletonSpearAttackState::EndMove, this), 1);
	animation->SetAnimationEndEvent(std::bind(&SkeletonSpearAttackState::EndAttack, this), animation->GetFrameCount() - 1);
	animation->SetAnimationStartEvent(std::bind(&SkeletonSpearAttackState::OnCreateHitBox, this), 1);
	animation->SetAnimationEndEvent(std::bind(&SkeletonSpearAttackState::OnDestoryHitBox, this), 1);
}

void SkeletonSpearAttackState::EndAttack()
{
	if (sequenceAttack)
	{
		SequenceAttack();
	}
	else
	{
		rigidbody->ResetVelocity();
		EvenetClear();
		fsm->ChangeState(SkeletonSpearStateType::Idle);
	}
}

void SkeletonSpearAttackState::SequenceAttack()
{
	EvenetClear();
	if (currentAttackCount == 1)
	{
		NextAttack();
	}
	else if (currentAttackCount == 2)
	{
		LastAttack();
	}
	else
	{
		StartAttack();
	}

	sequenceAttack = false;
}

void SkeletonSpearAttackState::OnCreateHitBox()
{
	attackBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(skeletonSpear, ColliderLayer::PlayerBullet, ColliderLayer::Boss, true, sf::Vector2f::right * 50.f), LayerType::PlayerBullet);
	attackBox->SetScale({ 150.f,150.f });
	attackBox->SetDamage(damageInfo);

	attackBox->AddStartHitEvent(std::bind(&SkeletonSpearAttackState::CreateEffect, this, std::placeholders::_1));
	attackBox->Start();
}

void SkeletonSpearAttackState::OnDestoryHitBox()
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
