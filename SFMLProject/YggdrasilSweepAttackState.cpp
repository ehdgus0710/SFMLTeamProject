#include "stdafx.h"
#include "YggdrasilSweepAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"
#include "Yggdrasil.h"
#include "Player.h"

void YggdrasilSweepAttackState::ReadyAttack(float deltaTime)
{
	currentAttackTime += deltaTime;
	lStartPos = yggdrasil->GetLeftFistPos();
	lEndPos = { yggdrasil->GetPosition().x + 1000.f, 0.f };
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(lStartPos, lEndPos, currentAttackTime / attackTime));
	rStartPos = yggdrasil->GetRightFistPos();
	rEndPos = { yggdrasil->GetPosition().x - 1000.f, 0.f };
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rStartPos, rEndPos, currentAttackTime / attackTime));
	isWait = true;
}

void YggdrasilSweepAttackState::StartLeftAttack(float deltaTime)
{
	currentAttackTime += deltaTime;
	lStartPos = { yggdrasil->GetPosition().x + 1000.f, 0.f };
	lEndPos = { yggdrasil->GetPosition().x - 1000.f, 0.f };
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(lStartPos, lEndPos, currentAttackTime / attackTime));

	if (currentAttackTime >= readyFistTime)
	{
		switchFist = true;
		++attackCount;
		currentAttackTime = 0.f;
	}
}

void YggdrasilSweepAttackState::StartRightAttack(float deltaTime)
{
	currentAttackTime += deltaTime;
	rStartPos = { yggdrasil->GetPosition().x - 1000.f, 0.f };
	rEndPos = { yggdrasil->GetPosition().x + 1000.f, 0.f };
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rStartPos, rEndPos, currentAttackTime / attackTime));

	if (currentAttackTime >= readyFistTime)
	{
		switchFist = true;
		++attackCount;
		currentAttackTime = 0.f;
	}
}

void YggdrasilSweepAttackState::EndAttackWait(float deltaTime)
{
	currentAttackDelay += deltaTime;

	if (currentAttackDelay >= 0.5f)
	{
		currentAttackDelay = 0.f;
		isRecovery = true;
		isWait = false;
	}
}

void YggdrasilSweepAttackState::Recovery(float deltaTime)
{
	currentAttackTime += deltaTime;
	lStartPos = { yggdrasil->GetPosition().x + 300.f, yggdrasil->GetPosition().y + 800.f };
	lEndPos = lFirstPos;
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(lStartPos, lEndPos, currentAttackTime / recoveryTime));
	rStartPos = { yggdrasil->GetPosition().x - 300.f, yggdrasil->GetPosition().y + 800.f };
	rEndPos = rFirstPos;
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rStartPos, rEndPos, currentAttackTime / recoveryTime));
	if (currentAttackTime >= recoveryTime)
	{
		++attackCount;
	}
}

void YggdrasilSweepAttackState::Awake()
{
	YggdrasilBaseState::Awake();
}

void YggdrasilSweepAttackState::Start()
{
	YggdrasilBaseState::Start();
}

void YggdrasilSweepAttackState::Enter()
{
	YggdrasilBaseState::Enter();

	currentAttackCount = 0;
	attackCount = 0;
	whatFist = Utils::RandomRange(1, 2);

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
	attackTime = 0.5f;
	recoveryTime = 1.f;
	readyFistTime = 2.f;

	lFirstPos = yggdrasil->GetLeftFistPos();
	rFirstPos = yggdrasil->GetRightFistPos();

}

void YggdrasilSweepAttackState::Exit()
{
	YggdrasilBaseState::Exit();
}

void YggdrasilSweepAttackState::Update(float deltaTime)
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
		if (attackCount < 2)
		{
			if (!switchFist)
			{
				if (whatFist == 1)
				{
					StartLeftAttack(deltaTime);
				}
				else if (whatFist == 2)
				{
					StartRightAttack(deltaTime);
				}
			}
			else
			{
				if (whatFist == 1)
				{
					StartRightAttack(deltaTime);
				}
				else if (whatFist == 2)
				{
					StartLeftAttack(deltaTime);
				}
			}
		}
	}
	if (attackCount == 2)
	{
		Recovery(deltaTime);
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

void YggdrasilSweepAttackState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilSweepAttackState::YggdrasilSweepAttackState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::SweepAttack)
{
}
