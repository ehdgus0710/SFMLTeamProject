#include "stdafx.h"
#include "YggdrasilBaseState.h"
#include "Yggdrasil.h"

#include "Scene.h"
#include "Player.h"

YggdrasilBaseState::YggdrasilBaseState(YggdrasilFSM* fsm, YggdrasilStateType stateType)
	: BaseState<YggdrasilStateType>(stateType)
	, fsm(fsm)
	, yggdrasil(fsm->GetChimera())
{
}

YggdrasilBaseState::~YggdrasilBaseState()
{
}

void YggdrasilBaseState::Awake()
{
	animator = yggdrasil->GetAnimator();
}

void YggdrasilBaseState::Start()
{
	player = static_cast<Player*>(SceneManager::GetInstance().GetCurrentScene()->FindGameObject("Player", LayerType::Player));
}

void YggdrasilBaseState::Enter()
{
	for (auto& startEvent : stateStartEvents)
	{
		startEvent();
	}
}

void YggdrasilBaseState::Exit()
{
	for (auto& endEvent : stateEndEvents)
	{
		endEvent();
	}
}

void YggdrasilBaseState::Update(float deltaTime)
{
}

void YggdrasilBaseState::FixedUpdate(float fixedDeltaTime)
{
}

void YggdrasilBaseState::LateUpdate(float deltaTime)
{
}
