#include "stdafx.h"
#include "YggdrasilEnergyBallAttackState.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "GameManager.h"
#include "Yggdrasil.h"
#include "Player.h"

void YggdrasilEnergyBallAttackState::EnergyBallFire(sf::Vector2f pos, sf::Vector2f dir, float speed, float deltaTime)
{
	shootTime += deltaTime;
	yggdrasil->SetHeadPos(pos + dir * speed * deltaTime);
	if (shootTime > shootDelay)
	{
		++attackCount;
		isShoot = false;
		shootTime = 0.f;
	}
}

void YggdrasilEnergyBallAttackState::Awake()
{
	YggdrasilBaseState::Awake();
}

void YggdrasilEnergyBallAttackState::Start()
{
	YggdrasilBaseState::Start();
}

void YggdrasilEnergyBallAttackState::Enter()
{
	YggdrasilBaseState::Enter();

	isShoot = false;

	speed = 500.f;
	attackCount = 0;
	currentFirstAttack = 0.f;
	firstAttackDelay = 2.f;
	shootTime = 0.f;
	shootDelay = 1.f;

	startPos = yggdrasil->GetHeadPos();
}

void YggdrasilEnergyBallAttackState::Exit()
{
	YggdrasilBaseState::Exit();
}

void YggdrasilEnergyBallAttackState::Update(float deltaTime)
{
	//Fire(position, look, bulletspeed, damege);
	if (attackCount < 2)
	{
		if (!isShoot)
		{
			currentFirstAttack += deltaTime;
			if (currentFirstAttack > firstAttackDelay)
			{
				look = { startPos.y - player->GetPosition().y, startPos.x - player->GetPosition().x };
				isShoot = true;
				currentFirstAttack = 0;
			}
		}
		else
		{
			EnergyBallFire(player->GetPosition(), look, speed, deltaTime);
		}
	}
	else
	{
		fsm->ChangeState(YggdrasilStateType::Idle);
	}
}

void YggdrasilEnergyBallAttackState::FixedUpdate(float fixedDeltaTime)
{
}

YggdrasilEnergyBallAttackState::YggdrasilEnergyBallAttackState(YggdrasilFSM* fsm)
	: YggdrasilBaseState(fsm, YggdrasilStateType::EnergyBallAttack)
{
}
