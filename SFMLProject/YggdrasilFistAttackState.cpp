#include "stdafx.h"
#include "YggdrasilFistAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"
#include "Yggdrasil.h"
#include "Player.h"

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
	onAttack = true;
}

void YggdrasilFistAttackState::Enter()
{
	YggdrasilBaseState::Enter();

	currentAttackCount = 0;
	attackCount = 2;

	isAttack = false;
	isRecovery = false;
	isWait = false;
	switchFist = false;

	currentAttackDelay = 0.f;
	currentAttackTime = 0.f;
	currentRecoveryTime = 0.f;
	switchFistDelay = 2.8f;

	attackDelay = 2.f;
	attackTime = 0.3f;
	recoveryTime = 0.5f;
	switchFistTime = 2.8f;

	endPos = { player->GetPosition().x, 0.f };
	//startPos = yggdrasil->GetLeftFistPos();
	//firstPos = yggdrasil->GetLeftFistPos();

}

void YggdrasilFistAttackState::Exit()
{
	YggdrasilBaseState::Exit();
}

void YggdrasilFistAttackState::Update(float deltaTime)
{
	switchFistDelay += deltaTime;
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
				isAttack = true;
				currentAttackTime = 0.f;

				endPos = { player->GetPosition().x, 0.f };
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
	if (switchFist)
	{
		if (!isAttack)
		{
			currentAttackDelay += deltaTime;

			if (currentAttackDelay >= attackDelay)
			{
				startPos = yggdrasil->GetRightFistPos();
				isAttack = true;
				currentAttackTime = 0.f;

				endPos = { player->GetPosition().x, 0.f };
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
		onAttack = false;

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

