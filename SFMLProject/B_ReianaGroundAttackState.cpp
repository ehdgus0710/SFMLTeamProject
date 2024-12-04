#include "stdafx.h"
#include "B_ReianaGroundAttackState.h"
#include "Player.h"	
#include "Rigidbody.h"
#include "Animator.h"
#include "Animation.h"
#include "HitBoxObject.h"
#include "MeteorGroundSmoke.h"
#include "Collider.h"

B_ReianaGroundAttackState::B_ReianaGroundAttackState(B_ReianaFsm* fsm)
	: B_ReianaBaseState(fsm, B_ReianaStateType::GroundAttack)

{
}

B_ReianaGroundAttackState::~B_ReianaGroundAttackState()
{
}

void B_ReianaGroundAttackState::Attack(float deltaTime)
{
	if (!start)
	{
		MeteorGroundSmoke* meteorGroundSmoke = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new MeteorGroundSmoke(), LayerType::EnemyBullet);
		meteorGroundSmoke->SetScale({ 2.f,2.f });
		meteorGroundSmoke->Start();
		meteorGroundSmoke->SetPosition(B_Reiana->GetPosition());
		if (!meteorGroundSmoke->IsFlipX() && !B_Reiana->IsFlipX())
		{
			meteorGroundSmoke->OnFlipX();
		}
		if (meteorGroundSmoke->IsFlipX() && B_Reiana->IsFlipX())
		{
			meteorGroundSmoke->OnFlipX();
		}
		start = true;
	}
	currentAttackTime += deltaTime;
	endPosition = B_Reiana->GetPosition();
	startPosition = { 200.f ,B_Reiana->GetPosition().y };
	B_Reiana->SetPosition(startPosition);
	endPosition = B_Reiana->GetPosition() + sf::Vector2f::left * moveDistance;
	animator->ChangeAnimation("meteorAttack", false);
	B_Reiana->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentAttackTime / attackTime));

	if (currentAttackTime > attackTime)
	{
		OnDestoryHitBox();
		fsm->ChangeState(B_ReianaStateType::Idle);
	}
}

void B_ReianaGroundAttackState::Wait(float deltaTime)
{
	currentWaitTime += deltaTime;

	if (currentWaitTime >= waitTime)
	{
		OnCreateHitBox();
		action = true;
	}
}

void B_ReianaGroundAttackState::ChangeReady2Animation()
{
	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->GetCurrentAnimation()->ClearEndEvent(endFrame);

	animator->ChangeAnimation("meteorGround2Ready", false);
}

void B_ReianaGroundAttackState::Awake()
{
	B_ReianaBaseState::Awake();
}

void B_ReianaGroundAttackState::Start()
{
	B_ReianaBaseState::Start();
}

void B_ReianaGroundAttackState::Enter()
{
	B_ReianaBaseState::Enter();
	animator->ChangeAnimation("meteorGroundReady", false);

	int endFrame = (int)animator->GetCurrentAnimation()->GetFrameInfo().size() - 1;
	animator->GetCurrentAnimation()->SetAnimationEndEvent(std::bind(&B_ReianaGroundAttackState::ChangeReady2Animation, this), endFrame);

	if (B_Reiana->IsFlipX())
		B_Reiana->OnFlipX();

	start = false;
	currentAttackTime = 0.f;
	currentWaitTime = 0.f;
	action = false;

	startPosition = { 200.f ,B_Reiana->GetPosition().y };
	B_Reiana->SetPosition(startPosition);
}

void B_ReianaGroundAttackState::Exit()
{
	B_ReianaBaseState::Exit();
}

void B_ReianaGroundAttackState::Update(float deltaTime)
{
	B_ReianaBaseState::Update(deltaTime);

	if (!action)
		Wait(deltaTime);
	else
		Attack(deltaTime);
}

void B_ReianaGroundAttackState::FixedUpdate(float fixedDeltaTime)
{
	B_ReianaBaseState::FixedUpdate(fixedDeltaTime);
}

void B_ReianaGroundAttackState::LateUpdate(float deltaTime)
{
	B_ReianaBaseState::LateUpdate(deltaTime);
}

void B_ReianaGroundAttackState::OnCreateHitBox()
{
	hitBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(B_Reiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, true, sf::Vector2f::zero, "groundAttack"), LayerType::EnemyBullet);
	hitBox->GetCollider()->SetOffsetPosition({ 0.f,B_Reiana->GetPosition().y - 180 });
	hitBox->SetScale({ 150.f,50.f });
	hitBox->SetDamage(1000);
}

void B_ReianaGroundAttackState::OnDestoryHitBox()
{
	hitBox->OnDestory();
	hitBox->SetActive(false);
	hitBox = nullptr;
}
