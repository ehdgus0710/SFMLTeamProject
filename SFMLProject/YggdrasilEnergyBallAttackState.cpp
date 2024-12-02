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
	yggdrasil->SetEnergyBallBigPos(pos + dir * speed * deltaTime);
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

	speed = 1000.f;
	attackCount = 0;
	currentFirstAttack = 0.f;
	firstAttackDelay = 2.f;
	shootTime = 0.f;
	shootDelay = 2.f;

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
			yggdrasil->SetEnergyBallBigPos(startPos);
			currentFirstAttack += deltaTime;
			if (currentFirstAttack > firstAttackDelay)
			{
				//float radi = atan2f(startPos.y - player->GetPosition().y, startPos.x - player->GetPosition().x);
				//float degr = (radi * 180 / Utils::PI) + 90;
				//look = 노멀라이즈 어디있는데 ㅋㅋㅋㅋ;
				look = player->GetPosition() - startPos;
				look.Normalized();
				isShoot = true;
				currentFirstAttack = 0;
			}
		}
		else
		{
			EnergyBallFire(yggdrasil->GetEnergyBallBigPos(), look, speed, deltaTime);
		}
	}
	else
	{
		yggdrasil->SetEnergyBallBigPos(startPos);
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
