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
			animator->ChangeAnimation("awakenRushC", false);
			rush3 = true;
			OnCreateHitBox();
			animationDelay = 2.f;
		}
		else if (rush1)
		{
			animator->ChangeAnimation("awakenRushB", false);
			rush2 = true;
			OnCreateHitBox();
		}
		else if (!rush1)
		{
			animator->ChangeAnimation("awakenRushA", false);
			rush1 = true;
			OnCreateHitBox();
		}
		move = false;
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
		playerPosCheck = true;
		MeteorGroundSmoke* meteorGroundSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new MeteorGroundSmoke(), LayerType::EnemyBullet);
		meteorGroundSmoke->SetScale({ 1.f,1.f });
		meteorGroundSmoke->Start();
		meteorGroundSmoke->SetPosition({ awakeReiana->GetPosition().x, awakeReiana->GetPosition().y });
		if (awakeReiana->GetPosition().x < awakeReiana->GetPlayer()->GetPosition().x && awakeReiana->IsFlipX())
		{
			awakeReiana->OnFlipX();
		}
		if (awakeReiana->GetPosition().x > awakeReiana->GetPlayer()->GetPosition().x && !awakeReiana->IsFlipX())
		{
			awakeReiana->OnFlipX();
		}
	}
	if (!rush3&&!move)
	{
		awakeReiana->SetPosition({ awakeReiana->GetPlayer()->GetPosition().x + rightPosition,awakeReiana->GetPosition().y});
		animator->ChangeAnimation("dash", false);
		move = true;
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
	MeteorGroundSmoke* meteorGroundSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new MeteorGroundSmoke(), LayerType::EnemyBullet);
	meteorGroundSmoke->SetPosition({ awakeReiana->GetPosition().x, awakeReiana->GetPosition().y});
	meteorGroundSmoke->Start();
	if (!meteorGroundSmoke->IsFlipX() && !awakeReiana->IsFlipX())
	{
		meteorGroundSmoke->OnFlipX();
	}
	if (meteorGroundSmoke->IsFlipX() && awakeReiana->IsFlipX())
	{
		meteorGroundSmoke->OnFlipX();
	}
	currentDelay = 0.f;
	currentAttackDelay = 0.f;
	currentAnimationDelay = 0.f;
	animationDelay = 0.5f;
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
	hitBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(awakeReiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, true, sf::Vector2f::zero, "groundAttack"), LayerType::EnemyBullet);
	hitBox->GetCollider()->SetOffsetPosition({ 0.f,awakeReiana->GetPosition().y - 180 });
	hitBox->SetScale({ 150.f,50.f });
	hitBox->SetDamage(1000);
}

void AwakeReianaAwakeDimensionState::OnDestoryHitBox()
{
	hitBox->OnDestory();
	hitBox->SetActive(false);
	hitBox = nullptr;
}
