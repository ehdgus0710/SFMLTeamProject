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
#include "AwakeDemensionWaitEffect.h"
#include "AwakenTeleport.h"

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
	if (rush2)
	{
		dimensionCreateCurrentTime += deltaTime;
		if (dimensionCreateCurrentTime >= dimensionCreateTime && dimensionCount <= 6)
		{
			AwakeDemensionWaitEffect* awakeDemensionWaitEffect = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AwakeDemensionWaitEffect(), LayerType::EnemyBullet);
			awakeDemensionWaitEffect->Start();
			dimensionList.push_back(awakeDemensionWaitEffect);
			dimensionCreateCurrentTime = 0.f;
			dimensionCreateTime = 0.3f;
			++dimensionCount;
		}
	}
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
			if(!rush3)
				OnDestoryHitBox();
		}
	}
	else if (currentAttackDelay >= attackDelay)
	{
		if (rush2)
		{
			animator->SetAnimationSpeed(1.2f);
			animator->ChangeAnimation("awakenRushC", false);
			rush3 = true;
			animationDelay = 4.f;
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
		for (auto dimension : dimensionList)
		{
			dimension->ChangeAttackAnimation();
		}
		fsm->ChangeState(AwakeReianaStateType::Idle);
	}
	if (!playerPosCheck)
	{
		AwakenTeleport* awakenTeleport = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AwakenTeleport(), LayerType::EnemyBullet);
		awakenTeleport->Start();
		awakenTeleport->SetPosition({ awakeReiana->GetPosition().x, awakeReiana->GetPosition().y });
		playerPosCheck = true;
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
		moveCurrentTime += deltaTime;
		awakeReiana->SetPosition({ -500.f,-1000 });
		if (moveTime < moveCurrentTime)
		{
			awakeReiana->SetPosition({ awakeReiana->GetPlayer()->GetPosition().x + rightPosition, 900 });
			animator->ChangeAnimation("dash", false);
			AwakenTeleport* awakenTeleport1 = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AwakenTeleport(), LayerType::EnemyBullet);
			awakenTeleport1->Start();
			awakenTeleport1->SetPosition({ awakeReiana->GetPosition().x, awakeReiana->GetPosition().y });
			move = true;
			moveCurrentTime = 0.f;
		}
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
	moveTime = 0.5f;
	moveCurrentTime = 0.f;
	dimensionCount = 0;
	currentDelay = 0.f;
	currentAttackDelay = 0.f;
	currentAnimationDelay = 0.f;
	animationDelay = 0.5f;
	dimensionCreateTime = 1.0f;
	dimensionCreateCurrentTime = 0.f;
	dimensionList.clear();
	animator->SetAnimationSpeed(1.0f);
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
	hitBox->GetCollider()->SetOffsetPosition({ 0.f,-80.f });
	hitBox->SetScale({ 150.f,50.f });
	hitBox->SetDamage(10);
}

void AwakeReianaAwakeDimensionState::OnDestoryHitBox()
{
	hitBox->OnDestory();
	hitBox->SetActive(false);
	hitBox = nullptr;
}
