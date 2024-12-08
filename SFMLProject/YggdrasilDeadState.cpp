#include "stdafx.h"
#include "YggdrasilDeadState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"

#include "Yggdrasil.h"
#include "Player.h"
#include "YggdrasilUIHub.h"
#include "DoorObject.h"

void YggdrasilDeadState::Enter()
{
	lStartPos = yggdrasil->GetLeftFistPos();
	lEndPos = { yggdrasil->GetLeftFistPos().x, 800.f };
	rStartPos = yggdrasil->GetRightFistPos();
	rEndPos = { yggdrasil->GetRightFistPos().x, 800.f };
	bStartPos = yggdrasil->GetPosition();
	bEndPos = { yggdrasil->GetPosition().x - 150.f, 650.f };
	hStartPos = yggdrasil->GetHeadPos();
	hEndPos = { yggdrasil->GetHeadPos().x - 150.f, 700.f };
	mStartPos = yggdrasil->GetMouthPos();
	mEndPos = { yggdrasil->GetMouthPos().x + 40.f, 860.f };
	if (!yggdrasil->GetPhaseUp())
	{
		yggdrasil->SetAnimeLeftHand("phase1HandLeftGrap", false);
		yggdrasil->SetAnimeRightHand("phase1HandRightGrap", false);
	}
	else
	{
		yggdrasil->SetAnimeLeftHand("phase2HandLeftGrap", false);
		yggdrasil->SetAnimeRightHand("phase2HandRightGrap", false);
	}
	deadTime = 0.f;
	deadDelay = 3.f;
}

void YggdrasilDeadState::Exit()
{
	
}

void YggdrasilDeadState::Update(float deltaTime)
{
	deadTime += deltaTime;
	yggdrasil->SetRotation(Utils::Lerp(0, -45, deadTime / deadDelay));
	yggdrasil->SetHeadRota(Utils::Lerp(0, -45, deadTime / deadDelay));
	yggdrasil->SetMouthRota(Utils::Lerp(0, -45, deadTime / deadDelay));
	yggdrasil->SetPosition(sf::Vector2f::Lerp(bStartPos, bEndPos, deadTime / deadDelay));
	yggdrasil->SetHeadPos(sf::Vector2f::Lerp(hStartPos, hEndPos, deadTime / deadDelay));
	yggdrasil->SetMouthPos(sf::Vector2f::Lerp(mStartPos, mEndPos, deadTime / deadDelay));
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(lStartPos, lEndPos, deadTime / deadDelay));
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rStartPos, rEndPos, deadTime / deadDelay));

	if (!deadEnd && deadTime > deadDelay)
	{
		deadEnd = true;
		yggdrasil->GetCollider()->SetActive(false);
		yggdrasil->GetYggdrasilUIHub()->OnDeadYggdrasil();

		ColliderManager::GetInstance().SetCollisionCheck(ColliderLayer::Door, ColliderLayer::Player);
		GameManager::GetInstance().OnRestart();
		DoorObject* clearDoor = SCENE_MANAGER.GetCurrentScene()->AddGameObject(new DoorObject("KeyF", SceneIds::Stage1, "ClearDoor"), LayerType::BackGround_Forward);
		clearDoor->SetPosition({ 960.f, 650.f });
		clearDoor->Start();
	}
}

void YggdrasilDeadState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilDeadState::YggdrasilDeadState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::Dead)
	, deadEnd(false)
{
}
