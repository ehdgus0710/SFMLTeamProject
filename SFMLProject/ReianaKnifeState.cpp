#include "stdafx.h"
#include "ReianaKnifeState.h"
#include "Player.h"
#include "Knife.h"

ReianaKnifeState::ReianaKnifeState(ReianaFsm* fsm)
	:ReianaBaseState(fsm, ReianaStateType::Knife)
{
}

ReianaKnifeState::~ReianaKnifeState()
{
}

void ReianaKnifeState::Awake()
{
}

void ReianaKnifeState::Start()
{
}

void ReianaKnifeState::CreateDimension()
{
	Knife* knife = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new Knife(reiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, "MenuBar"), LayerType::EnemyBullet);
	knife->SetPosition(reiana->GetPosition());
	knife->Awake();
	knife->Start();
}

void ReianaKnifeState::Enter()
{
	ReianaBaseState::Enter();

	CreateDimension();
}

void ReianaKnifeState::Exit()
{
	ReianaBaseState::Exit();

}

void ReianaKnifeState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);

}

void ReianaKnifeState::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void ReianaKnifeState::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);

}
