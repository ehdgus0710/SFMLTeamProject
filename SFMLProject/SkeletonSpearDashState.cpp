#include "stdafx.h"
#include "SkeletonSpearDashState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "HitBoxObject.h"


SkeletonSpearDashState::SkeletonSpearDashState(SkeletonSpearFSM* fsm)
	: SkeletonSpearBaseState(fsm, SkeletonSpearStateType::Dash)
	, isExtraDash(false)
	, dashTime(0.3f)
	, currentTime(0.f)
	, rigidbody(nullptr)
{
	animationKeys.push_back("spearDash");

	damageInfo.damege = 20.f;
	damageInfo.useKnockback = true;
	damageInfo.knockbackDuration = 0.2f;
	damageInfo.owner = skeletonSpear;
	damageInfo.knockbackVelocity = { 30.f,0.f };
	damageInfo.hitDirection = sf::Vector2f::down;
}

SkeletonSpearDashState::~SkeletonSpearDashState()
{
}

void SkeletonSpearDashState::StartDash()
{
	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], false);
	dashEndPos = skeletonSpear->GetPosition() + (skeletonSpear->IsFlipX() ? sf::Vector2f::left : sf::Vector2f::right) * 400.f;
	dashStartPos = skeletonSpear->GetPosition();
	skeletonSpear->OnDash();
	currentTime = 0.f;
}

void SkeletonSpearDashState::OnCreateHitBox()
{
	attackBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(skeletonSpear, ColliderLayer::PlayerBullet, ColliderLayer::Boss, true, sf::Vector2f::right * 50.f), LayerType::PlayerBullet);
	attackBox->SetScale({ 150.f,150.f });
	attackBox->SetDamage(damageInfo);

	attackBox->AddStartHitEvent(std::bind(&SkeletonSpearDashState::CreateEffect, this, std::placeholders::_1));
	attackBox->Start();
}

void SkeletonSpearDashState::OnDestoryHitBox()
{
	attackBox->OnDestory();
	attackBox->SetActive(false);
	attackBox = nullptr;

	Animation* animation = animator->GetCurrentAnimation();
	animation->ClearStartEvent(1);
	animation->ClearEndEvent(1);
}

void SkeletonSpearDashState::CreateEffect(GameObject* object)
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

void SkeletonSpearDashState::Start()
{
	rigidbody = skeletonSpear->GetRigidbody();
}

void SkeletonSpearDashState::Enter()
{
	SkeletonSpearBaseState::Enter();
	OnCreateHitBox();
	rigidbody->ResetDropSpeed();
	rigidbody->ResetVelocity();
	rigidbody->Disable();
	isExtraDash = false;
	StartDash();
}

void SkeletonSpearDashState::Exit()
{
	OnDestoryHitBox();
	rigidbody->SetActive(true);
	SkeletonSpearBaseState::Exit();
}

void SkeletonSpearDashState::Update(float deltaTime)
{
	SkeletonSpearBaseState::Update(deltaTime);
	currentTime += deltaTime;
	skeletonSpear->SetPosition(sf::Vector2f::Lerp(dashStartPos, dashEndPos, currentTime / dashTime));

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Z))
	{
		isExtraDash = true;
	}

	if (currentTime >= dashTime + 0.1f)
	{
		if (isExtraDash && skeletonSpear->GetCurrentDashCount() > 0)
		{
			StartDash();
		}
		else
		{
			if (rigidbody->IsGround())
			{
				fsm->ChangeState(SkeletonSpearStateType::Idle);
			}
			else
			{
				fsm->ChangeState(SkeletonSpearStateType::Falling);
			}
		}
	}

	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::C) && skeletonSpear->GetCurrentJumpCount() > 0)
	{
		skeletonSpear->SetCurrentJumpCount(skeletonSpear->GetCurrentJumpCount() - 1);
		fsm->ChangeState(SkeletonSpearStateType::Jump);
	}
}