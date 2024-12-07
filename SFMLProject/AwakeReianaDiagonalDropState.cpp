#include "stdafx.h"
#include "AwakeReianaDiagonalDropState.h"
#include "Player.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "HitBoxObject.h"
#include "IntroLandSmoke.h"

AwakeReianaDiagonalDropState::AwakeReianaDiagonalDropState(AwakeReianaFsm* fsm)
	:AwakeReianaBaseState(fsm, AwakeReianaStateType::DropAttack)
{
}

AwakeReianaDiagonalDropState::~AwakeReianaDiagonalDropState()
{
}

void AwakeReianaDiagonalDropState::Wait(float deltaTime)
{
	currentWaitTime += deltaTime;
	awakeReiana->SetPosition(awakeReiana->GetPosition());
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

void AwakeReianaDiagonalDropState::Drop(float deltaTime)
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
			introLandSmoke->SetPosition(awakeReiana->GetPosition());
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

void AwakeReianaDiagonalDropState::Awake()
{
	AwakeReianaBaseState::Awake();
}

void AwakeReianaDiagonalDropState::Start()
{
	AwakeReianaBaseState::Start();
}

void AwakeReianaDiagonalDropState::Enter()
{
	AwakeReianaBaseState::Enter();
	rigidbody = awakeReiana->GetRigidbody();
	animator->ChangeAnimation("awakenGoldMeteorJump", true);

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

	//moveDirection = awakeReiana->GetPlayer()->GetPosition() - awakeReiana->GetPosition();
	//moveDirection.Normalized();
	//awakeReiana->SetRotation(Utils::Angle(moveDirection));

	awakeReiana->SetPosition(startPosition);
	rigidbody->SetActive(false);
}

void AwakeReianaDiagonalDropState::Exit()
{
	AwakeReianaBaseState::Exit();
	rigidbody->SetActive(true);
	if (hitBox != nullptr)
	{
		OnDestoryHitBox();
	}
}

void AwakeReianaDiagonalDropState::Update(float deltaTime)
{
	AwakeReianaBaseState::Update(deltaTime);

	if (!action)
		Wait(deltaTime);
	else
	{
		Drop(deltaTime);
	}
}

void AwakeReianaDiagonalDropState::FixedUpdate(float fixedDeltaTime)
{
	AwakeReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void AwakeReianaDiagonalDropState::LateUpdate(float deltaTime)
{
	AwakeReianaBaseState::LateUpdate(deltaTime);

}

void AwakeReianaDiagonalDropState::OnCreateHitBox()
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

void AwakeReianaDiagonalDropState::OnDestoryHitBox()
{
	hitBox->OnDestory();
	hitBox->SetActive(false);
	hitBox = nullptr;
}


