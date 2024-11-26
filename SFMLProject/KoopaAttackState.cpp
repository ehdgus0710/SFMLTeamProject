#include "stdafx.h"
#include "KoopaAttackState.h"
#include "Rigidbody.h"
#include "Animation.h"
#include "Animator.h"
#include "KoopaFireBullet.h"

KoopaAttackState::KoopaAttackState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Attack)
	, rigidbody(nullptr)
	, createPosition(64.f, -32.f)
{
}

KoopaAttackState::~KoopaAttackState()
{
}


void KoopaAttackState::StartAttack()
{
	KoopaFireBullet* bullet = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new KoopaFireBullet(), LayerType::EnemyBullet);

	sf::Vector2f direciton;

	if (!enemy->IsFlipX())
	{
		direciton = sf::Vector2f::left;
		bullet->SetPosition(enemy->GetPosition() + (createPosition * sf::Vector2f::left));
	}
	else
	{
		direciton = sf::Vector2f::right;
		bullet->SetPosition(enemy->GetPosition() + (createPosition * sf::Vector2f::right));
	}

	direciton.Normalized();

	bullet->SetMoveDirection(direciton);

	bullet->Awake();
	bullet->Start();
}

void KoopaAttackState::EndAttack()
{
	fsm->ChangeState(EnemyStateType::Idle);
}

void KoopaAttackState::Awake()
{
}

void KoopaAttackState::Start()
{
}

void KoopaAttackState::Enter()
{
	enemy->GetAnimator()->ChangeAnimation("koopaAttack", true);

	Animation* animation = enemy->GetAnimator()->GetCurrentAnimation();
	animation->SetAnimationEndEvent(std::bind(&KoopaAttackState::StartAttack, this), 0);
	animation->SetAnimationEndEvent(std::bind(&KoopaAttackState::EndAttack, this), 1);
	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void KoopaAttackState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}

	Animation* animation = enemy->GetAnimator()->GetCurrentAnimation();
	animation->ClearEndEvent(0);
	animation->ClearEndEvent(1);
}

void KoopaAttackState::Update(float deltaTime)
{
}

void KoopaAttackState::FixedUpdate(float fixedDeltaTime)
{
}

void KoopaAttackState::LateUpdate(float deltaTime)
{
}