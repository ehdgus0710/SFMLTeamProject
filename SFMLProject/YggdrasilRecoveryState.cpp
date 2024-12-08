#include "stdafx.h"
#include "YggdrasilRecoveryState.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"
#include "Camera.h"

#include "Yggdrasil.h"
#include "Player.h"

void YggdrasilRecoveryState::FirstPos(float deltaTime)
{

	deadTime += deltaTime;
	yggdrasil->SetRotation(Utils::Lerp(-45, 0, deadTime / deadDelay));
	yggdrasil->SetHeadRota(Utils::Lerp(-45, 0, deadTime / deadDelay));
	yggdrasil->SetMouthRota(Utils::Lerp(-45, 0, deadTime / deadDelay));
	yggdrasil->SetPosition(sf::Vector2f::Lerp(bStartPos, bEndPos, deadTime / deadDelay));
	yggdrasil->SetHeadPos(sf::Vector2f::Lerp(hStartPos, hEndPos, deadTime / deadDelay));
	yggdrasil->SetMouthPos(sf::Vector2f::Lerp(mStartPos, mEndPos, deadTime / deadDelay));

	if (deadTime >= recoveryDelay)
	{
		yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(lStartPos, lEndPos, deadTime / endDelay));
		yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rStartPos, rEndPos, deadTime / endDelay));
		yggdrasil->SetPhaseUp(true);
	}
}

void YggdrasilRecoveryState::Start()
{
	YggdrasilBaseState::Start();
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("ElderEnt_Up 1", "AudioClip/Stage1/ElderEnt_Up 1.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("ElderEnt_Groggy_Recovery", "AudioClip/Stage1/ElderEnt_Groggy_Recovery.wav");
	ResourcesManager<sf::SoundBuffer>::GetInstance().Load("ElderEnt_Roar", "AudioClip/Stage1/ElderEnt_Roar.wav");
	SoundManger::GetInstance().PlaySfx("ElderEnt_Up 1", false);
}

void YggdrasilRecoveryState::Enter()
{
	YggdrasilBaseState::Enter();

	PosMove = false;
	oneSound = false;

	deadTime = 0.f;
	soundStartTime = 0.f;
	endTime = 0.f;
	deadDelay = 3.f;
	deadDelay = 3.f;
	recoveryDelay = 4.f;
	endDelay = 11.f;

	bStartPos = yggdrasil->GetPosition();
	bEndPos = { 960.f, 400.f };
	hStartPos = yggdrasil->GetHeadPos();
	hEndPos = { yggdrasil->GetPosition().x + 150.f, yggdrasil->GetPosition().y - 350.f };
	mStartPos = yggdrasil->GetMouthPos();
	mEndPos = { yggdrasil->GetPosition().x + 200.f, yggdrasil->GetPosition().y - 50.f };
	lStartPos = yggdrasil->GetLeftFistPos();
	lEndPos = { yggdrasil->GetPosition().x + 900.f, yggdrasil->GetPosition().y };
	rStartPos = yggdrasil->GetRightFistPos();
	rEndPos = { yggdrasil->GetPosition().x - 500.f, yggdrasil->GetPosition().y };
	if (!yggdrasil->GetPhaseUp())
	{
		yggdrasil->SetAnimeLeftHand("phase1HandLeftGrap", false);
		yggdrasil->SetAnimeRightHand("phase1HandRightGrap", false);
	}
	else
	{
		yggdrasil->SetAnimeLeftHand("phase2HandLeftIdle", false);
		yggdrasil->SetAnimeRightHand("phase2HandRightIdle", false);
	}
}

void YggdrasilRecoveryState::Exit()
{
	YggdrasilBaseState::Exit();
	yggdrasil->OnEndPhaseUp();
}

void YggdrasilRecoveryState::Update(float deltaTime)
{
	soundStartTime += deltaTime;
	endTime += deltaTime;
	if (!PosMove)
	{
		FirstPos(deltaTime);
	}

	if (soundStartTime >= recoveryDelay && !oneSound)
	{
		SoundManger::GetInstance().PlaySfx("ElderEnt_Roar", false);
		SceneManager::GetInstance().GetCurrentScene()->GetMainCamera()->
			SetCameraShake({ 20.f, 20.f }, MoveDirection::Random, 2000.f, 5.f);
		soundStartTime = 0.f;
		oneSound = true;
	}

	if (endTime >= endDelay)
	{
		fsm->ChangeState(YggdrasilStateType::Idle);
		endTime = 0.f;
		deadTime = 0.f;
	}

}

void YggdrasilRecoveryState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilRecoveryState::YggdrasilRecoveryState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::YggdrasilRecovery)
{
}
