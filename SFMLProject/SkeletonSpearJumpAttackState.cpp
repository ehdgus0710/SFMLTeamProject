#include "stdafx.h"
#include "SkeletonSpearJumpAttackState.h"
#include "Rigidbody.h"
#include "Animation.h"
#include "Animator.h"
#include "HitBoxObject.h"

SkeletonSpearJumpAttackState::SkeletonSpearJumpAttackState(SkeletonSpearFSM* fsm)
	: SkeletonSpearBaseState(fsm, SkeletonSpearStateType::JumpAttack)
	, rigidbody(nullptr)
	, horizontal(0)
	, attackBox(nullptr)
	, sequenceAttack(false)
{
	animationKeys.push_back("littleboneJumpAttack");
	animationKeys.push_back("noheadlittleboneJumpAttack");

	damageInfo.damege = 10.f;
	damageInfo.useKnockback = true;
	damageInfo.knockbackDuration = 0.2f;
	damageInfo.owner = skeletonSpear;
	damageInfo.knockbackVelocity = { 30.f,0.f };
	damageInfo.hitDirection = sf::Vector2f::down;
}

SkeletonSpearJumpAttackState::~SkeletonSpearJumpAttackState()
{
}

void SkeletonSpearJumpAttackState::Start()
{
	rigidbody = skeletonSpear->GetRigidbody();
}

void SkeletonSpearJumpAttackState::Enter()
{
	SkeletonSpearBaseState::Enter();

	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], false);
	OnStartAttack();
}

void SkeletonSpearJumpAttackState::Exit()
{
	ClearEvenet();

	if (attackBox)
	{
		OnDestoryHitBox();
	}

	SkeletonSpearBaseState::Exit();
	horizontal = 0.f;
	sequenceAttack = false;
}

void SkeletonSpearJumpAttackState::Update(float deltaTime)
{
	if (rigidbody->IsGround())
	{
		skeletonSpear->SetCurrentJumpCount(skeletonSpear->GetJumpCount());

		fsm->ChangeState(SkeletonSpearStateType::Idle);
		return;
	}

	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left))
	{
		horizontal = -1.f;
	}
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
	{
		horizontal = 1.f;
	}
	if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::X))
		sequenceAttack = true;

	skeletonSpear->SetMoveDirection(horizontal);
}

void SkeletonSpearJumpAttackState::FixedUpdate(float fixedDeltaTime)
{
	rigidbody->SetVelocity({ horizontal * skeletonSpear->GetSpeed() * 0.5f , rigidbody->GetCurrentVelocity().y });
}

void SkeletonSpearJumpAttackState::OnStartAttack()
{
	Animation* animation = animator->GetCurrentAnimation();
	animation->Reset();
	animation->Play(1.f, false);
	animation->SetAnimationEndEvent(std::bind(&SkeletonSpearJumpAttackState::OnEndAttack, this), animation->GetFrameCount() - 1);
	animation->SetAnimationStartEvent(std::bind(&SkeletonSpearJumpAttackState::OnCreateHitBox, this), 1);
	animation->SetAnimationEndEvent(std::bind(&SkeletonSpearJumpAttackState::OnDestoryHitBox, this), 1);

	sequenceAttack = false;
}

void SkeletonSpearJumpAttackState::OnEndAttack()
{
	if (!rigidbody->IsGround())
	{
		if (sequenceAttack)
		{
			animator->GetCurrentAnimation()->ClearEndEvent(animator->GetCurrentAnimation()->GetFrameCount() - 1);
			OnStartAttack();
		}
		else
			fsm->ChangeState(SkeletonSpearStateType::Falling);
	}
	else
	{
		fsm->ChangeState(SkeletonSpearStateType::Idle);
		skeletonSpear->SetCurrentJumpCount(skeletonSpear->GetJumpCount());
	}
}


void SkeletonSpearJumpAttackState::OnCreateHitBox()
{
	attackBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(skeletonSpear, ColliderLayer::PlayerBullet, ColliderLayer::Boss, true, (sf::Vector2f::right * 30.f)), LayerType::PlayerBullet);
	attackBox->SetScale({ 50.f,50.f });

	attackBox->SetDamage(damageInfo);
	attackBox->AddStartHitEvent(std::bind(&SkeletonSpearJumpAttackState::CreateEffect, this, std::placeholders::_1));
}

void SkeletonSpearJumpAttackState::OnDestoryHitBox()
{
	attackBox->OnDestory();
	attackBox->SetActive(false);
	attackBox = nullptr;

	Animation* animation = animator->GetCurrentAnimation();
	animation->ClearStartEvent(1);
	animation->ClearEndEvent(1);
}

void SkeletonSpearJumpAttackState::ClearEvenet()
{
	Animation* animation = animator->GetAnimation(animationKeys[GetAnimationIndex()]);
	animation->ClearEndEvent(animation->GetFrameCount() - 1);
	animation->ClearStartEvent(1);
	animation->ClearEndEvent(1);
}

void SkeletonSpearJumpAttackState::CreateEffect(GameObject* object)
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
