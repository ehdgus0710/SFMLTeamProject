#include "stdafx.h"
#include "KoopaTroopaDeadState.h"

#include "Animator.h"
#include "Collider.h"
#include "Rigidbody.h"

#include "InGameScoreUI.h"
#include "GameManager.h"

KoopaTroopaDeadState::KoopaTroopaDeadState(EnemyFSM* fsm)
	: EnemyBaseState(fsm, EnemyStateType::Dead)
	, rotationTime(0.3f)
	, currentRotationTime(0.f)
	, currentTime(0.f)
	, isJumpDie(false)
	, isEndRotation(false)
	, jumpDeadTime(0.3f)
	, rigidbody(nullptr)
{
}

KoopaTroopaDeadState::~KoopaTroopaDeadState()
{
}

void KoopaTroopaDeadState::Awake()
{
}

void KoopaTroopaDeadState::Start()
{
	rigidbody = enemy->GetRigidbody();
}

void KoopaTroopaDeadState::Enter()
{
	enemy->SetCurrentState(stateType);

	rigidbody->ResetVelocity();
	rigidbody->SetGround(false);
	enemy->GetCollider()->SetActive(false);


	enemy->GetAnimator()->ChangeAnimation("koopaTroopaMove", true);

	hitDirection = enemy->GetHitDirection();
	currentRotationTime = 0.f;
	rigidbody->SetVelocity({ hitDirection.x * 300.f, -450.f });

	SoundManger::GetInstance().PlaySfx("Chop");

	GameManager::GetInstance().AddScore(100);
	InGameScoreUI* inGameScoreUI = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new InGameScoreUI("DungGeunMo", "CoinScoreUI", 30), LayerType::InGameUI);
	inGameScoreUI->SetString("200");
	inGameScoreUI->SetPosition(enemy->GetPosition() + sf::Vector2f::up * 20.f);
	inGameScoreUI->Start();


	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}

}

void KoopaTroopaDeadState::IsHitDie(float deltaTime)
{
	if (!isEndRotation)
	{
		currentRotationTime += deltaTime;
		float rotation = enemy->GetRotation();

		rotation = Utils::Lerp(rotation, 180.f, currentRotationTime / rotationTime);
		enemy->SetRotation(rotation);

		if (currentRotationTime >= rotationTime)
		{
			isEndRotation = true;
			rigidbody->SetVelocity({ hitDirection.x * 200.f , rigidbody->GetCurrentVelocity().y });
		}
	}

	if (enemy->GetPosition().y >= 2000.f)
		enemy->OnDestory();
}

void KoopaTroopaDeadState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}

void KoopaTroopaDeadState::Update(float deltaTime)
{
	IsHitDie(deltaTime);
}

void KoopaTroopaDeadState::FixedUpdate(float fixedDeltaTime)
{
}

void KoopaTroopaDeadState::LateUpdate(float deltaTime)
{
}