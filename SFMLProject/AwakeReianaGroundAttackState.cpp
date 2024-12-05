#include "stdafx.h"
#include "AwakeReianaGroundAttackState.h"
#include "Player.h"	
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "HitBoxObject.h"
#include "MeteorGroundSmoke.h"
#include "Collider.h"
#include "AwakeGroundDimention.h"

AwakeReianaGroundAttackState::AwakeReianaGroundAttackState(AwakeReianaFsm* fsm)
	: AwakeReianaBaseState(fsm, AwakeReianaStateType::GroundAttack)

{
}

AwakeReianaGroundAttackState::~AwakeReianaGroundAttackState()
{
}

void AwakeReianaGroundAttackState::Attack(float deltaTime)
{
	if (!start)
	{
		animator->ChangeAnimation("awakenMeteorAttack", false);
		MeteorGroundSmoke* meteorGroundSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new MeteorGroundSmoke(), LayerType::EnemyBullet);
		meteorGroundSmoke->SetScale({ 2.f,2.f });
		meteorGroundSmoke->Start();
		meteorGroundSmoke->SetPosition(awakeReiana->GetPosition());
		if (meteorGroundSmoke->IsFlipX() && !awakeReiana->IsFlipX())
		{
			meteorGroundSmoke->OnFlipX();
		}
		if (!meteorGroundSmoke->IsFlipX() && awakeReiana->IsFlipX())
		{
			meteorGroundSmoke->OnFlipX();
		}
		start = true;
	}
	currentAttackTime += deltaTime;
	endPosition = awakeReiana->GetPosition();
	startPosition = { 1700.f ,awakeReiana->GetPosition().y };
	awakeReiana->SetPosition(startPosition);
	endPosition = awakeReiana->GetPosition() + sf::Vector2f::left * moveDistance;
	awakeReiana->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentAttackTime / attackTime*5));
	AwakeGroundDimention* awakeGroundDimention = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AwakeGroundDimention("GroundDimension"), LayerType::EnemyBullet);
	awakeGroundDimention->SetPosition(awakeReiana->GetPosition());
	awakeGroundDimention->Start();
	if (currentAttackTime > endTime)
	{
		awakeReiana->OnFlipX();
		animator->ChangeAnimation("awakenMeteorGroundEnd", false);
		endTime = 10.f;
	}
	if (currentAttackTime > attackTime)
	{
		OnDestoryHitBox();
		fsm->ChangeState(AwakeReianaStateType::Idle);
	}
}

void AwakeReianaGroundAttackState::Wait(float deltaTime)
{
	currentWaitTime += deltaTime;

	if (currentWaitTime >= waitTime)
	{
		OnCreateHitBox();
		action = true;
	}
}

void AwakeReianaGroundAttackState::ChangeReady2Animation()
{
	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->GetCurrentAnimation()->ClearEndEvent(endFrame);

	animator->ChangeAnimation("awakenMeteorGround2Ready", false);
}

void AwakeReianaGroundAttackState::Awake()
{
	AwakeReianaBaseState::Awake();
}

void AwakeReianaGroundAttackState::Start()
{
	AwakeReianaBaseState::Start();
}

void AwakeReianaGroundAttackState::Enter()
{
	AwakeReianaBaseState::Enter();
	animator->ChangeAnimation("awakenMeteorGroundReady", false);

	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&AwakeReianaGroundAttackState::ChangeReady2Animation, this), endFrame);

	if (!awakeReiana->IsFlipX())
		awakeReiana->OnFlipX();

	start = false;
	currentAttackTime = 0.f;
	currentWaitTime = 0.f;
	endTime = 1.f;
	action = false;

	startPosition = { 1700.f ,awakeReiana->GetPosition().y };
	awakeReiana->SetPosition(startPosition);
}

void AwakeReianaGroundAttackState::Exit()
{
	AwakeReianaBaseState::Exit();
}

void AwakeReianaGroundAttackState::Update(float deltaTime)
{
	AwakeReianaBaseState::Update(deltaTime);

	if (!action)
		Wait(deltaTime);
	else
		Attack(deltaTime);
}

void AwakeReianaGroundAttackState::FixedUpdate(float fixedDeltaTime)
{
	AwakeReianaBaseState::FixedUpdate(fixedDeltaTime);
}

void AwakeReianaGroundAttackState::LateUpdate(float deltaTime)
{
	AwakeReianaBaseState::LateUpdate(deltaTime);
}

void AwakeReianaGroundAttackState::OnCreateHitBox()
{
	hitBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(awakeReiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, true), LayerType::EnemyBullet);
	hitBox->GetCollider()->SetOffsetPosition({ 0.f,awakeReiana->GetPosition().y - 180 });
	hitBox->SetScale({ 100.f,50.f });
	DamegeInfo damageInfo;
	damageInfo.damege = 10.f;
	damageInfo.useKnockback = true;
	damageInfo.knockbackDuration = 0.2f;
	damageInfo.owner = awakeReiana;
	damageInfo.knockbackVelocity = { 50.f,0.f };
	damageInfo.hitDirection = (awakeReiana->IsFlipX() ? sf::Vector2f::left : sf::Vector2f::Vector2::right);
	hitBox->SetDamage(damageInfo);
}
void AwakeReianaGroundAttackState::OnDestoryHitBox()
{
	hitBox->OnDestory();
	hitBox->SetActive(false);
	hitBox = nullptr;
}

