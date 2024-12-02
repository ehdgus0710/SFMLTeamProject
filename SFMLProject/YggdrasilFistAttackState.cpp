#include "stdafx.h"
#include "YggdrasilFistAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"
#include "Yggdrasil.h"
#include "Player.h"

void YggdrasilFistAttackState::ReadyFist(float deltaTime)
{
	currentAttackTime += deltaTime;
	startPos = yggdrasil->GetLeftFistPos();
	endPos = { yggdrasil->GetLeftFistPos().x, yggdrasil->GetPosition().y - 200 };
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(startPos, endPos, currentAttackTime / readyDelay));
	startPos = yggdrasil->GetRightFistPos();
	endPos = { yggdrasil->GetRightFistPos().x, yggdrasil->GetPosition().y - 200 };
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(startPos, endPos, currentAttackTime / readyDelay));



	if (currentAttackTime > readyDelay)
	{
		startPos = endPos;
		endPos = { player->GetPosition().x, 0.f };
		currentAttackTime = 0.f;
	}

}

void YggdrasilFistAttackState::StartAttack(float deltaTime)
{
	switchFistDelay = 0.f;
	if (!switchFist)
	{
		currentAttackTime += deltaTime;
		yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(startPos, endPos, currentAttackTime / attackTime));

		if (currentAttackTime >= attackTime)
		{
			currentAttackTime = 0.f;
			currentAttackDelay = 0.f;
			isWait = true;
		}
	}
	else
	{
		currentAttackTime += deltaTime;
		yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(startPos, endPos, currentAttackTime / attackTime));

		if (currentAttackTime >= attackTime)
		{
			currentAttackTime = 0.f;
			currentAttackDelay = 0.f;
			isWait = true;
		}
	}
}

void YggdrasilFistAttackState::EndAttackWait(float deltaTime)
{
	currentAttackDelay += deltaTime;


	if (currentAttackDelay >= 0.5f)
	{
		currentAttackDelay = 0.f;
		isRecovery = true;
		isWait = false;
	}
}

void YggdrasilFistAttackState::EndFistPos(float deltaTime)
{
	currentAttackTime += deltaTime;
	startPos = { yggdrasil->GetLeftFistPos().x, yggdrasil->GetPosition().y - 200 };
	endPos = firstLeftPos;
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(startPos, endPos, currentAttackTime / readyDelay));
	startPos = { yggdrasil->GetRightFistPos().x, yggdrasil->GetPosition().y - 200 };
	endPos = firstRightPos;
	yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(startPos, endPos, currentAttackTime / readyDelay));


	if (currentAttackTime >= readyDelay)
	{
		readyFist = false;
		onAttack = false;
	}

}

void YggdrasilFistAttackState::Recovery(float deltaTime)
{
	if (!switchFist)
	{
		currentRecoveryTime += deltaTime;
		yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(endPos, startPos, currentRecoveryTime / recoveryTime));

		if (currentRecoveryTime >= recoveryTime)
		{
			isAttack = false;
			isRecovery = false;
			currentRecoveryTime = 0.f;
			++currentAttackCount;
		}
	}
	else
	{
		currentRecoveryTime += deltaTime;
		yggdrasil->SetRightFistPos(sf::Vector2f::Lerp(endPos, startPos, currentRecoveryTime / recoveryTime));

		if (currentRecoveryTime >= recoveryTime)
		{
			isAttack = false;
			isRecovery = false;
			currentRecoveryTime = 0.f;
			++currentAttackCount;
		}
	}
}

void YggdrasilFistAttackState::Awake()
{
	YggdrasilBaseState::Awake();

}

void YggdrasilFistAttackState::Start()
{
	YggdrasilBaseState::Start();
}

void YggdrasilFistAttackState::Enter()
{
	YggdrasilBaseState::Enter();

	yggdrasil->SetAnimeLeftHand("phase1HandLeftTakedown", false);
	yggdrasil->SetAnimeRightHand("phase1HandRightTakedown", false);

	currentAttackCount = 0;
	attackCount = 2;

	readyFist = false;
	isAttack = false;
	isRecovery = false;
	isWait = false;
	switchFist = false;
	onAttack = true;

	currentAttackDelay = 0.f;
	currentAttackTime = 0.f;
	currentRecoveryTime = 0.f;
	switchFistDelay = 2.8f;
	readyTime = 0.f;

	readyDelay = 1.f;
	attackDelay = 2.f;
	attackTime = 0.3f;
	recoveryTime = 0.7f;
	switchFistTime = 2.8f;

	endPos = { player->GetPosition().x, 0.f };
	firstLeftPos = yggdrasil->GetLeftFistPos();
	firstRightPos = yggdrasil->GetRightFistPos();
}

void YggdrasilFistAttackState::Exit()
{
	YggdrasilBaseState::Exit();
}

void YggdrasilFistAttackState::Update(float deltaTime)
{
	if (!readyFist)
	{
		readyTime += deltaTime;
		ReadyFist(deltaTime);
		if (readyTime > readyDelay)
		{
			readyFist = true;
		}
	}
	else
	{
		switchFistDelay += deltaTime;
	}
	if (player->GetPosition().x > yggdrasil->GetPosition().x && switchFistDelay >= switchFistTime)
	{
		switchFist = false;
	}
	else if (player->GetPosition().x < yggdrasil->GetPosition().x && switchFistDelay >= switchFistTime)
	{
		switchFist = true;
	}
	if (!switchFist)
	{
		if (!isAttack)
		{
			currentAttackDelay += deltaTime;

			if (currentAttackDelay >= attackDelay)
			{
				startPos = yggdrasil->GetLeftFistPos();
				endPos = { player->GetPosition().x, 913.f };
				isAttack = true;
				currentAttackTime = 0.f;
			}
		}
		else
		{
			if (isRecovery)
			{
				Recovery(deltaTime);
			}
			else
			{
				if (!isWait)
				{
					StartAttack(deltaTime);
				}
				else
					EndAttackWait(deltaTime);
			}
		}
	}
	if (switchFist)
	{
		if (!isAttack)
		{
			currentAttackDelay += deltaTime;

			if (currentAttackDelay >= attackDelay)
			{
				startPos = yggdrasil->GetRightFistPos();
				endPos = { player->GetPosition().x, 913.f };
				isAttack = true;
				currentAttackTime = 0.f;
			}
		}
		else
		{
			if (isRecovery)
			{
				Recovery(deltaTime);
			}
			else
			{
				if (!isWait)
					StartAttack(deltaTime);
				else
					EndAttackWait(deltaTime);
			}
		}
	}


	if (currentAttackCount == attackCount)
	{
		EndFistPos(deltaTime);
	}

	if (!onAttack)
	{
		fsm->ChangeState(YggdrasilStateType::Idle);
	}
}

void YggdrasilFistAttackState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilFistAttackState::YggdrasilFistAttackState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::FistAttack)
{
}

