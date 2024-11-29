#include "stdafx.h"
#include "ReianaAroundDimensionState.h"
#include "AroundDimention.h"

ReianaAroundDimensionState::ReianaAroundDimensionState(ReianaFsm* fsm)
	: ReianaBaseState(fsm, ReianaStateType::Aruond)
	, delay(0.25f)
	, currentDelay(0.f)
	, count(1.f)

{
}

ReianaAroundDimensionState::~ReianaAroundDimensionState()
{
}

void ReianaAroundDimensionState::CreateLeftDimension()
{
	AroundDimention* dimension = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AroundDimention(reiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, "MenuBar"), LayerType::EnemyBullet);
	auto dimensionPos = reiana->GetPosition();
	dimension->SetPosition(dimensionPos + (leftPos * count));
}

void ReianaAroundDimensionState::CreateRigthDimension()
{
	AroundDimention* dimension = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new AroundDimention(reiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, "MenuBar"), LayerType::EnemyBullet);
	auto dimensionPos = reiana->GetPosition();
	dimension->SetPosition(dimensionPos + (rigthPos * count));
}

void ReianaAroundDimensionState::Awake()
{
}

void ReianaAroundDimensionState::Start()
{
}

void ReianaAroundDimensionState::Enter()
{
	delay = 0.25f;
	currentDelay = 0.f;
	count = 1.f;
}

void ReianaAroundDimensionState::Exit()
{
}

void ReianaAroundDimensionState::Update(float deltaTime)
{
	currentDelay += deltaTime;

	if (delay < currentDelay)
	{
		currentDelay = 0.f;
		CreateLeftDimension();
		CreateRigthDimension();

		if (count >= 9)
		{
			fsm->ChangeState(ReianaStateType::Idle);
		}
	}
}

void ReianaAroundDimensionState::FixedUpdate(float fixedDeltaTime)
{
}

void ReianaAroundDimensionState::LateUpdate(float deltaTime)
{
}
