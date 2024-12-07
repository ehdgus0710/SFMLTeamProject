#include "stdafx.h"
#include "AwakeReianaDimensionState.h"
#include "Player.h"
#include "Rigidbody.h"
#include "Dimension.h"
#include "Animator.h"
#include "AwakenDimention.h"

AwakeReianaDimensionState::AwakeReianaDimensionState(AwakeReianaFsm* fsm)
	:AwakeReianaBaseState(fsm, AwakeReianaStateType::Dimension)
{
}

AwakeReianaDimensionState::~AwakeReianaDimensionState()
{
}

void AwakeReianaDimensionState::CreateDimension()
{
	AwakenDimention* dimension = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AwakenDimention(), LayerType::EnemyBullet);
	dimension->SetActive(true);
	dimension->SetPosition(awakeReiana->GetPlayer()->GetPosition());
	dimension->SetRotation((float)Utils::RandomRange(1, 180));
	dimension->Awake();
	dimension->Start();
}

void AwakeReianaDimensionState::Awake()
{
	AwakeReianaBaseState::Awake();
}

void AwakeReianaDimensionState::Start()
{
	AwakeReianaBaseState::Start();
}

void AwakeReianaDimensionState::Enter()
{
	AwakeReianaBaseState::Enter();
	currentTime = 0.f;
	animator->ChangeAnimation("awakenDimensionPierceAttack", false);
	if (awakeReiana->GetPosition().x < awakeReiana->GetPlayer()->GetPosition().x && awakeReiana->IsFlipX())
	{
		awakeReiana->OnFlipX();
	}
	if (awakeReiana->GetPosition().x > awakeReiana->GetPlayer()->GetPosition().x && !awakeReiana->IsFlipX())
	{
		awakeReiana->OnFlipX();
	}
	CreateDimension();
}

void AwakeReianaDimensionState::Exit()
{
	AwakeReianaBaseState::Exit();
}

void AwakeReianaDimensionState::Update(float deltaTime)
{
	AwakeReianaBaseState::Update(deltaTime);
	currentTime += deltaTime;
	if (currentTime > time)
	{
		fsm->ChangeState(AwakeReianaStateType::Idle);
	}
}

void AwakeReianaDimensionState::FixedUpdate(float fixedDeltaTime)
{
	AwakeReianaBaseState::FixedUpdate(fixedDeltaTime);
}

void AwakeReianaDimensionState::LateUpdate(float deltaTime)
{
	AwakeReianaBaseState::LateUpdate(deltaTime);
}
