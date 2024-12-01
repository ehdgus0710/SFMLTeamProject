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
}

void YggdrasilSweepAttackState::StartRightAttack(float deltaTime)
{
	currentAttackTime += deltaTime;
	rStartPos = { yggdrasil->GetPosition().x - 1000.f, 0.f };
	rEndPos = { yggdrasil->GetPosition().x + 1000.f, 0.f };
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(rStartPos, rEndPos, currentAttackTime / attackTime));
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
	//if (!switchFist)
	//{
	//	currentRecoveryTime += deltaTime;
	//	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(endPos, startPos, currentRecoveryTime / recoveryTime));
	//
	//	if (currentRecoveryTime >= recoveryTime)
	//	{
	//		isAttack = false;
	//		isRecovery = false;
	//		currentRecoveryTime = 0.f;
	//		++currentAttackCount;
	//	}
	//}
	//else
	//{
	//	currentRecoveryTime += deltaTime;
	//	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(endPos, startPos, currentRecoveryTime / recoveryTime));
	//
	//	if (currentRecoveryTime >= recoveryTime)
	//	{
	//		isAttack = false;
	//		isRecovery = false;
	//		currentRecoveryTime = 0.f;
	//		++currentAttackCount;
	//	}
	//}
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
	attackTime = 0.3f;
	recoveryTime = 0.5f;
	readyFistTime = 2.f;

}

void YggdrasilSweepAttackState::Exit()
{
	YggdrasilBaseState::Exit();
}

void YggdrasilSweepAttackState::Update(float deltaTime)
{
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
		readyFistDelay += deltaTime;
		if (readyFistDelay > readyFistTime)
		{
			currentAttackDelay += deltaTime;
			if (currentAttackDelay > attackDelay)
			{
				switchFist = true;
				currentAttackTime = 0.f;
			}
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
