#include "stdafx.h"
#include "ReianaGroundAttackState.h"
#include "Player.h"	
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "HitBoxObject.h"
#include "MeteorGroundSmoke.h"
#include "Collider.h"
#include "AwakeGroundDimention.h"

ReianaGroundAttackState::ReianaGroundAttackState(ReianaFsm* fsm)
	: ReianaBaseState(fsm, ReianaStateType::GroundAttack)

{
}

ReianaGroundAttackState::~ReianaGroundAttackState()
{
}

void ReianaGroundAttackState::Attack(float deltaTime)
{
	if (!start)
	{
		MeteorGroundSmoke* meteorGroundSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new MeteorGroundSmoke(), LayerType::EnemyBullet);
		meteorGroundSmoke->SetScale({ 3.f,3.f });
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
		
		start = true;
	}
	currentAttackTime += deltaTime;
	endPosition = reiana->GetPosition();
	startPosition = { 1700.f ,reiana->GetPosition().y };
	reiana->SetPosition(startPosition);
	endPosition = reiana->GetPosition() + sf::Vector2f::left * moveDistance;
	animator->ChangeAnimation("meteorAttack", false);
	reiana->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentAttackTime / attackTime*2));

	if (currentAttackTime > attackTime)
	{
		OnDestoryHitBox();
		fsm->ChangeState(ReianaStateType::Idle);
	}
} 

void ReianaGroundAttackState::Wait(float deltaTime)
{
	currentWaitTime += deltaTime;

	if (currentWaitTime >= waitTime)
	{
		OnCreateHitBox();
		action = true;
	}
}

void ReianaGroundAttackState::ChangeReady2Animation()
{
	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->GetCurrentAnimation()->ClearEndEvent(endFrame);

	animator->ChangeAnimation("meteorGround2Ready", false);
}

void ReianaGroundAttackState::Awake()
{
	ReianaBaseState::Awake();
}

void ReianaGroundAttackState::Start()
{
	ReianaBaseState::Start();
}

void ReianaGroundAttackState::Enter()
{
	ReianaBaseState::Enter();
	animator->ChangeAnimation("meteorGroundReady", false);

	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&ReianaGroundAttackState::ChangeReady2Animation, this), endFrame);

	if(!reiana->IsFlipX())
		reiana->OnFlipX();

	start = false;
	currentAttackTime = 0.f;
	currentWaitTime = 0.f;
	action = false;

	startPosition = { 1700.f ,reiana->GetPosition().y };
	reiana->SetPosition(startPosition);	
}

void ReianaGroundAttackState::Exit()
{
	ReianaBaseState::Exit();
}

void ReianaGroundAttackState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);
	
	if (!action)
		Wait(deltaTime);
	else
		Attack(deltaTime);
}

void ReianaGroundAttackState::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);
}

void ReianaGroundAttackState::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);
}

void ReianaGroundAttackState::OnCreateHitBox()
{
	hitBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(reiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, true), LayerType::EnemyBullet);
	hitBox->SetScale({ 150.f,50.f });
	hitBox->GetCollider()->SetOffsetPosition({ 0,-80.f });

	DamegeInfo damageInfo;
	damageInfo.damege = 10.f;
	damageInfo.useKnockback = true;
	damageInfo.knockbackDuration = 0.2f;
	damageInfo.owner = reiana;
	damageInfo.knockbackVelocity = { 50.f,0.f };
	damageInfo.hitDirection = (reiana->IsFlipX() ? sf::Vector2f::left : sf::Vector2f::Vector2::right);
	hitBox->SetDamage(damageInfo);
}

void ReianaGroundAttackState::OnDestoryHitBox()
{
	hitBox->OnDestory();
	hitBox->SetActive(false);
	hitBox = nullptr;
}

