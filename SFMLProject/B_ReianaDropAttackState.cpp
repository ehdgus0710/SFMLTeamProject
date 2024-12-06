#include "stdafx.h"
#include "B_ReianaDropAttackState.h"
#include "Player.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "HitBoxObject.h"
#include "IntroLandSmoke.h"

B_ReianaDropAttackState::B_ReianaDropAttackState(B_ReianaFsm* fsm)
	:B_ReianaBaseState(fsm, B_ReianaStateType::DropAttack)
{
}

B_ReianaDropAttackState::~B_ReianaDropAttackState()
{
}

void B_ReianaDropAttackState::Wait(float deltaTime)
{
	currentWaitTime += deltaTime;

	if (currentWaitTime >= waitTime)
	{
		action = true;
		OnCreateHitBox();
	}
}

void B_ReianaDropAttackState::Drop(float deltaTime)
{
	currentDropTime += deltaTime;

	b_reiana->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentDropTime / dropTime));
	if (currentDropTime > dropTime)
	{
		animator->ChangeAnimation("goldmetorLanding", false);
		currentLandingTime += deltaTime;
		if (!effect)
		{
			IntroLandSmoke* introLandSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new IntroLandSmoke(), LayerType::EnemyBullet);
			introLandSmoke->SetScale({ 2.f,2.f });
			introLandSmoke->Start();
			introLandSmoke->SetPosition(b_reiana->GetPosition());
			effect = true;
		}
		if (currentLandingTime >= landingTime)
		{
			OnDestoryHitBox();
			fsm->ChangeState(B_ReianaStateType::Idle);
		}
	}

}

void B_ReianaDropAttackState::Awake()
{
	B_ReianaBaseState::Awake();
}

void B_ReianaDropAttackState::Start()
{
	B_ReianaBaseState::Start();
}

void B_ReianaDropAttackState::Enter()
{
	B_ReianaBaseState::Enter();
	rigidbody = b_reiana->GetRigidbody();
	animator->ChangeAnimation("goldMeteorAttack", true);

	currentDropTime = 0.f;
	currentWaitTime = 0.f;
	currentLandingTime = 0.f;
	action = false;
	effect = false;
	auto playerPos = b_reiana->GetPlayer()->GetPosition();
	endPosition = { playerPos.x, 900.f };

	playerPos -= moveDistance;
	startPosition = playerPos;

	playerPos = b_reiana->GetPlayer()->GetPosition();



	b_reiana->SetPosition(startPosition);
	rigidbody->SetActive(false);
}

void B_ReianaDropAttackState::Exit()
{
	B_ReianaBaseState::Exit();
	rigidbody->SetActive(true);
}

void B_ReianaDropAttackState::Update(float deltaTime)
{
	B_ReianaBaseState::Update(deltaTime);

	if (!action)
		Wait(deltaTime);
	else
	{
		Drop(deltaTime);
	}
}

void B_ReianaDropAttackState::FixedUpdate(float fixedDeltaTime)
{
	B_ReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void B_ReianaDropAttackState::LateUpdate(float deltaTime)
{
	B_ReianaBaseState::LateUpdate(deltaTime);

}

void B_ReianaDropAttackState::OnCreateHitBox()
{
	hitBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(b_reiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, true), LayerType::EnemyBullet);
	hitBox->SetScale({ 50.f,100.f });
	hitBox->SetDamage(1000);
}

void B_ReianaDropAttackState::OnDestoryHitBox()
{
	hitBox->OnDestory();
	hitBox->SetActive(false);
	hitBox = nullptr;
}


