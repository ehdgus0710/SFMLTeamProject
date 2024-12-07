#include "stdafx.h"
#include "B_ReianaThreeSwordState.h"
#include "Knife.h"
#include "Player.h"
#include "Animator.h"

B_ReianaThreeSwordState::B_ReianaThreeSwordState(B_ReianaFsm* fsm)
	:B_ReianaBaseState(fsm, B_ReianaStateType::ThreeSword)
	, currentDelay(0.f)
	, delayTime(1.f)
	, fix(false)
	, changeTime(3.f)
{
}

B_ReianaThreeSwordState::~B_ReianaThreeSwordState()
{
}

void B_ReianaThreeSwordState::Awake()
{
	B_ReianaBaseState::Awake();

}

void B_ReianaThreeSwordState::Start()
{
	B_ReianaBaseState::Start();

}

void B_ReianaThreeSwordState::CreateKnife()
{
	Knife* knife = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new Knife(b_reiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, "MenuBar"), LayerType::EnemyBullet);
	knife->SetScale({ 2.f,2.f });
	if (b_reiana->IsFlipX())
	{
		switch ((B_ReianaThreeSwordState::Pos)count)
		{
		case B_ReianaThreeSwordState::Pos::POS1:
			knife->SetPosition(b_reiana->GetPosition() + plusPos1);
			knife->setDelay(1.4f);
			break;
		case B_ReianaThreeSwordState::Pos::POS2:
			knife->SetPosition(b_reiana->GetPosition() + plusPos2);
			knife->setDelay(1.6f);
			break;
		case B_ReianaThreeSwordState::Pos::POS3:
			knife->SetPosition(b_reiana->GetPosition() + plusPos3);
			knife->setDelay(1.8f);
			break;
		default:
			break;
		}
	}
	else
	{
		switch ((B_ReianaThreeSwordState::Pos)count)
		{
		case B_ReianaThreeSwordState::Pos::POS1:
			knife->SetPosition(b_reiana->GetPosition() - plusFlipPos1);
			knife->setDelay(1.4f);
			break;
		case B_ReianaThreeSwordState::Pos::POS2:
			knife->SetPosition(b_reiana->GetPosition() - plusFlipPos2);
			knife->setDelay(1.6f);
			break;
		case B_ReianaThreeSwordState::Pos::POS3:
			knife->SetPosition(b_reiana->GetPosition() - plusFlipPos3);
			knife->setDelay(1.8f);
			break;
		default:
			break;
		}
	}
	count++;
	knife->Awake();
	knife->Start();
}

void B_ReianaThreeSwordState::Enter()
{
	B_ReianaBaseState::Enter();
	count = 1;
	currentDelay = 0.f;
	currentChangeTime = 0.f;
	delayTime = 0.5f;
	animator->ChangeAnimation("homingpierceReady", false);
	fix = false;
	if (!b_reiana->IsFlipX() && b_reiana->GetPosition().x > b_reiana->GetPlayer()->GetPosition().x)
	{
		b_reiana->OnFlipX();
	}
	if (b_reiana->IsFlipX() && b_reiana->GetPosition().x < b_reiana->GetPlayer()->GetPosition().x)
	{
		b_reiana->OnFlipX();
	}
	CreateKnife();

}

void B_ReianaThreeSwordState::Exit()
{
	B_ReianaBaseState::Exit();
}

void B_ReianaThreeSwordState::Update(float deltaTime)
{
	B_ReianaBaseState::Update(deltaTime);
	currentDelay += deltaTime;
	currentChangeTime += deltaTime;
	if (currentChangeTime > changeTime)
	{
		fsm->ChangeState(B_ReianaStateType::Idle);
	}
	if (currentDelay > delayTime)
	{
		animator->ChangeAnimation("homingPierce", false);
		CreateKnife();
		delayTime = 100.f;
	}
	else if (!fix && currentDelay > delayTime / 2)
	{
		animator->ChangeAnimation("homingPierce", false);
		CreateKnife();
		fix = true;
	}
}

void B_ReianaThreeSwordState::FixedUpdate(float fixedDeltaTime)
{
	B_ReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void B_ReianaThreeSwordState::LateUpdate(float deltaTime)
{
	B_ReianaBaseState::LateUpdate(deltaTime);

}
