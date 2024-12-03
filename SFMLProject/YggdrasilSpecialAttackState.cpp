#include "stdafx.h"
#include "YggdrasilSpecialAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"
#include "Yggdrasil.h"
#include "Player.h"
#include "HitBoxObject.h"
#include "YggdrasilLeftHand.h"
#include "YggdrasilRightHand.h"
void YggdrasilSpecialAttackState::ReadyAttack(float deltaTime)
{
	currentAttackTime += deltaTime;
	lEndPos = { yggdrasil->GetRightFistPos() + sf::Vector2f::up * 800.f };
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(lStartPos, lEndPos, currentAttackTime / readyFistTime));
	rEndPos = { yggdrasil->GetRightFistPos() + sf::Vector2f::up * 800.f };
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rStartPos, rEndPos, currentAttackTime / readyFistTime));
	isWait = true;
}

void YggdrasilSpecialAttackState::StartLeftAttack(float deltaTime)
{

	currentAttackTime += deltaTime;
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(lEndPos, lStartPos, currentAttackTime / attackTime));
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rEndPos, rStartPos, currentAttackTime / attackTime));


	if (currentAttackTime >= readyFistTime)
	{
		attackBox = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new HitBoxObject(yggdrasil->GetYggdrasilLeftHand(), ColliderLayer::Boss, ColliderLayer::Player, true, (sf::Vector2f::right * 30.f)), LayerType::Boss);
		attackBox->SetScale({ 2000.f,25.f });
		attackBox->SetDamage(10);
		attackBox->SetPosition({ yggdrasil->GetPosition().x, 913.f });
		++attackCount;
		currentAttackTime = 0.f;
	}
}

void YggdrasilSpecialAttackState::EndAttackWait(float deltaTime)
{
	attackBox->OnDestory();
	hitBoxOn = false;
	currentAttackDelay += deltaTime;

	if (currentAttackDelay >= attackDelay)
	{
		currentAttackDelay = 0.f;
		isRecovery = true;
		isWait = false;
	}
}

void YggdrasilSpecialAttackState::Recovery(float deltaTime)
{
	currentAttackTime += deltaTime;
	lEndPos = { yggdrasil->GetRightFistPos() + sf::Vector2f::up * 800.f };
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(lStartPos, lEndPos, currentAttackTime / recoveryTime));
	rEndPos = { yggdrasil->GetRightFistPos() + sf::Vector2f::up * 800.f };
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rStartPos, rEndPos, currentAttackTime / recoveryTime));
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

	attackDelay = 2.f;
	attackTime = 2.f;
	recoveryTime = 1.f;
	readyFistTime = 2.f;

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
		currentAttackTime = 0.f;
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
		if (attackCount < 4)
		{
			if (isWait)
			{
				StartLeftAttack(deltaTime);
			}
			else
			{
				EndAttackWait(deltaTime);
			}
		}
	}
	if (attackCount == 1 || attackCount == 2 || attackCount == 3)
	{
		Recovery(deltaTime);
	}

	if (attackCount == 4)
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