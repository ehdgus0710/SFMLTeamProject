#include "stdafx.h"
#include "ReianaNomalAttackState.h"
#include "Player.h"	
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "Camera.h"
#include "MeteorGroundSmoke.h"
#include "HitBoxObject.h"
#include "Collider.h"

ReianaNomalAttackState::ReianaNomalAttackState(ReianaFsm* fsm)
	: ReianaBaseState(fsm, ReianaStateType::NomalAttack)
{
}

ReianaNomalAttackState::~ReianaNomalAttackState()
{
}

void ReianaNomalAttackState::Attack(float deltaTime)
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

void ReianaNomalAttackState::Wait(float deltaTime)
{
	currentDelay += deltaTime;
	if (rush3)
	{
		fsm->ChangeState(ReianaStateType::Idle);
	}
	if (!playerPosCheck)
	{
		startPosition = reiana->GetPosition();
		endPosition = { reiana->GetPlayer()->GetPosition().x ,reiana->GetPosition().y };
		playerPosCheck = true;
		MeteorGroundSmoke* meteorGroundSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new MeteorGroundSmoke(), LayerType::EnemyBullet);
		meteorGroundSmoke->SetScale({ 2.f,2.f });
		meteorGroundSmoke->Start();
		meteorGroundSmoke->SetPosition(reiana->GetPosition());
		if (reiana->GetPosition().x < reiana->GetPlayer()->GetPosition().x && reiana->IsFlipX())
		{
			reiana->OnFlipX();
		}
		if (reiana->GetPosition().x > reiana->GetPlayer()->GetPosition().x && !reiana->IsFlipX())
		{
			reiana->OnFlipX();
		}
		if (meteorGroundSmoke->IsFlipX() && !reiana->IsFlipX())
		{
			meteorGroundSmoke->OnFlipX();
		}
		if (!meteorGroundSmoke->IsFlipX() && reiana->IsFlipX())
		{
			meteorGroundSmoke->OnFlipX();
		}
	}
	if (!rush3)
	{
		reiana->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentDelay / delay));
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

void ReianaNomalAttackState::MoveSet()
{
}

void ReianaNomalAttackState::Awake()
{
	ReianaBaseState::Awake();
}

void ReianaNomalAttackState::Start()
{
	ReianaBaseState::Start();
}

void ReianaNomalAttackState::Enter()
{
	ReianaBaseState::Enter();

	endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	startPosition = reiana->GetPosition();
	endPosition = { reiana->GetPlayer()->GetPosition().x ,reiana->GetPosition().y };
	MeteorGroundSmoke* meteorGroundSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new MeteorGroundSmoke(), LayerType::EnemyBullet);
	meteorGroundSmoke->SetScale({ 1.f,1.f });
	meteorGroundSmoke->Start();
	meteorGroundSmoke->SetPosition(reiana->GetPosition());
	if (meteorGroundSmoke->IsFlipX() && !reiana->IsFlipX())
	{
		meteorGroundSmoke->OnFlipX();
	}
	if (!meteorGroundSmoke->IsFlipX() && reiana->IsFlipX())
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

void ReianaNomalAttackState::Exit()
{
	ReianaBaseState::Exit();
}

void ReianaNomalAttackState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);
	if (action)
	{
		Attack(deltaTime);
	}
	else
	{
		Wait(deltaTime);
	}
}

void ReianaNomalAttackState::FixedUpdate(float fixedDeltaTime)
{
}

void ReianaNomalAttackState::LateUpdate(float deltaTime)
{
}

void ReianaNomalAttackState::OnCreateHitBox()
{
	hitBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(reiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, true, sf::Vector2f::zero, "groundAttack"), LayerType::EnemyBullet);
	hitBox->GetCollider()->SetOffsetPosition({ 0.f,- 80.f });
	hitBox->SetScale({ 150.f,50.f });
	hitBox->SetDamage(10);
}

void ReianaNomalAttackState::OnDestoryHitBox()
{
	hitBox->OnDestory();
	hitBox->SetActive(false);
	hitBox = nullptr;
}
