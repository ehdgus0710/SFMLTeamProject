#include "stdafx.h"
#include "ReianaDropAttackState.h"
#include "Player.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "HitBoxObject.h"
#include "IntroLandSmoke.h"

ReianaDropAttackState::ReianaDropAttackState(ReianaFsm* fsm)
	:ReianaBaseState(fsm, ReianaStateType::DropAttack)
{
}

ReianaDropAttackState::~ReianaDropAttackState()
{
}

void ReianaDropAttackState::Wait(float deltaTime)
{
	currentWaitTime += deltaTime;

	if (currentWaitTime >= waitTime)
	{
		action = true;
		OnCreateHitBox();
	}
}

void ReianaDropAttackState::Drop(float deltaTime)
{
	currentDropTime += deltaTime;

	reiana->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentDropTime / dropTime));
	if (currentDropTime > dropTime)
	{
		animator->ChangeAnimation("goldmetorLanding", false);
		currentLandingTime += deltaTime;
		if (!effect)
		{
			IntroLandSmoke* introLandSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new IntroLandSmoke(), LayerType::EnemyBullet);
			introLandSmoke->SetScale({ 2.f,2.f });
			introLandSmoke->Start();
			introLandSmoke->SetPosition(reiana->GetPosition());
			effect = true;
		}
		if (currentLandingTime >= landingTime)
		{
			OnDestoryHitBox();
			fsm->ChangeState(ReianaStateType::Idle);
		}
	}
	
}

void ReianaDropAttackState::Awake()
{
	ReianaBaseState::Awake();
}

void ReianaDropAttackState::Start()
{
	ReianaBaseState::Start();
}

void ReianaDropAttackState::Enter()
{
	ReianaBaseState::Enter();
	rigidbody = reiana->GetRigidbody();
	animator->ChangeAnimation("goldMeteorAttack", true);

	currentDropTime = 0.f;
	currentWaitTime = 0.f;
	currentLandingTime = 0.f;
	action = false; 
	effect = false;
	auto playerPos = reiana->GetPlayer()->GetPosition();
	endPosition = { playerPos.x, 900.f };

	playerPos -= moveDistance;
	startPosition = playerPos;

	playerPos = reiana->GetPlayer()->GetPosition();
	
	

	reiana->SetPosition(startPosition);
	rigidbody->SetActive(false);
}

void ReianaDropAttackState::Exit()
{
	ReianaBaseState::Exit();
	rigidbody->SetActive(true);
}

void ReianaDropAttackState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);

	if (!action)
		Wait(deltaTime);
	else
	{
		Drop(deltaTime);
	}
}

void ReianaDropAttackState::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void ReianaDropAttackState::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);

}

void ReianaDropAttackState::OnCreateHitBox()
{
	hitBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(reiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, true), LayerType::EnemyBullet);
	hitBox->SetScale({ 50.f,100.f });

	DamegeInfo damageInfo;
	damageInfo.damege = 10.f;
	damageInfo.useKnockback = true;
	damageInfo.knockbackDuration = 0.5f;
	damageInfo.owner = reiana;
	damageInfo.knockbackVelocity = { 100.f,0.f };
	damageInfo.hitDirection = sf::Vector2f::down;
	hitBox->SetDamage(damageInfo);
}

void ReianaDropAttackState::OnDestoryHitBox()
{
	hitBox->OnDestory();
	hitBox->SetActive(false);
	hitBox = nullptr;
}


