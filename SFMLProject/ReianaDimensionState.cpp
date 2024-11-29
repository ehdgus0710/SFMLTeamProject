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
	Dimension* dimension = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new Dimension(ColliderLayer::EnemyBullet,"MenuBar"), LayerType::EnemyBullet);
	dimension->SetActive(true);
	dimension->SetPosition(reiana->GetPlayer()->GetPosition());
	dimension->Awake();
	dimension->Start();
	dimension->SetRotation((float)Utils::RandomRange(1,180));
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
	animator->ChangeAnimation("dimensionPierceAttack", false);
	CreateDimension();
}

void ReianaDimensionState::Exit()
{
	ReianaBaseState::Exit();
}

void ReianaDimensionState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);
}

void ReianaDimensionState::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);
}

void ReianaDimensionState::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);
}