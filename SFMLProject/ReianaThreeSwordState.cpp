#include "stdafx.h"
#include "ReianaThreeSwordState.h"
#include "ReianaKnifeState.h"
#include "Knife.h"
#include "Player.h"

ReianaThreeSwordState::ReianaThreeSwordState(ReianaFsm* fsm)
	:ReianaBaseState(fsm,ReianaStateType::ThreeSword)
	,currentDelay(0.f)
	,delayTime(0.5f)
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
	if (reiana->IsFlipX())
	{
		switch ((ReianaThreeSwordState::Pos)count)
		{
		case ReianaThreeSwordState::Pos::POS1:
			knife->SetPosition(reiana->GetPosition() + plusPos1);
			knife->setDelay(1.f);
			break;
		case ReianaThreeSwordState::Pos::POS2:
			knife->SetPosition(reiana->GetPosition() + plusPos2);
			knife->setDelay(1.5f);
			break;
		case ReianaThreeSwordState::Pos::POS3:
			knife->SetPosition(reiana->GetPosition() + plusPos3);
			knife->setDelay(2.f);
			break;
		default:
			break;
		}
	}
	else
	{
		switch ((ReianaThreeSwordState::Pos)count)
		{
		case ReianaThreeSwordState::Pos::POS1:
			knife->SetPosition(reiana->GetPosition() - plusFlipPos1);
			knife->setDelay(1.f);
			break;
		case ReianaThreeSwordState::Pos::POS2:
			knife->SetPosition(reiana->GetPosition() - plusFlipPos2);
			knife->setDelay(1.5f);
			break;
		case ReianaThreeSwordState::Pos::POS3:
			knife->SetPosition(reiana->GetPosition() - plusFlipPos3);
			knife->setDelay(2.f);
			break;
		default:
			break;
		}
	}
	count++;
	knife->Awake();
	knife->Start();
}

void ReianaThreeSwordState::Enter()
{
	ReianaBaseState::Enter();
	count = 1;
	currentDelay = 0.f;
	fix = false;
	if (reiana->IsFlipX() && reiana->GetPosition().x < reiana->GetPlayer()->GetPosition().x)
	{
		reiana->OnFlipX();
	}
	if (!reiana->IsFlipX() && reiana->GetPosition().x > reiana->GetPlayer()->GetPosition().x)
	{
		reiana->OnFlipX();
	}
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
