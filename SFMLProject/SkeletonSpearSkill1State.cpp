#include "stdafx.h"
#include "SkeletonSpearSkill1State.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "HitBoxObject.h"



SkeletonSpearSkill1State::SkeletonSpearSkill1State(SkeletonSpearFSM* fsm)
	: SkeletonSpearBaseState(fsm, SkeletonSpearStateType::Skill1)
	, isExtraDash(false)
	, dashTime(0.3f)
	, currentTime(0.f)
	, rigidbody(nullptr)
{
	animationKeys.push_back("spearPierce");
}

SkeletonSpearSkill1State::~SkeletonSpearSkill1State()
{
}

void SkeletonSpearSkill1State::StartDash()
{
	animator->ChangeAnimation(animationKeys[GetAnimationIndex()], false);
	dashEndPos = skeletonSpear->GetPosition() + (skeletonSpear->IsFlipX() ? sf::Vector2f::left : sf::Vector2f::right) * 600.f;
	dashStartPos = skeletonSpear->GetPosition();
	skeletonSpear->OnDash();
	currentTime = 0.f;
}

void SkeletonSpearSkill1State::OnCreateHitBox()
{
	attackBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(skeletonSpear, ColliderLayer::PlayerBullet, ColliderLayer::Boss, true, sf::Vector2f::right * 50.f), LayerType::PlayerBullet);
	attackBox->SetScale({ 150.f,150.f });
	attackBox->SetDamage(damageInfo);

	attackBox->AddStartHitEvent(std::bind(&SkeletonSpearSkill1State::CreateEffect, this, std::placeholders::_1));
	attackBox->Start();
}

void SkeletonSpearSkill1State::OnDestoryHitBox()
{
	attackBox->OnDestory();
	attackBox->SetActive(false);
	attackBox = nullptr;

	Animation* animation = animator->GetCurrentAnimation();
	animation->ClearStartEvent(1);
	animation->ClearEndEvent(1);
}

void SkeletonSpearSkill1State::CreateEffect(GameObject* object)
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

void SkeletonSpearSkill1State::Start()
{
	rigidbody = skeletonSpear->GetRigidbody();
}

void SkeletonSpearSkill1State::Enter()
{
	SkeletonSpearBaseState::Enter();
	OnCreateHitBox();
	rigidbody->ResetDropSpeed();
	rigidbody->ResetVelocity();
	rigidbody->Disable();
	isExtraDash = false;
	StartDash();
}

void SkeletonSpearSkill1State::Exit()
{
	OnDestoryHitBox();
	rigidbody->SetActive(true);
	SkeletonSpearBaseState::Exit();
}

void SkeletonSpearSkill1State::Update(float deltaTime)
{
	SkeletonSpearBaseState::Update(deltaTime);
	currentTime += deltaTime;
	skeletonSpear->SetPosition(sf::Vector2f::Lerp(dashStartPos, dashEndPos, currentTime / dashTime));

	if (currentTime >= dashTime + 0.1f)
	{
		if (isExtraDash && skeletonSpear->GetCurrentDashCount() > 0)
		{
			StartDash();
		}
		else
		{
			if (rigidbody->IsGround())
				fsm->ChangeState(SkeletonSpearStateType::Idle);
			else
				fsm->ChangeState(SkeletonSpearStateType::Falling);
		}
	}
}