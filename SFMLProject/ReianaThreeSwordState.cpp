#include "stdafx.h"
#include "ReianaThreeSwordState.h"
#include "ReianaKnifeState.h"
#include "Knife.h"

ReianaThreeSwordState::ReianaThreeSwordState(ReianaFsm* fsm)
	:ReianaBaseState(fsm,ReianaStateType::ThreeSword)
	,currentDelay(0.f)
	,delayTime(2.f)
	,fix(false)
{
}

ReianaThreeSwordState::~ReianaThreeSwordState()
{
}

void ReianaThreeSwordState::Awake()
{
}

void ReianaThreeSwordState::Start()
{
}

void ReianaThreeSwordState::CreateKnife()
{
	Knife* knife = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new Knife(reiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, "MenuBar"), LayerType::EnemyBullet);
	knife->SetPosition(reiana->GetPosition());
	knife->Awake();
	knife->Start();
}

void ReianaThreeSwordState::Enter()
{
	ReianaBaseState::Enter();
	currentDelay = 0.f;
	fix = false;
	CreateKnife();
}

void ReianaThreeSwordState::Exit()
{
	ReianaBaseState::Exit();

}

void ReianaThreeSwordState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);
	currentDelay += deltaTime;
	if (currentDelay > delayTime)
	{
		CreateKnife();
		fsm->ChangeState(ReianaStateType::Idle);
	}
	else if (!fix&&currentDelay > delayTime / 2)
	{
		CreateKnife();
		fix = true;
	}
}

void ReianaThreeSwordState::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void ReianaThreeSwordState::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);

}
