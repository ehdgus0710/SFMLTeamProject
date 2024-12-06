#include "stdafx.h"
#include "AwakeReianaDropAttackState.h"
#include "Player.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "HitBoxObject.h"
#include "IntroLandSmoke.h"
#include "AwakenDropEnd.h"
#include "AwakenDropStart.h"
#include "AwakenDropSide.h"

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
	awakeReiana->SetPosition(awakeReiana->GetPosition());
	if (currentWaitTime >= waitTime)
	{
		AwakenDropStart* awakenDropStart = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AwakenDropStart(), LayerType::BackGround_Forward);
		awakenDropStart->Start();
		awakenDropStart->SetPosition({ awakeReiana->GetPosition().x,awakeReiana->GetPosition().y + 900 });
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

	awakeReiana->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentDropTime / dropTime));
	if (currentDropTime > dropTime)
	{
		animator->ChangeAnimation("awakenGoldMeteorLanding", false);
		currentLandingTime += deltaTime;
		if (!effect)
		{
			IntroLandSmoke* introLandSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new IntroLandSmoke(), LayerType::EnemyBullet);
			introLandSmoke->SetScale({ 2.f,2.f });
			introLandSmoke->Start();
			introLandSmoke->SetPosition({ awakeReiana->GetPosition().x,awakeReiana->GetPosition().y });
			
			awakenDropSide1 = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AwakenDropSide(), LayerType::EnemyBullet);
			awakenDropSide2 = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AwakenDropSide(), LayerType::EnemyBullet);
			awakenDropSide1->SetPosition({ awakeReiana->GetPosition().x,awakeReiana->GetPosition().y + 60 });
			awakenDropSide2->SetPosition({ awakeReiana->GetPosition().x,awakeReiana->GetPosition().y + 60});
			awakenDropSide2->OnFlipX();
			AwakenDropEnd* awakenDropEnd = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AwakenDropEnd(), LayerType::EnemyBullet);
			awakenDropEnd->Start();
			awakenDropEnd->SetPosition({ awakeReiana->GetPosition().x,awakeReiana->GetPosition().y + 30 });
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
	rigidbody = awakeReiana->GetRigidbody();
	animator->ChangeAnimation("awakenGoldMeteorJump",true);

	currentDropTime = 0.f;
	currentWaitTime = 0.f;
	currentLandingTime = 0.f;
	action = false;
	effect = false;
	attack = false;
	waitAnimation = false;
	auto playerPos = awakeReiana->GetPlayer()->GetPosition();
	endPosition = { playerPos.x, 80.f };

	playerPos -= waitStartPos;
	startPosition = playerPos;

	playerPos = awakeReiana->GetPlayer()->GetPosition();

	

	awakeReiana->SetPosition(startPosition);
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
	if (awakenDropSide1 != nullptr)
	{
		awakenDropSide1->Move(deltaTime,awakeReiana->GetPosition());
	}
	if (awakenDropSide2 != nullptr)
	{
		awakenDropSide2->Move2(deltaTime,awakeReiana->GetPosition());
	}
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
	hitBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(awakeReiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, true), LayerType::EnemyBullet);
	hitBox->SetScale({ 50.f,100.f });

	DamegeInfo damageInfo;
	damageInfo.damege = 10.f;
	damageInfo.useKnockback = true;
	damageInfo.knockbackDuration = 0.5f;
	damageInfo.owner = awakeReiana;
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


