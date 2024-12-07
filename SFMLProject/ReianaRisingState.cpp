#include "stdafx.h"
#include "ReianaRisingState.h"
#include "Player.h"
#include "Knife.h"
#include "Animation.h"
#include "Animator.h"
#include "RisingReady.h"
#include "Scene.h"
#include "Rising.h"

ReianaRisingState::ReianaRisingState(ReianaFsm* fsm)
	:ReianaBaseState(fsm, ReianaStateType::Rising)
{
}

ReianaRisingState::~ReianaRisingState()
{
}

void ReianaRisingState::Awake()
{
	ReianaBaseState::Awake();
}

void ReianaRisingState::Start()
{
	ReianaBaseState::Start();
}

void ReianaRisingState::CreateRising()
{
	if (count < 11)
	{
		Rising* rising = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new Rising(reiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, "RisingPierce"), LayerType::EnemyBullet);
		rising->Start();
		rising->SetPosition(risingReadyPos + (risingPos * count));

		Rising* rising1 = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new Rising(reiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, "RisingPierce"), LayerType::EnemyBullet);
		rising1->Start();
		rising1->SetPosition(risingReadyPos - (risingPos * count));

		if (count == 8)
		{
			animator->ChangeAnimation("risingPierceEnd", false);
		}
		++count;
	}
	else
	{
		fsm->ChangeState(ReianaStateType::Idle);
	}
}

void ReianaRisingState::Enter()
{
	ReianaBaseState::Enter();
	RisingReady* risingReady = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new RisingReady(reiana, ColliderLayer::EnemyBullet, ColliderLayer::Player, "RisingPierceReady"), LayerType::EnemyBullet);
	risingReady->Start();
	risingReadyPos = risingReady->GetEffectPos();
	animator->ChangeAnimation("risingPierceReady", false);
	startCurrentDelay = 0.f;
	endCurrentDelay = 0.f;
	CurrentRisingDelat = 0.f;
	count = 1;
	if (reiana->GetPosition().x < reiana->GetPlayer()->GetPosition().x && reiana->IsFlipX())
	{
		reiana->OnFlipX();
	}
	if (reiana->GetPosition().x > reiana->GetPlayer()->GetPosition().x && !reiana->IsFlipX())
	{
		reiana->OnFlipX();
	}
}

void ReianaRisingState::Exit()
{
	ReianaBaseState::Exit();
}

void ReianaRisingState::Update(float deltaTime)
{
	ReianaBaseState::Update(deltaTime);
	startCurrentDelay += deltaTime;

	if (startCurrentDelay > startDelay)
	{
		CurrentRisingDelat += deltaTime;
		if (CurrentRisingDelat > RisingDelat)
		{
			CreateRising();
			CurrentRisingDelat = 0;
		}
	}

}

void ReianaRisingState::FixedUpdate(float fixedDeltaTime)
{
	ReianaBaseState::FixedUpdate(fixedDeltaTime);

}

void ReianaRisingState::LateUpdate(float deltaTime)
{
	ReianaBaseState::LateUpdate(deltaTime);

}
