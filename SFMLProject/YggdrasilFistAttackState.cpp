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
	currentAttackTime += deltaTime;
	yggdrasil->SetLeftFistPos(sf::Vector2f::Lerp(startPos, endPos, currentAttackTime / attackTime));

	if (currentAttackTime >= attackTime)
	{
		currentAttackTime = 0.f;
		currentAttackDelay = 0.f;
		isWait = true;
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

	currentAttackDelay = 0.f;
	currentAttackTime = 0.f;
	currentRecoveryTime = 0.f;

	attackDelay = 1.f;
	attackTime = 1.f;
	recoveryTime = 1.f;

	endPos = player->GetPosition();
	startPos = yggdrasil->GetLeftFistPos();
	firstPos = yggdrasil->GetLeftFistPos();
	
}

void YggdrasilFistAttackState::Exit()
{
	YggdrasilBaseState::Exit();
}

void YggdrasilFistAttackState::Update(float deltaTime)
{

	if (!isAttack)
	{
		currentAttackDelay += deltaTime;

		if (currentAttackDelay >= attackDelay)
		{
			isAttack = true;
			currentAttackTime = 0.f;

			endPos = player->GetPosition();
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

