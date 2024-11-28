#include "stdafx.h"
#include "ReianaDimensionState.h"
#include "Player.h"
#include "Rigidbody.h"
#include "Dimension.h"

ReianaDimensionState::ReianaDimensionState(ReianaFsm* fsm)
	:ReianaBaseState(fsm,ReianaStateType::Dimension)
{
}

ReianaDimensionState::~ReianaDimensionState()
{
}

void ReianaDimensionState::Awake()
{
}

void ReianaDimensionState::Start()
{
}

void ReianaDimensionState::Enter()
{
	ReianaBaseState::Enter();	
	auto dimension = dynamic_cast<Dimension*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("dimension", LayerType::EnemyBullet));
	dimension->SetActive(true);
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
