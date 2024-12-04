#include "stdafx.h"
#include "AwakeReianaDropAttackState.h"
#include "Player.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "HitBoxObject.h"
#include "IntroLandSmoke.h"

AwakeReianaDropAttackState::AwakeReianaDropAttackState(AwakeReianaFsm* fsm)
	:AwakeReianaBaseState(fsm, AwakeReianaStateType::DropAttack)
{
}

AwakeReianaDropAttackState::~AwakeReianaDropAttackState()
{
}

void AwakeReianaDropAttackState::Wait(float deltaTime)
{
	currentWaitTime += deltaTime;
	AwakeReiana->SetPosition(AwakeReiana->GetPosition());
	if (currentWaitTime >= waitTime)
	{
		OnCreateHitBox();
		action = true;
	}
	else if (!waitAnimation)
	{
		waitAnimation = true;
		animator->ChangeAnimation("awakenGoldMeteorReady", false);
	}
}

void AwakeReianaDropAttackState::Drop(float deltaTime)
{
	currentDropTime += deltaTime;

	AwakeReiana->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentDropTime / dropTime));
	if (currentDropTime > dropTime)
	{
		animator->ChangeAnimation("awakenGoldMeteorLanding", false);
		currentLandingTime += deltaTime;
		if (!effect)
		{
			IntroLandSmoke* introLandSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new IntroLandSmoke(), LayerType::EnemyBullet);
			introLandSmoke->SetScale({ 2.f,2.f });
			introLandSmoke->Start();
			introLandSmoke->SetPosition(AwakeReiana->GetPosition());
			effect = true;
		}
		if (currentLandingTime >= landingTime)
		{
			OnDestoryHitBox();
			fsm->ChangeState(AwakeReianaStateType::Idle);
		}
	}
	else if (!attack)
	{
		attack = true;
		animator->ChangeAnimation("awakenGoldMeteorAttack", false);
	}
}

void AwakeReianaDropAttackState::Awake()
{
	AwakeReianaBaseState::Awake();
}

void AwakeReianaDropAttackState::Start()
{
	AwakeReianaBaseState::Start();
}

void AwakeReianaDropAttackState::Enter()
{
	AwakeReianaBaseState::Enter();
	rigidbody = AwakeReiana->GetRigidbody();
	animator->ChangeAnimation("awakenGoldMeteorJump",true);

	currentDropTime = 0.f;
	currentWaitTime = 0.f;
	currentLandingTime = 0.f;
	action = false;
	effect = false;
	attack = false;
	waitAnimation = false;
	auto playerPos = AwakeReiana->GetPlayer()->GetPosition();
	endPosition = { playerPos.x, 80.f };

	playerPos -= waitStartPos;
	startPosition = playerPos;

	playerPos = AwakeReiana->GetPlayer()->GetPosition();



	AwakeReiana->SetPosition(startPosition);
	rigidbody->SetActive(false);
}

void AwakeReianaDropAttackState::Exit()
{
	AwakeReianaBaseState::Exit();
	rigidbody->SetActive(true);
}

void AwakeReianaDropAttackState::Update(float deltaTime)
{
	AwakeReianaBaseState::Update(deltaTime);

	if (!action)
		Wait(deltaTime);
	else
	{
		Drop(deltaTime);
	}
}

void AwakeReianaDropAttackState::FixedUpdate(float fixedDeltaTime)
{
	AwakeReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void AwakeReianaDropAttackState::LateUpdate(float deltaTime)
{
	AwakeReianaBaseState::LateUpdate(deltaTime);

}

void AwakeReianaDropAttackState::OnCreateHitBox()
{
	hitBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(AwakeReiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, true), LayerType::EnemyBullet);
	hitBox->SetScale({ 50.f,100.f });

	DamegeInfo damageInfo;
	damageInfo.damege = 10.f;
	damageInfo.useKnockback = true;
	damageInfo.knockbackDuration = 0.5f;
	damageInfo.owner = AwakeReiana;
	damageInfo.knockbackVelocity = { 100.f,0.f };
	damageInfo.hitDirection = sf::Vector2f::down;
	hitBox->SetDamage(damageInfo);
}

void AwakeReianaDropAttackState::OnDestoryHitBox()
{
	hitBox->OnDestory();
	hitBox->SetActive(false);
	hitBox = nullptr;
}


