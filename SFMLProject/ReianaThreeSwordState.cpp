#include "stdafx.h"
#include "ReianaThreeSwordState.h"
#include "Knife.h"
#include "Player.h"
#include "Animator.h"

ReianaThreeSwordState::ReianaThreeSwordState(ReianaFsm* fsm)
	:ReianaBaseState(fsm,ReianaStateType::ThreeSword)
	,currentDelay(0.f)
	,delayTime(1.f)
	,fix(false)
	,changeTime(3.f)
{
}

ReianaThreeSwordState::~ReianaThreeSwordState()
{
}

void ReianaThreeSwordState::Awake()
{
	ReianaBaseState::Awake();

}

void ReianaThreeSwordState::Start()
{
	ReianaBaseState::Start();

}

void ReianaThreeSwordState::CreateKnife()
{
	Knife* knife = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new Knife(reiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, "MenuBar"), LayerType::EnemyBullet);
	knife->SetScale({ 2.f,2.f });
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
			knife->setDelay(1.f);
			break;
		case ReianaThreeSwordState::Pos::POS3:
			knife->SetPosition(reiana->GetPosition() + plusPos3);
			knife->setDelay(1.5f);
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
			knife->setDelay(1.f);
			break;
		case ReianaThreeSwordState::Pos::POS3:
			knife->SetPosition(reiana->GetPosition() - plusFlipPos3);
			knife->setDelay(1.5f);
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
	currentChangeTime = 0.f;
	delayTime = 1.f;
	animator->ChangeAnimation("homingpierceReady", false);
	fix = false;
	if (reiana->GetPosition().x < reiana->GetPlayer()->GetPosition().x && reiana->IsFlipX())
	{
		reiana->OnFlipX();
	}
	if (reiana->GetPosition().x > reiana->GetPlayer()->GetPosition().x && !reiana->IsFlipX())
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
	currentChangeTime += deltaTime;
	if (currentChangeTime > changeTime)
	{
		fsm->ChangeState(ReianaStateType::Idle);
	}
	if (currentDelay > delayTime)
	{
		animator->ChangeAnimation("homingPierce", false);
		CreateKnife();
		delayTime = 100.f;
	}
	else if (!fix&&currentDelay > delayTime / 2)
	{
		animator->ChangeAnimation("homingPierce", false);
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
