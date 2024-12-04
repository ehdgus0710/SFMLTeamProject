#include "stdafx.h"
#include "AwakeReianaAwakeDimensionState.h"
#include "Player.h"	
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "Camera.h"
#include "MeteorGroundSmoke.h"
#include "HitBoxObject.h"
#include "Collider.h"

AwakeReianaAwakeDimensionState::AwakeReianaAwakeDimensionState(AwakeReianaFsm* fsm)
	: AwakeReianaBaseState(fsm, AwakeReianaStateType::AwakeDimension)
{
}

AwakeReianaAwakeDimensionState::~AwakeReianaAwakeDimensionState()
{
}

void AwakeReianaAwakeDimensionState::Attack(float deltaTime)
{
	currentAttackDelay += deltaTime;
	if (animation)
	{
		currentAnimationDelay += deltaTime;
		if (currentAnimationDelay > animationDelay)
		{
			currentDelay = 0.f;
			currentAnimationDelay = 0.f;
			currentAttackDelay = 0.f;
			action = false;
			animation = false;
			OnDestoryHitBox();
		}
	}
	else if (currentAttackDelay >= attackDelay)
	{
		if (rush2)
		{
			animator->ChangeAnimation("rushC", false);
			rush3 = true;
			OnCreateHitBox();
		}
		else if (rush1)
		{
			animator->ChangeAnimation("rushB", false);
			rush2 = true;
			OnCreateHitBox();
		}
		else if (!rush1)
		{
			animator->ChangeAnimation("rushA", false);
			rush1 = true;
			OnCreateHitBox();
		}
		animation = true;
	}
}

void AwakeReianaAwakeDimensionState::Wait(float deltaTime)
{
	currentDelay += deltaTime;
	if (rush3)
	{
		fsm->ChangeState(AwakeReianaStateType::Idle);
	}
	if (!playerPosCheck)
	{
		startPosition = AwakeReiana->GetPosition();
		endPosition = { AwakeReiana->GetPlayer()->GetPosition().x ,AwakeReiana->GetPosition().y };
		playerPosCheck = true;
		MeteorGroundSmoke* meteorGroundSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new MeteorGroundSmoke(), LayerType::EnemyBullet);
		meteorGroundSmoke->SetScale({ 1.f,1.f });
		meteorGroundSmoke->Start();
		meteorGroundSmoke->SetPosition(AwakeReiana->GetPosition());
		if (AwakeReiana->GetPosition().x < AwakeReiana->GetPlayer()->GetPosition().x && AwakeReiana->IsFlipX())
		{
			AwakeReiana->OnFlipX();
		}
		if (AwakeReiana->GetPosition().x > AwakeReiana->GetPlayer()->GetPosition().x && !AwakeReiana->IsFlipX())
		{
			AwakeReiana->OnFlipX();
		}
		if (!meteorGroundSmoke->IsFlipX() && !AwakeReiana->IsFlipX())
		{
			meteorGroundSmoke->OnFlipX();
		}
		if (meteorGroundSmoke->IsFlipX() && AwakeReiana->IsFlipX())
		{
			meteorGroundSmoke->OnFlipX();
		}
	}
	if (!rush3)
	{
		AwakeReiana->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentDelay / delay));
		animator->ChangeAnimation("dash", false);
	}

	if (currentDelay >= delay)
	{
		animator->ChangeAnimation("rushReady", false);
		action = true;
		if (!rush2)
		{
			playerPosCheck = false;
		}
	}

}

void AwakeReianaAwakeDimensionState::MoveSet()
{
}

void AwakeReianaAwakeDimensionState::Awake()
{
	AwakeReianaBaseState::Awake();
}

void AwakeReianaAwakeDimensionState::Start()
{
	AwakeReianaBaseState::Start();
}

void AwakeReianaAwakeDimensionState::Enter()
{
	AwakeReianaBaseState::Enter();

	endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	startPosition = AwakeReiana->GetPosition();
	endPosition = { AwakeReiana->GetPlayer()->GetPosition().x ,AwakeReiana->GetPosition().y };
	MeteorGroundSmoke* meteorGroundSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new MeteorGroundSmoke(), LayerType::EnemyBullet);
	meteorGroundSmoke->SetScale({ 1.f,1.f });
	meteorGroundSmoke->Start();
	meteorGroundSmoke->SetPosition(AwakeReiana->GetPosition());
	if (!meteorGroundSmoke->IsFlipX() && !AwakeReiana->IsFlipX())
	{
		meteorGroundSmoke->OnFlipX();
	}
	if (meteorGroundSmoke->IsFlipX() && AwakeReiana->IsFlipX())
	{
		meteorGroundSmoke->OnFlipX();
	}

	currentDelay = 0.f;
	currentAttackDelay = 0.f;
	currentAnimationDelay = 0.f;
	action = false;
	checkFilp = false;
	rush1 = false;
	rush2 = false;
	rush3 = false;
	playerPosCheck = true;
}

void AwakeReianaAwakeDimensionState::Exit()
{
	AwakeReianaBaseState::Exit();
}

void AwakeReianaAwakeDimensionState::Update(float deltaTime)
{
	AwakeReianaBaseState::Update(deltaTime);
	if (action)
	{
		Attack(deltaTime);
	}
	else
	{
		Wait(deltaTime);
	}
}

void AwakeReianaAwakeDimensionState::FixedUpdate(float fixedDeltaTime)
{
}

void AwakeReianaAwakeDimensionState::LateUpdate(float deltaTime)
{
}

void AwakeReianaAwakeDimensionState::OnCreateHitBox()
{
	hitBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(AwakeReiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, true, sf::Vector2f::zero, "groundAttack"), LayerType::EnemyBullet);
	hitBox->GetCollider()->SetOffsetPosition({ 0.f,AwakeReiana->GetPosition().y - 180 });
	hitBox->SetScale({ 150.f,50.f });
	hitBox->SetDamage(1000);
}

void AwakeReianaAwakeDimensionState::OnDestoryHitBox()
{
	hitBox->OnDestory();
	hitBox->SetActive(false);
	hitBox = nullptr;
}
