#include "stdafx.h"
#include "YggdrasilSpecialAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"
#include "Yggdrasil.h"
#include "Player.h"
#include "HitBoxObject.h"
void YggdrasilSpecialAttackState::ReadyAttack(float deltaTime)
{
	currentAttackTime += deltaTime;
	lStartPos = lFirstPos;
	lEndPos = { yggdrasil->GetLeftFistPos().x, 200.f };
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(lStartPos, lEndPos, currentAttackTime / readyFistTime));
	rStartPos = rFirstPos;
	rEndPos = { yggdrasil->GetRightFistPos().x, 200.f };
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rStartPos, rEndPos, currentAttackTime / readyFistTime));
	if (currentAttackTime > readyFistTime)
	{
		currentAttackDelay = 0.f;
		currentAttackTime = 0.f;
	}
}

void YggdrasilSpecialAttackState::StartSpecialAttack(float deltaTime)
{

	currentAttackTime += deltaTime;
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(lEndPos, lStartPos, currentAttackTime / attackTime));
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rEndPos, rStartPos, currentAttackTime / attackTime));


	if (currentAttackTime >= readyFistTime)
	{
		HitBoxOn();
		++attackCount;
		currentAttackTime = 0.f;
	}
}

void YggdrasilSpecialAttackState::EndAttackWait(float deltaTime)
{
	currentAttackDelay += deltaTime;

	if (currentAttackDelay >= waitTime)
	{
		currentAttackDelay = 0.f;
		isRecovery = true;
		isWait = false;
	}
}

void YggdrasilSpecialAttackState::Recovery(float deltaTime)
{
	HitBoxOff();
	currentAttackTime += deltaTime;
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(lStartPos, lEndPos, currentAttackTime / recoveryTime));
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rStartPos, rEndPos, currentAttackTime / recoveryTime));
	if (currentAttackTime > recoveryTime)
	{
		isRecovery = false;
		isWait = true;
	}
}

void YggdrasilSpecialAttackState::HitBoxOn()
{
	attackBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(yggdrasil, ColliderLayer::Boss, ColliderLayer::Player, false, (sf::Vector2f::right * 30.f)), LayerType::Boss);
	attackBox->SetScale({ 2000.f,50.f });
	attackBox->SetDamage(10);
	attackBox->SetPosition({ 960.f, 913.f });
}

void YggdrasilSpecialAttackState::HitBoxOff()
{
	attackBox->OnDestory();
}

void YggdrasilSpecialAttackState::Awake()
{
	YggdrasilBaseState::Awake();
}

void YggdrasilSpecialAttackState::Start()
{
	YggdrasilBaseState::Start();
	changeOn = false;
}

void YggdrasilSpecialAttackState::Enter()
{
	YggdrasilBaseState::Enter();
	yggdrasil->SetAnimeLeftHand("phase2HandLeftTakedown", false);
	yggdrasil->SetAnimeRightHand("phase2HandRightTakedown", false);

	attackCount = 0;

	readyAttack = false;
	isAttack = false;
	isRecovery = false;
	isWait = false;
	switchFist = false;
	onAttack = true;

	currentAttackDelay = 0.f;
	currentAttackTime = 0.f;
	currentRecoveryTime = 0.f;
	readyFistDelay = 0.f;

	attackDelay = 1.f;
	attackTime = 0.3f;
	recoveryTime = 0.5f;
	readyFistTime = 1.f;
	waitTime = 1.f;

	lFirstPos = yggdrasil->GetLeftFistPos();
	rFirstPos = yggdrasil->GetRightFistPos();

}

void YggdrasilSpecialAttackState::Exit()
{
	YggdrasilBaseState::Exit();
}

void YggdrasilSpecialAttackState::Update(float deltaTime)
{
	// 휩쓸기 준비 모션
	if (!readyAttack)
	{
		readyFistDelay += deltaTime;
		ReadyAttack(deltaTime);
		if (readyFistDelay > readyFistTime)
		{
			readyAttack = true;
			readyFistDelay = 0.f;
			currentAttackTime = 0.f;
		}
	}
	else
	{
		if (attackCount < 3)
		{
			if (isWait)
			{
				StartSpecialAttack(deltaTime);
			}
			else
			{
				EndAttackWait(deltaTime);
			}
		}
	}
	if (isRecovery)
	{
		Recovery(deltaTime);
	}
	if (attackCount == 0 || attackCount == 2)
	{
		waitTime = 3.f;
	}
	else
	{
		waitTime = 1.f;
	}

	if (attackCount == 3)
	{
		fsm->ChangeState(YggdrasilStateType::Idle);
	}


	//if (currentAttackCount == attackCount)
	//	onAttack = false;

	//if (!onAttack)
	//{
	//	fsm->ChangeState(YggdrasilStateType::Idle);
	//}
}

void YggdrasilSpecialAttackState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilSpecialAttackState::YggdrasilSpecialAttackState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::YggdrasilSpecialAttack)
{
}