#include "stdafx.h"
#include "ReianaDimensionState.h"
#include "Player.h"
#include "Rigidbody.h"
#include "Dimension.h"
#include "Animator.h"

ReianaDimensionState::ReianaDimensionState(ReianaFsm* fsm)
	:ReianaBaseState(fsm,ReianaStateType::Dimension)
{
}

ReianaDimensionState::~ReianaDimensionState()
{
}

void ReianaDimensionState::CreateDimension()
{
	Dimension* dimension = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new Dimension(), LayerType::EnemyBullet);
	dimension->SetActive(true);
	dimension->SetPosition(reiana->GetPlayer()->GetPosition());
	dimension->SetRotation((float)Utils::RandomRange(1,180));
	dimension->Awake();
	dimension->Start();
}

void ReianaDimensionState::Awake()
{
	ReianaBaseState::Awake();
}

void ReianaDimensionState::Start()
{
	ReianaBaseState::Start();
}

void ReianaDimensionState::Enter()
{
	ReianaBaseState::Enter();	
	currentTime = 0.f;
	animator->ChangeAnimation("dimensionPierceAttack", false);
	if (reiana->GetPosition().x < reiana->GetPlayer()->GetPosition().x && reiana->IsFlipX())
	{
		reiana->OnFlipX();
	}
	if (reiana->GetPosition().x > reiana->GetPlayer()->GetPosition().x && !reiana->IsFlipX())
	{
		reiana->OnFlipX();
	}
	CreateDimension();
}

void ReianaDimensionState::Exit()
{
	ReianaBaseState::Exit();
}

void ReianaDimensionState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);
	currentTime += deltaTime;
	if (currentTime > time)
	{
		fsm->ChangeState(ReianaStateType::Idle);
	}
}

void ReianaDimensionState::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);
}

void ReianaDimensionState::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);
}
